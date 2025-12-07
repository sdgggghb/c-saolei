// MineSweeper_s.c : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

#define row 10
#define col 10
#define MINE 10 

int mine_map[row][col] = {0};//基础图,用于后台，0有雷，1无雷
int show_map[row][col] = {0};//用于标记，0未翻开，1已翻开，2标记地雷

void set_mine(void)
{
	srand((unsigned int)time(NULL));
	int count = 0;
	while (count < MINE)
	{
		int i = rand() % row;
		int j = rand() % col;
		if (mine_map[i][j] == 0)//防止重复埋雷
		{
			mine_map[i][j] = 1;
			count++;
		}
	}
}
int count_surround_mine(int i, int j)//用于翻  开后知晓周围八个格子一共的雷数
{
	int count = 0;
	for (int x = -1; x <= 1; x++)
	{
		for (int y = -1; y <= 1; y++)
		{
			if (x == 0 && y == 0)
			{
				continue;
			}
			int ni = x + i;
			int nj = y + j;
			if (ni >= 0 && ni < row && nj >= 0 && nj < col)//防止越界
			{
				if (mine_map[ni][nj] == 1)
					count++;
			}
		}
	}
	return count;
}
void open_cell(int i, int j)
{
	if (i < 0 || i >= row || j < 0 || j >= col || show_map[i][j] == 1 || mine_map[i][j] == 1)//越界，雷，已翻开
	{
		return;//boom!!!
	}

	show_map[i][j] = 1;
	int mine_count = count_surround_mine(i, j);//调用上面的函数计算这个格子的周围雷数

	if (mine_count == 0)
	{
		for (int x = -1; x <= 1; x++)
		{
			for (int y = -1; y <= 1; y++)
			{
				if (x != 0 || y != 0)
				{
					open_cell(i + x, j + y);//更新位置啦，因为要开到有数字，so空格子就像被递归一下下吃掉了嘿嘿！这就是递归的魅力，
				}
			}
		}
	}
}
void print_map(void)
{
	printf(" ");
	for (int j = 0; j < col; j++)
	{
		printf("%d", j);//列号，就是每行前的序号，只不过是为了好看点，不然每行前面没1234难看死了
	}
	printf("\n");
	for (int i = 0; i < row; i++)
	{
		printf("%d", i);
		for (int j = 0; j < col; j++)
		{
			if (show_map[i][j] == 0)
			{
				printf("*");
			}
			else if (show_map[i][j] == 2)
			{
				printf("!");
			}
			else
			{
				int mine_count = count_surround_mine(i, j);
				printf("%d", mine_count);
			}
		}
		printf("\n");//每次遍历一行的所有格子后，记得换行
	}
}
int main()
{
	set_mine();//造棋盘，塞雷
	int open_count = 0;
	while (1)//死循环，用break终止
	{
		system("cls");
		print_map();//输出棋盘
		int op, i, j;//操作指令与行列数据
		printf("请输入操作(1 = 翻格子 2 = 标记地雷) 行 列 ; ");
		scanf_s("%d %d %d", &op, &i, &j);
		if (i < 0 || i >= row || j < 0 || j >= col)//依旧越界判断
		{
			printf("坐标越界! 按回车继续...");
			getchar();getchar();
			continue;//越界了那还说啥了，回去吧
		}
		if (op == 1)
		{
			if (mine_map[i][j] == 1)
			{
				printf("踩雷了!游戏结束!\n");
				for (int x = 0; x < row; x++)
				{
					for (int y = 0; y < col; y++)
					{
						if (mine_map[x][y] == 1)
							show_map[x][y] = 1;
					}
				}//好了全图遍历，让你死个明白
				print_map();//好了重来
				break;
			}
			if (show_map[i][j] == 0)
			{
				open_cell(i, j);
				open_count = 0;
				for (int x = 0; x < row; x++)
				{
					for (int y = 0; y < col; y++)
					{
						if (show_map[x][y] == 1)
							open_count++;
					}
				}//胜利代表已翻开=总格子 - 地雷数
				if (open_count == row * col - MINE)
				{
					printf("恭喜胜利！\n");
					break;
				}
			}
		}
		else if (op == 2)
		{
			show_map[i][j] = show_map[i][j] == 2 ? 0 : 2;
		}
	}
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
