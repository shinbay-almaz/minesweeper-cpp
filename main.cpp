#include <iostream>
#include <vector> 
#include <random>
#include <stdlib.h>


using namespace std;


struct Cell {
	bool isOpened = false;
	bool isMine = false;
};

int rows, cols, mines;
vector <vector <Cell>> gameBoard;
bool gameOver;

void initializeGameBoard() {
	gameBoard.clear();
	for (int i = 0; i < rows; i++) {
		vector <Cell> gameBoardRow(cols);
		gameBoard.push_back(gameBoardRow);
	}
}

void generateMines() {
	for (int i = 1; i <= mines; ) {
		int rand_x = rand() % rows;
		int rand_y = rand() % cols;
		if (!gameBoard[rand_x][rand_y].isMine) {
			gameBoard[rand_x][rand_y].isMine = true;
			i++;
		}
	}
}

void generateGameBoard(int _rows, int _cols, int _mines) {
	rows = _rows, cols = _cols, mines = _mines;
	initializeGameBoard();
	generateMines();
}

bool isValidCell(int x, int y) {
	return (x >= 0 && x < rows && y >= 0 && y < cols);
}

int checkNeighbours(int x, int y) {
	int neighbourMines = 0;
	for (int dx = -1; dx <= 1; dx++) {
		for (int dy = -1; dy <= 1; dy++) {
			if (!dx && !dy) continue;
			int nx = x + dx;
			int ny = y + dy;
			if (isValidCell(nx, ny)) {
				neighbourMines += gameBoard[nx][ny].isMine;
			}
		}
	}
	return neighbourMines;
}

void printCurrentGameBoard() {
	cout << "     ";
	for (int i = 0; i < cols; i++) {
		printf("%3d", i);	
	}
	cout << "\n\n";
	for (int i = 0; i < rows; i++) {
		printf("%4d ", i);
		for (int j = 0; j < cols; j++) {
			if (gameBoard[i][j].isOpened) {
				cout << "  " << checkNeighbours(i, j);
			} else {
				cout << "  _";
			}
		}
		cout << '\n';
	}
	cout << '\n';
}

void openCells(int x, int y) {
	if (gameBoard[x][y].isMine) {
		gameOver = true;
		return;
	}

	if (gameBoard[x][y].isOpened) {
		return;
	}

	gameBoard[x][y].isOpened = true;

	if (checkNeighbours(x, y) > 0) {
		return;
	}

	for (int dx = -1; dx <= 1; dx++) {
		for (int dy = -1; dy <= 1; dy++) {
			if (!dx & !dy) continue;
			int nx = x + dx;
			int ny = y + dy;
			if (isValidCell(nx, ny)) {
				openCells(nx, ny);
			}
		}
	}
}

bool openCell(int x, int y) {
	if (!isValidCell(x, y)) {
		return false;
	}
	openCells(x, y);
	return true;
}

void printGameBoard() {
	cout << "    ";
	for (int i = 0; i < cols; i++) {
		printf("%3d", i);	
	}
	cout << "\n\n";
	for (int i = 0; i < rows; i++) {
		printf("%4d ", i);
		for (int j = 0; j < cols; j++) {
			if (gameBoard[i][j].isMine) {
				cout << "  X";
			} else {
				cout << "  " << checkNeighbours(i, j);
			}
		}
		cout << '\n';
	}
	cout << '\n';
}

bool isWinningState() {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (!gameBoard[i][j].isOpened && !gameBoard[i][j].isMine) {
				return false;
			}
		}
	}
	return true;
}

int main() {
	srand(time(0));
	
	bool programIsRunning = true;

	cout << "MINESWEEPER\n\n";

	while (programIsRunning) {
		
		gameOver = false;

		cout << "Please choose a difficulty [1-3]\n";
		cout << "1) Easy (8X10, 10 mines)\n";
		cout << "2) Medium (14X18, 40 mines)\n";
		cout << "3) Hard (20X22, 99 mines)\n\n";
		
		int difficulty;
		cin >> difficulty;

		switch (difficulty) {
			case 1: 
				generateGameBoard(8, 10, 10);
				break;
			case 2:
				generateGameBoard(14, 18, 40);
				break;
			case 3:
				generateGameBoard(20, 24, 99);
				break;
			default:
				cout << "Difficulty must be between 1 and 3.\n";
				continue;
		}

		while (!gameOver && !isWinningState()) {

			printCurrentGameBoard();

			cout << "Please write the coordinate of a cell to open\n";
			
			int x, y;
			cin >> x >> y;

			if (!openCell(x, y)) {
				cout << "Invalid cell\n";
			}
		}
		
		if (gameOver) {
			cout << "\nYou Lose!\n\n";
		} else {
			cout << "\nYou Win!\n\n";
		}

		printGameBoard();

		bool responded = false;

		while (!responded) {
			cout << "\nDo you want to play again? [Y/N]\n\n";

			char c;
			cin >> c;
			switch (c) {
				case 'Y': responded = true; break;
				case 'N': responded = true; programIsRunning = false; break;
				default: {
					cout << "\nPlease write 'Y' or 'N'\n\n";
					break;
				}
			}
		}

	}

}
