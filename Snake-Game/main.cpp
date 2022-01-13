#include <iostream>
#include <cstdio>
#include <conio.h>
#include <windows.h>
using namespace std;

bool gameOver;
const int width = 40.0;
const int height = 12.0;
int x, y, fruitX, fruitY, score;
enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;
int tailX[100], tailY[100];
int nTail;

void input();
void draw();
void logic();
void setup();

//============ main program =============
int main()
{
    setup();
    while (!gameOver)
    {
    draw();
    input();
    logic();

//    Sleep(10);
    }

    return 0;
}

//========= Function Definition =========
void setup()
{
  gameOver = false;
  dir = STOP;
  x = width / 2;
  y = height / 2;
  fruitX = rand() % width;
  fruitY = rand() % height;
  score = 0;
}

void input()
{
  if (_kbhit())
  {
      switch (_getch())
      {
      case 'a':
         dir = LEFT;
         break;

      case 'd':
         dir = RIGHT;
         break;

      case 'w':
         dir = UP;
         break;

      case 's':
         dir = DOWN;
         break;

      case 'x':
         gameOver = true;
         break;
      }
  }
}

void draw(){
     system("cls");
     for (int i = 0; i < width; i++)
        cout << "=";
     cout << "\n";

     for (int i = 0; i < height; i++)
     {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)
              cout << "#";
            if (i == y && j == x)
              cout << "O";
            else if (i == fruitY && j == fruitX)
              cout << "F";
            else
              {
                  bool print = false;
                  for (int k = 0; k < nTail; k++)
                  {

                      if (tailX[k] == j && tailY[k] == i)
                      {
                          cout << "o";
                          print = true;
                      }
                  }
                  if (!print)
                    cout << " ";
              }
            if (j == width - 1)
                cout << "#";
        }
        cout << "\n";
     }

     for (int i = 0; i < width; i++)
        cout << "=";
     cout << "\n";

  cout << "Score: " << score << "\n";
}

void logic()
{
   int prevX = tailX[0];
   int prevY = tailY[0];
   int prev2X, prev2Y;
   tailX[0] = x;
   tailY[0] = y;
   for (int i = 1; i < nTail; i++)
   {
       prev2X = tailX[i];
       prev2Y = tailY[i];
       tailX[i] = prevX;
       tailY[i] = prevY;
       prevX = prev2X;
       prevY = prev2Y;
   }
   switch(dir)
   {
    case LEFT:
      x--;
      break;

    case RIGHT:
      x++;
      break;

    case UP:
      y--;
      break;

    case DOWN:
      y++;
      break;
   }
   if (x > width || x < 0 || y > height || y < 0)
     gameOver = true;
   if (x == fruitX && y == fruitY)
   {
     score += 10;
     fruitX = rand() % width;
     fruitY = rand() % height;
     nTail++;
   }

}
