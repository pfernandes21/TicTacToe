#include <iostream>
#include <cmath>

using namespace std;

#include "olcConsoleGameEngine.h"

class game_class : public olcConsoleGameEngine
{
public:
	game_class()
	{
		m_sAppName = L"Jogo do galo";
	}

	void Draw_Grid()
	{
		DrawLine(21, 0, 21, 64, PIXEL_SOLID, FG_WHITE);
		DrawLine(43, 0, 43, 64, PIXEL_SOLID, FG_WHITE);
		DrawLine(0, 21, 64, 21, PIXEL_SOLID, FG_WHITE);
		DrawLine(0, 43, 64, 43, PIXEL_SOLID, FG_WHITE);
	}

	int hash(int i)
	{
		if (i == 0) return 0;
		else if (i == 1) return 22;
		else if (i == 2) return 44;
		else return -1;
	}

	void Draw_Pieces()
	{
		int i, j;

		for (i = 0; i < 3; i++)
		{
			for (j = 0; j < 3; j++)
			{
				if (grid[i][j] == 1)
				{
					DrawLine(hash(i) + 1, hash(j) + 1, hash(i) + 19, hash(j) + 19, PIXEL_SOLID, FG_BLUE);
					DrawLine(hash(i) + 1, hash(j) + 19, hash(i) + 19, hash(j) + 1, PIXEL_SOLID, FG_BLUE);
				}

				else if (grid[i][j] == 2)
				{
					DrawCircle(hash(i) + 10, hash(j) + 10, 9, PIXEL_SOLID, FG_RED);
				}

			}
		}
	}

	void Draw_Select()
	{
		int x, y;
		short cor;

		if (player == 1)
			cor = FG_BLUE;
		else if (player == 2)
			cor = FG_RED;

		x = hash(selx);
		y = hash(sely);
		
		DrawLine(x, y, x + 20, y, PIXEL_SOLID, cor);
		DrawLine(x, y, x, y + 20, PIXEL_SOLID, cor);
		DrawLine(x + 20, y + 20, x, y + 20, PIXEL_SOLID, cor);
		DrawLine(x + 20, y + 20, x + 20, y, PIXEL_SOLID, cor);
	}

	void start()
	{
		int i, j;

		for (i = 0; i < 3; i++)
		{
			for (j = 0; j < 3; j++)
				grid[i][j] = 0;
		}

		player = 1;
		selx = 0;
		sely = 0;
		finish = 0;
		jogadas = 0;
	}

	void end()
	{
		//check linhas
		if (grid[0][0] != 0 && grid[0][0] == grid[1][0] && grid[0][0] == grid[2][0]) finish = 1;
		if (grid[0][1] != 0 && grid[0][1] == grid[1][1] && grid[0][1] == grid[2][1]) finish = 1;
		if (grid[0][2] != 0 && grid[0][2] == grid[1][2] && grid[0][2] == grid[2][2]) finish = 1;

		//check colunas
		if (grid[0][0] != 0 && grid[0][0] == grid[0][1] && grid[0][0] == grid[0][2]) finish = 1;
		if (grid[1][0] != 0 && grid[1][0] == grid[1][1] && grid[1][0] == grid[1][2]) finish = 1;
		if (grid[2][0] != 0 && grid[2][0] == grid[2][1] && grid[2][0] == grid[0][2]) finish = 1;

		//check diagonais
		if (grid[0][0] != 0 && grid[0][0] == grid[1][1] && grid[0][0] == grid[2][2]) finish = 1;
		if (grid[2][0] != 0 && grid[2][0] == grid[1][1] && grid[2][0] == grid[0][2]) finish = 1;

		//check empate
		if (jogadas == 9) finish = 1;

		if (finish == 1) start();
	}

private:
	int grid[3][3]; //0 - quadrado vazio, 1 - quadrado com cruz, 2 - quadrado com bola 
	int player; //player 1 ou 2
	int selx, sely; //coordenadas quadrado selecionado
	int finish, jogadas;

protected:
	// Called by olcConsoleGameEngine
	virtual bool OnUserCreate()
	{
		start();
		return true;
	}

	// Called by olcConsoleGameEngine
	virtual bool OnUserUpdate(float fElapsedTime)
	{
		//Desenhar a grelha
		Fill(0, 0, ScreenWidth(), ScreenHeight(), L' ', BG_BLACK);
		Draw_Grid();

		//Desenhar as peças
		Draw_Pieces();

		//Interacao com teclas
		if (player == 1)
		{
			if (m_keys[VK_UP].bPressed && sely > 0)
			{
				sely--;
			}
			if (m_keys[VK_LEFT].bPressed && selx > 0)
			{
				selx--;
			}
			if (m_keys[VK_RIGHT].bPressed && selx < 2)
			{
				selx++;
			}
			if (m_keys[VK_DOWN].bPressed && sely < 2)
			{
				sely++;
			}
			if (m_keys[VK_RETURN].bPressed && grid[selx][sely] == 0)
			{
				jogadas++;

				if (player == 1)
				{
					grid[selx][sely] = 1;
					player = 2;
				}
				else if (player == 2)
				{
					grid[selx][sely] = 2;
					player = 1;
				}
			}
		}
		else if (player == 2)
		{
			if (m_keys[0x57].bPressed && sely > 0)
			{
				sely--;
			}
			if (m_keys[0x41].bPressed && selx > 0)
			{
				selx--;
			}
			if (m_keys[0x44].bPressed && selx < 2)
			{
				selx++;
			}
			if (m_keys[0x53].bPressed && sely < 2)
			{
				sely++;
			}
			if (m_keys[VK_SPACE].bPressed && grid[selx][sely] == 0)
			{
				jogadas++;

				if (player == 1)
				{
					grid[selx][sely] = 1;
					player = 2;
				}
				else if (player == 2)
				{
					grid[selx][sely] = 2;
					player = 1;
				}
			}
		}

		//Desenhar quadrado de selecao
		Draw_Select();

		//Se o jogo acabou
		end();

		return true;
	}
};

int main()
{
	game_class game;
	game.ConstructConsole(65, 65, 10, 10);
	game.Start();

	return 0;
}