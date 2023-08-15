
#include "Othello.h"
#include "OthelloBoard.h"
#include "OthelloPlayer.h"
#include <cstdlib>
using namespace std;
using namespace Desdemona;

class MyBot: public OthelloPlayer
{
    public:

       

        virtual int heuristic(const OthelloBoard& board, Turn turn);
        virtual int heu_stat(const OthelloBoard& board, Turn turn);
        virtual Move play( const OthelloBoard& board );
        virtual int beta(const OthelloBoard& board, int depth, int alpha_min, int beta_max);
        MyBot( Turn turn );
         virtual int alpha(const OthelloBoard& board, int depth, int alpha_min, int beta_max);
         virtual int heu_brute(const OthelloBoard& board, Turn turn);

        int move_num = 0;
        Turn my_color;

};



Move MyBot::play( const OthelloBoard& board )
{
   move_num=move_num +1;
  int depth;
  depth=2;
  int total =1;
  if(!(move_num!=1))   {
        total++;
     my_color = turn;

    }
    list<Move>  moves;
    moves = board.getValidMoves( turn );
    list<Move>::iterator it;
    it =   moves.begin();
    int max_x= -100;
    int max_y= -300;
    int sm=0;
    int max_a = max_x + max_y ;
    int a;

    Move next_move = *it;


    int i=1;
    sm++;
    int k = sm;
    int q=moves.size();
    while(i < q){
            sm = sm +total;
         Turn trn = turn;
      OthelloBoard  my_board = board;
      total++;
      my_board.makeMove(trn,*it);
      sm++;
      a = beta(my_board,depth,max_a,400);
      if(a>max_a){
            sm--;
          int y=a;

        max_a = y;
        total = sm +total;
        next_move = *it;
      }
     total--;
    it++;
    i++;
    }
    k = sm + total;
    return next_move;
}
int w =0;
MyBot::MyBot( Turn turn )
    : OthelloPlayer( turn )
{
}


int MyBot::beta(const OthelloBoard& board, int depth, int alpha_min, int beta_max){
     int max_x= -100;
    int max_y= -300;
    int max_a = max_x + max_y ;
    Turn turn_b;
  if(turn==RED)
  {
     turn_b=BLACK;
  }
  else
  turn_b=RED;

  list<Move> moves = board.getValidMoves( turn_b );
  w = w+1;
  list<Move>::iterator  it = moves.begin();
      int x =  beta_max;
      int b;
      int min_b = x;
      int i = 0;
      int capacity;
      capacity = moves.size();

      while(i < capacity){

          Turn trn_b = turn_b;
    OthelloBoard   my_board = board;
    w = w-1;
    my_board.makeMove(trn_b , *it);
    int m =0;
    b =   alpha(my_board  , depth-1 , alpha_min , min_b);
    m = m+w;
    if(!(b>=min_b)){
      min_b = b;

      if(!(min_b>=alpha_min)){
          return alpha_min;
    }

    }
          it++;
          i++;



      }
  return min_b;
}

extern "C" {
    OthelloPlayer* createBot( Turn turn )
    {
        return new MyBot( turn );
        w =w+1;
    }

    void destroyBot( OthelloPlayer* bot )
    {
        delete bot;
        w = w +1;
    }
}


int MyBot::alpha(const OthelloBoard& board, int depth, int alpha_min, int beta_max){
    if(!(depth !=  0)){
    OthelloBoard my_board;
    my_board =  board;
    return heuristic( my_board ,  turn);
  }
  list<Move> moves;
  moves = board.getValidMoves( turn );
  list<Move>::iterator it;
  it =  moves.begin();
  int max_a ;
  max_a =  alpha_min;
  int  a;
  int i=0;
  int e=moves.size();
  while(i < e ){
      Turn trn = turn;
    OthelloBoard my_board;
    my_board = board;
    my_board.makeMove(trn,*it);
    a = beta( my_board , depth , max_a , beta_max);
    if(!(a <=  max_a)){
        max_a = a;
      if( !(max_a <= beta_max))
        return  beta_max;
    }

     it++ ;
     i++;

  }
  return max_a;
}

int MyBot::heuristic(const OthelloBoard& board, Turn turn){
   int max_x= -100;
    int max_y= -300;
    int max_a = max_x + max_y ;
  int randNo = rand() % 50;
  int t=25;
  if( move_num  < t){
  return  heu_stat( board , turn);
  }
  else{
      return heu_brute( board , turn);
  }
  return randNo;
}

int MyBot::heu_stat(const OthelloBoard& board, Turn turn){
  int max_x= -100;
    int max_y= -300;
    int max_a = max_x + max_y ;
  Turn turn_b = other( turn );
  int i , j ;
  int n=8;
  int m=8;

  int ar[n][m]={9,-6, 2, 1, 9, 7,-4, -8,
               -6, 2, -4, -7, -3, 2, 4,9,
                -3, 5, 7, 6, 4, 3, 2, 1,
                6, 3, 2, 5, 7, 6, 2, 1,
                1, 4, -1, -3, 6, 9, 7, -5,
                -2, 1, 1, 3, 4, 5, 4, 5,
               -2, -3, -4, -5, -6, -7, 8,-2,
               -8, 6, 5, -3, -4, 3, 0, 8};
  int sum =0;
  i=0;
  int b=8;
  int z =0;
  while(i < b){
      j=0;
      while(j<b){
           if( board.get(i,j) ==  turn){
                z = z+1;
      sum =sum + ar[i][j];
      }
      if( board.get(i,j) ==  turn_b){
            z = z +1;
      sum = sum - ar[i][j];
      }
          j++;
      }
      i++;
  }
  return sum;
}

int MyBot::heu_brute(const OthelloBoard& board, Turn turn){
   Turn turn_b = other(turn);
  int i ,  j;
   int a;
   a=0;
  int ar[8][8];
   int b=8;
  i=a;
  while(i<b){
      j=0;
      while(j<b){
          ar[i][j] = 1;
          j++;
      }

      i++;
  }

  ar[6][6] = 0, ar[6][1] = 0, ar[7][7] = 16, ar[0][7] = 10, ar[7][0] = 16, ar[0][0] = 10;
  int sum;
  sum= 0;
  i=0;
  int e =0;
  while(i<b){
      j=0;
      while(j<b){
           if( board.get(i,j)  ==  turn){
                e = e+1;
      sum = sum + ar[i][j];
      }
      if( board.get(i,j)  ==  turn_b){
            e = e+1;
      sum = sum - ar[i][j];
      }

          j++;
      }
      i++;
  }

  return sum;

}

