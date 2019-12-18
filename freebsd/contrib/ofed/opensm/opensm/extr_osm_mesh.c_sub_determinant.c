#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  lash_t ;

/* Variables and functions */
 scalar_t__ determinant (int /*<<< orphan*/ *,int,int,int***,int*) ; 
 int /*<<< orphan*/  free (int*) ; 
 int*** pm_alloc (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  pm_free (int***,int) ; 
 int* poly_alloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int sub_determinant(lash_t *p_lash, int n, int l, int row, int col,
			   int ***matrix, int **poly)
{
	int ret = -1;
	int ***m = NULL;
	int *p = NULL;
	int i, j, k, x, y;
	int rank = l - 1;

	do {
		if (!(p = poly_alloc(p_lash, n))) {
			break;
		}

		if (rank <= 0) {
			p[0] = 1;
			ret = 0;
			break;
		}

		if (!(m = pm_alloc(p_lash, rank, n))) {
			free(p);
			p = NULL;
			break;
		}

		x = 0;
		for (i = 0; i < l; i++) {
			if (i == row)
				continue;

			y = 0;
			for (j = 0; j < l; j++) {
				if (j == col)
					continue;

				for (k = 0; k <= n; k++)
					m[x][y][k] = matrix[i][j][k];

				y++;
			}
			x++;
		}

		if (determinant(p_lash, n, rank, m, p)) {
			free(p);
			p = NULL;
			break;
		}

		ret = 0;
	} while (0);

	pm_free(m, rank);
	*poly = p;
	return ret;
}