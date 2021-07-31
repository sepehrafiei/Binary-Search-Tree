//
//  main.cpp
//  AVL
//  Created by Sepehr Rafiei on 5/1/21.
//  This program creates an AVL tree from the values within a file.

//includes
#include <iostream>
#include <fstream>
#include <string>
#include<cstdlib>
#include<conio.h>
#include<Windows.h>
#include <fcntl.h>
#include <io.h>
#include <stdint.h>
using namespace std;

//used within certain classes to differentiate stages of recursion.
bool newBranch = false;



//Node Class
class Node {
public:
    //children
    Node* left;
    Node* right;

    int value; //value
};

//Create root
Node* root = nullptr; //Create root node

//Change location in terminal
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    //set location to x, y
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//Box Menu Options
void box(int xpos, int ypos) {
    //x,y is the location of the center of node.
    //Draws box around the center.
    gotoxy(xpos - 2, ypos + 1);
    wcout << L"╚═══╝";
    gotoxy(xpos - 2, ypos);
    wcout << L"║";
    gotoxy(xpos + 2, ypos);
    wcout << L"║";
    gotoxy(xpos - 2, ypos - 1);
    wcout << L"╔═══╗";

    gotoxy(xpos, ypos);
}

//Box a node
void BoxNode(int xpos, int ypos) {
    //x,y is the location of the center of node.
    //Draws box around the center.
    gotoxy(xpos - 2, ypos + 1);
    wcout << L"╚════╝";
    gotoxy(xpos - 2, ypos);
    wcout << L"║";
    gotoxy(xpos + 3, ypos);
    wcout << L"║";
    gotoxy(xpos - 2, ypos - 1);
    wcout << L"╔════╗";

    gotoxy(xpos, ypos);
}

//Erase Node
void unBoxNode(int x, int y) {
    //x,y is the location of the center of node.
    gotoxy(x - 2, y + 1);
    wcout << L"      ";
    gotoxy(x - 2, y);
    wcout << L"      ";
    gotoxy(x - 2, y - 1);
    wcout << L"      ";
}

//Draw branch
void branch(int x, int y, int xx, int yy, int s) {
    //x,y is the center of starting node
    //xx,yy is the center of destination node
    yy -= 2;//makes sure line doesn't go all the way through the center

    gotoxy(x, y);//go to starting node location

    //if the distination node is on the right, start on the right side of the starting node.
    if (x < xx) {
        x += 3;
    }
    //if the destination node is on the left, start on the left side of the starting node
    else {
        x -= 2;
    }
    //draws ─ until reaches x position of destination node, adds ┐ to the end(travelling right)
    while (x < xx) {
        x = x + 1;
        gotoxy(x, y);
        wcout << L"─";
        Sleep(s);
        if (x == (xx)) {
            gotoxy(x, y);
            wcout << L'┐';
        }
    }
    //draws ─ until reaches x position of destination node, adds ┌ to the end(travelling left)
    while (xx < x) {
        x = x - 1;
        gotoxy(x, y);
        wcout << L"─";
        Sleep(s);
        if (x == (xx)) {
            gotoxy(x, y);
            wcout << L'┌';
        }
    }

    //draws │ until reachs y position of destination node(travelling down);
    while (yy > y) {
        y = y + 1;
        gotoxy(x, y);
        wcout << L"│";
        Sleep(s);
    }

    //draws │ until reachs y position of destination node(travelling up);
    while (yy < y) {
        y = y - 1;
        gotoxy(x, y);
        wcout << L"│";
        Sleep(s);
    }
}

//Erase branch
void unbranch(int x, int y, int xx, int yy) {
    //Same logic as "branch" method, refer to this function for further commentation.
    //Instead of lines, it draws spaces to erase the branches that were drawn
    yy -= 2;
    gotoxy(x, y);
    if (x < xx) {
        x += 3;
    }
    else {
        x -= 2;
    }
    while (x < xx) {
        x = x + 1;
        gotoxy(x, y);
        wcout << L" ";

    }
    while (xx < x) {
        x = x - 1;
        gotoxy(x, y);
        wcout << L" ";
    }
    while (yy > y) {
        y = y + 1;
        gotoxy(x, y);
        wcout << L" ";
    }
    while (yy < y) {
        y = y - 1;
        gotoxy(x, y);
        wcout << L" ";
    }
}

//Welcome the user
void welcome(int x, int y) {
    //go to the middle of the screen - half the size of our welcome message
    //write welcome, then delete it

    x = (x / 2) - 3;
    y = (y / 2);
    gotoxy(x, y);
    wcout << "W";
    Sleep(200);
    wcout << "e";
    Sleep(200);
    wcout << "l";
    Sleep(200);
    wcout << "c";
    Sleep(200);
    wcout << "o";
    Sleep(200);
    wcout << "m";
    Sleep(200);
    wcout << "e";
    Sleep(200);
    wcout << "!";
    Sleep(800);
    wcout << "\b \b";
    Sleep(100);
    wcout << "\b \b";
    Sleep(100);
    wcout << "\b \b";
    Sleep(100);
    wcout << "\b \b";
    Sleep(100);
    wcout << "\b \b";
    Sleep(100);
    wcout << "\b \b";
    Sleep(100);
    wcout << "\b \b";
    Sleep(100);
    wcout << "\b \b";

    gotoxy(0, 0);
}

//Draw the menu
void menu() {
    //draw O
    gotoxy(3, 2);
    wcout << 'O';
    box(3, 2);
    gotoxy(7, 2);
    wcout << "Open File";

    //draw I
    gotoxy(3, 6);
    wcout << 'I';
    box(3, 6);
    gotoxy(7, 6);
    wcout << "Insert";

    //draw D
    gotoxy(3, 10);
    wcout << 'D';
    box(3, 10);
    gotoxy(7, 10);
    wcout << "Delete";

    //draw <
    gotoxy(3, 14);
    wcout << "<";
    box(3, 14);
    gotoxy(7, 14);
    wcout << "Dec Speed";

    //draw N
    gotoxy(20, 2);
    wcout << 'N';
    box(20, 2);
    gotoxy(24, 2);
    wcout << "NLR";

    //draw L
    gotoxy(20, 6);
    wcout << 'L';
    box(20, 6);
    gotoxy(24, 6);
    wcout << "LNR";

    //draw R
    gotoxy(20, 10);
    wcout << 'R';
    box(20, 10);
    gotoxy(24, 10);
    wcout << "LRN";

    //draw >
    gotoxy(20, 14);
    wcout << '>';
    box(20, 14);
    gotoxy(24, 14);
    wcout << "Inc Speed";

    //draw the menu border
    int x = 34;
    int y = 0;
    while (16 > y) {
        gotoxy(x, y);
        wcout << L"║";
        y = y + 1;
    }

    gotoxy(0, 16);
    wcout << L"══════════════════════════════════╝";

    //draw message box border
    gotoxy(43, 1);
    wcout << L"╚══════════════════════════════════════════════════════════════════╝";
    gotoxy(43, 0);
    wcout << L"║";
    gotoxy(110, 0);
    wcout << L"║";

    gotoxy(0, 25);
}

//Write a message on the message box
void message(wstring message) {
    //erase previous message
    //print new message
    gotoxy(47, 0);
    wcout << "                                                               ";
    gotoxy(76 - (message.length() / 2), 0);
    wcout << message;
    gotoxy(0, 25);
}

//create a new node and return it
Node* newNode(int v,int x, int y, int s) {
    Node* n = new Node();//create node
    n->value = v;//set the value to argument
    n->left = nullptr;//set children to nullptr
    n->right = nullptr;
    //draw the node on terminal
    gotoxy(x, y);
    wcout << v;
   BoxNode(x, y);
    Sleep(s);
    return n;//return node
}

//Draw a tree
void DisplayTree(Node* r, int xpos, int ypos, int width, string t, int s) {
    //return if node is nullptr
    if (r == nullptr) {
        return;
    }


    //if displaying tree in NLR
    if (t == "NLR") {
        //draw node
        //if node has children, draw branches
        gotoxy(xpos, ypos);
        wcout << r->value;
        BoxNode(xpos, ypos);
        Sleep(s);
        if (r->left != nullptr) {
            branch(xpos, ypos, xpos - width, ypos + 3, s / 10);
        }
        if (r->right != nullptr) {
            branch(xpos, ypos, xpos + width, ypos + 3, s / 10);
        }
    }

    //call DisplayTree function for the left node
    DisplayTree(r->left, xpos - width, ypos + 3, (width / 2) + 3, t, s);

    //if displaying tree in LNR
    if (t == "LNR") {
        //draw node
        //if node has children, draw branches
        gotoxy(xpos, ypos);
        wcout << r->value;
        BoxNode(xpos, ypos);
        Sleep(s);
        if (r->left != nullptr) {
            branch(xpos, ypos, xpos - width, ypos + 3, s / 10);
        }
        if (r->right != nullptr) {
            branch(xpos, ypos, xpos + width, ypos + 3, s / 10);
        }
    }

    //call DisplayTree function for the right node
    DisplayTree(r->right, xpos + width, ypos + 3, (width / 2) + 3, t, s);


    //if displaying tree in LRN
    if (t == "LRN") {
        //draw node
        //if node has children, draw branches
        gotoxy(xpos, ypos);
        wcout << r->value;
        BoxNode(xpos, ypos);
        Sleep(s);
        if (r->left != nullptr) {
            branch(xpos, ypos, xpos - width, ypos + 3, s / 10);
        }
        if (r->right != nullptr) {
            branch(xpos, ypos, xpos + width, ypos + 3, s / 10);
        }
    }

    gotoxy(0, 0);

}

//return NLR order
wstring NLR(Node* n) {
    wstring order;
    order += to_wstring(n->value) + L" "; //add value to string
    if (n->left != nullptr) {//if the left node isn't a nullptr, add to string the string returned from recalling the same function with the left node
        order += NLR(n->left);
    }
    if (n->right != nullptr) {//if the right node isn't a nullptr, add to string the string returned from recalling the same function with the right node
        order += NLR(n->right);
    }
    return order;
}

//return LNR order
wstring LNR(Node* n) {
    wstring order;
    if (n->left != nullptr) {//if the left node isn't a nullptr, add to string the string returned from recalling the same function with the left node
        order += LNR(n->left);
    }
    order += to_wstring(n->value) + L" "; //add value to string
    if (n->right != nullptr) {//if the right node isn't a nullptr, add to string the string returned from recalling the same function with the right node
        order += LNR(n->right);
    }
    return order;
}

//return LRN order
wstring LRN(Node* n) {
    wstring order;
    if (n->left != nullptr) {//if the left node isn't a nullptr, add to string the string returned from recalling the same function with the left node
        order += LRN(n->left);
    }
    
    if (n->right != nullptr) {//if the right node isn't a nullptr, add to string the string returned from recalling the same function with the right node
        order += LRN(n->right);
    }
    order += to_wstring(n->value) + L" "; //add value to string
    return order;
}

//erase a node and all its children
void eraseFamily(Node* n, int x, int y, int width) {
    //if left node isnt a nullptr, call eraseFamily function with left node
    if (n->left != nullptr) {
        eraseFamily(n->left, x - width, y + 3, (width / 2) + 3);
    }
    //if right node isnt a nullptr, call eraseFamily function with right node
    if (n->right != nullptr) {
        eraseFamily(n->right, x + width, y + 3, (width / 2) + 3);
    }
    //erase box
    //erase branch
    unBoxNode(x, y);
    unbranch(x, y, x - width, y + 3);
    unbranch(x, y, x + width, y + 3);
    
    
}

//insert function
Node* insert(Node* n, int value, int x, int y, int width, int s) {

    //if node is nullptr, create a new node with the value, draw it and return it.
    if (n == nullptr) {
        newBranch = true;
        return newNode(value, x, y, s);
    }

    //if the value is less than the node's value, set the left child of the argument node to the node 
    //that is returned from calling the insert function with the left child and the same value
    if (value < n->value) {
        n->left = insert(n->left, value,x-width,y+3, (width / 2) + 3, s);
    }


    //if the value is greater than the node's value, set the right child of the argument node to the node
    //that is returned from calling the insert function with the right child and the same value.
    else if (value >= n->value) {
        n->right = insert(n->right, value, x+width, y+3, (width / 2) + 3, s);
    }

    //if a new node was created, draw branches
    if (newBranch) {
        if (n->left != nullptr) {
            branch(x, y, x - width, y + 3, s / 10);
        }
        if (n->right != nullptr) {
            branch(x, y, x + width, y + 3, s / 10);
        }
        newBranch = false;
    }
  
    
    return n;
}

//delete node
Node* deleteNode(Node* n, int value, int x, int y, int width) {
    //if the node is a nullptr, return nullptr
    if (n == nullptr) {
        return nullptr;
    }

    //if the value you are looking for is equal to the value of the node
    if (n->value == value) {
        //erase the node and all its children
        eraseFamily(n, x, y, width);
        //let the parent know child was deleted
        newBranch = true;

        //*******************No child case*************************************
        //if height is 0, return nullptr
        if (n->left == nullptr && n->right == nullptr) {
            return nullptr;
        }

        //******************One child cases****************************************
        //if left node is nullptr, return the right child of the node.
        else if (n->left == nullptr) {
            Node* temp = n->right;
            free(n);
            return temp;
        }

        //if right node is nullptr, return the left child of the node.
        else if (n->right == nullptr) {
            Node* temp = n->left;
            free(n);
            return temp;
        }

        //*******************Two child Case***********************
        //else
        else {
            Node* N = n->left;//create a new node and set it equal to the left child of the node
            while (N->right != nullptr) {//while the new node has a right child
                N = N->right;//set new node equal to the right child of the new node.
            }

            n->value = N->value;//set the value of node to the value of new node.

            n->left = deleteNode(n->left, N->value, x - width, y + 3, (width / 2) + 3);//set the left child of node to the value that is returned when calling the delete
                                                      //function with the left child and new node's value as argument.
        }
    }

    //if the value you are looking for is less that the value of the node, call the delete function with the left child and the value as its argument
    if (value < n->value) {
        n->left = deleteNode(n->left, value, x - width, y + 3, (width / 2) + 3);
    }
    //if the value you are looking for is greater than the value of the node, call the delete function with the right child and the value as its argument.
    else if (value > n->value) {
        n->right = deleteNode(n->right, value, x + width, y + 3, (width / 2) + 3);
    }

    //if child was deleted, delete branches
     if (newBranch) {
        if (n->left == nullptr) {
            unbranch(x, y, x - width, y + 3);
        }
        if (n->right == nullptr) {
            unbranch(x, y, x + width, y + 3);
        }
        
        newBranch = false;
    }
    
   
    //return node
    return n;
  
}

//Add values from a file to tree
void readFile(wstring location) {
    ifstream file;//initialize ifstream to read a file
    message(L"Opening " + location);
    Sleep(1000);
    file.open(location);//open input.txt
    string line;//holds line data
    int value;//holds the value of the line

    //if file couldn't be opened
    if (!file.is_open()) {
        message(L"Could not open "+location);
        Sleep(1000);
    }
    //else file opened successfully
    else {
        message(L"Successfully Opened C://temp//input.txt");
        Sleep(1000);
        message(L"Displaying Tree: NLR");
        getline(file, line);//get line and store it in line
        value = stoi(line);
        while (value != -1) {
            root = insert(root, value,76,4,15,0);//insert number to the tree
            wstring msg = L"Added " + to_wstring(value) + L" to the tree!";
            message(msg);
            Sleep(500);
            getline(file, line);//get line and store it in line
            value = stoi(line);
        }
        message(L"NLR: " + NLR(root));
        
    }
}

//driver class
int main(int argc, const char* argv[]) {
    //allow console to print special symbols/ASCII characters
    _setmode(_fileno(stdout), _O_U16TEXT);

    //Used for getting screen size
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;//width of console
    int rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;//height of console

    system("color b");//set the console color to light blue
    welcome(columns, rows);//display welcome screen
    menu();//draw the menus
    message(L"Press 'q' To Exit.");//let the user know they can exit if they press q
    Sleep(1200);
    
    //make a tree from the values in input.txt
    readFile(L"C://temp//input.txt");
    
    //********user interface********

    //user's input
    char input;
    //speed of actions
    int speed = 200;
    do{
        input = _getch();//get user input

        //if i pressed, insert value to tree
        if (input == 'i') {
            gotoxy(0, 17);
            wcout << "Insert:";
            int value;
            cin >> value;
            gotoxy(0, 17);
            wcout << L"                              ";
            root = insert(root, value, 76, 4, 15, speed);
            gotoxy(0, 17);
            message(L"Inserted " + to_wstring(value));
        }

        //if d pressed, delete value from tree
        if (input == 'd') {
            gotoxy(0, 17);
            wcout << "Delete:";
            int value;
            cin >> value;
            gotoxy(0, 17);
            wcout << L"                              ";
            root = deleteNode(root, value, 76, 4, 15);
            DisplayTree(root, 76, 4, 15, "NLR", 0);
            message(L"Deleted " + to_wstring(value));
        }

        //if o pressed, add the values from the file user provides
        if (input == 'o') {
            gotoxy(0, 17);
            wcout << "File location: ";
            wstring location;
            wcin >> location;
            gotoxy(0, 17);
            wcout << L"                                         ";
            readFile(location);
        }

        //if n pressed, display tree in NLR
        if (input == 'n') {
            message(L"NLR: " + NLR(root));
            eraseFamily(root, 76, 4, 15);
            DisplayTree(root, 76, 4, 15, "NLR", speed);
        }

        //if l pressed, display tree in LNR
        if (input == 'l') {
            message(L"LNR: " + LNR(root));
            eraseFamily(root, 76, 4, 15);
            DisplayTree(root, 76, 4, 15, "LNR", speed);
        }

        //if r pressed, display tree in LRN
        if (input == 'r') {
            message(L"LRN: " + LRN(root));
            eraseFamily(root, 76, 4, 15);
            DisplayTree(root, 76, 4, 15, "LRN", speed);
        }
        
        //if right arrow pressed, decrease speed by increasing the sleep time
        if (input == 77) {
            if (speed - 100 >= 0) {
                speed -= 100;
            }
            message(L"Speed: " + to_wstring((1500-speed)/15));
        }

        //if left arrow pressed, increase pseed by decreasing the sleep time
        if (input == 75) {
            if (speed + 100 <= 1500) {
                speed += 100;
            }
            message(L"Speed: " + to_wstring((1500-speed)/15));
        }
        
 
    } while (input != 'q');
    exit(0);
   

       
       


     //DisplayTree(root, columns/2, rows/3, 20, "NLR", 1000);
     
    




    return 0;
}
