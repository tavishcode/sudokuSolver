/*
 * lab5.cpp
 *
 *  Created on: Mar 14, 2016
 *      Author: Tavish
 */
/*
 * skeleton.cpp
 *
 * written by Dai Zuozhuo and Yu Chen for the course comp2011, HKUST.
 * contact via: ychenbh@ust.hk
 *
 *
 * This piece of code is the skeleton code for Lab 5.
 * Complete the following code and finish the task specified.
 * In order to use this file in eclipse, just create a normal
 * project and add a source file as usual. Copy and paste the
 * entire file to Eclipse.
 *
 * Please don't open it by double-click the file at CSE lab,
 * it will open the Microsoft Visual Studio Instead.
 *
 * You can add more functions into the file.
 */

#include <iostream>
#include <cstdlib>
using namespace std;

void reset(bool vis[9]) {
    for (int i = 0; i < 9; i++) {
        vis[i] = false;
    }
}

//randomly set n positions on board to empty cell '.'
void initializeBoard(char board[][9], int n) {
    int row, col;
    for (int i = 0; i < n; i++) {
        do {
            row = rand() % 9;
            col = rand() % 9;
        } while (board[row][col] == '.');
        board[row][col] = '.';
    }
}

//checks if the Sudoku is valid
bool isValidSudoku(const char board[][9]) {
    bool vis[9];
    reset(vis);
    for (int i = 0; i < 9; i++) {
        reset(vis);
        for (int j = 0; j < 9; j++) {
            if (board[i][j] == '.')
                continue;
            int num = board[i][j] - '1';
            if (vis[num])
                return false;
            else
                vis[num] = true;
        }
        reset(vis);
        for (int j = 0; j < 9; j++) {
            if (board[j][i] == '.')
                continue;
            int num = board[j][i] - '1';
            if (vis[num])
                return false;
            else
                vis[num] = true;
        }
    }
    for (int k = 0; k < 9; k++) {
        reset(vis);
        int i = k / 3, j = k % 3;
        for (int l = 0; l < 9; l++) {
            char pos = board[i * 3 + l / 3][j * 3 + l % 3];
            if (pos == '.')
                continue;
            int num = pos - '1';
            if (vis[num])
                return false;
            else
                vis[num] = true;
        }

    }
    return true;
}

//checks if the Sudoku is solved
bool isSolvedSudoku(const char board[][9]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (board[i][j] == '.')
                return false;
        }
    }
    return isValidSudoku(board);
}

//prints the Sudoku value and board grid line
void printBoard(const char board[][9]) {
    for (int i = 0; i < 9; i++) {
        if (i % 3 == 0) {
            for (int k = 0; k < 22; k++)
                cout << "-";
            cout << endl;
        }
        for (int j = 0; j < 9; j++) {
            if (j % 3 == 0)
                cout << "|";
            cout << board[i][j] << " ";
        }
        cout << "|" << endl;
    }
    for (int k = 0; k < 22; k++)
        cout << "-";
    cout << endl;
}

// TODO: Define and implement a recursive helper function
// e.g. bool solvesSudokuHelper(char board[][9], ...)
// the helper function will solve Sudoku by recursion
// if Sudoku is solved, return true, otherwise return false
bool solveSudokuHelper(char board[][9],int num_start)
{
	if(isSolvedSudoku(board))
		return true;
	if(board[num_start/9][num_start%9]=='.')
	{
		for(int num_check=1;num_check<10;num_check++)
		{
			board[num_start/9][num_start%9]=num_check+'0';
			if(!isValidSudoku(board))
			{
				board[num_start/9][num_start%9]='.';
				continue;
			}
			cout<<"Fill cell "<<(num_start/9)+1<<", "<<(num_start%9)+1<<" with "<<num_check<<endl;
			if(solveSudokuHelper(board,num_start+1))
			{
				return true;
			}
			board[num_start/9][num_start%9]='.';
		}
		cout<<"Backtrack"<<endl;
		return false;
	}
	if(solveSudokuHelper(board,num_start+1))
	{
		return true;
	}
	return false;
}


//TODO: Solve Sudoku by calling a recursive helper function.
void solveSudoku(char board[][9]) {
	/*TODO:
	 * Call a helper function, e.g. solveSudokuHelper(board,...)
	 * the helper function solves Sudoku by recursion
	 */
	solveSudokuHelper(board,0);
	cout<<"results"<<endl;
	printBoard(board);
}

int main() {
    char board[][9] = { '5', '3', '4', '6', '7', '8', '9', '1', '2', '6', '7',
            '2', '1', '9', '5', '3', '4', '8', '1', '9', '8', '3', '4', '2',
            '5', '6', '7', '8', '5', '9', '7', '6', '1', '4', '2', '3', '4',
            '2', '6', '8', '5', '3', '7', '9', '1', '7', '1', '3', '9', '2',
            '4', '8', '5', '6', '9', '6', '1', '5', '3', '7', '2', '8', '4',
            '2', '8', '7', '4', '1', '9', '6', '3', '5', '3', '4', '5', '2',
            '8', '6', '1', '7', '9' };
    int empty;
    cout << "Input the number of empty cells to initialize board" << endl;
    cin >> empty;
    initializeBoard(board, empty);
    cout << "Finish initialize board" << endl;
    printBoard(board);

    solveSudoku(board);//This is the function you need to implement.

    return 0;
}



