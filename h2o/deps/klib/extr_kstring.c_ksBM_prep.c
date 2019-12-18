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
typedef  size_t ubyte_t ;

/* Variables and functions */
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  free (int*) ; 

__attribute__((used)) static int *ksBM_prep(const ubyte_t *pat, int m)
{
	int i, *suff, *prep, *bmGs, *bmBc;
	prep = (int*)calloc(m + 256, sizeof(int));
	bmGs = prep; bmBc = prep + m;
	{ // preBmBc()
		for (i = 0; i < 256; ++i) bmBc[i] = m;
		for (i = 0; i < m - 1; ++i) bmBc[pat[i]] = m - i - 1;
	}
	suff = (int*)calloc(m, sizeof(int));
	{ // suffixes()
		int f = 0, g;
		suff[m - 1] = m;
		g = m - 1;
		for (i = m - 2; i >= 0; --i) {
			if (i > g && suff[i + m - 1 - f] < i - g)
				suff[i] = suff[i + m - 1 - f];
			else {
				if (i < g) g = i;
				f = i;
				while (g >= 0 && pat[g] == pat[g + m - 1 - f]) --g;
				suff[i] = f - g;
			}
		}
	}
	{ // preBmGs()
		int j = 0;
		for (i = 0; i < m; ++i) bmGs[i] = m;
		for (i = m - 1; i >= 0; --i)
			if (suff[i] == i + 1)
				for (; j < m - 1 - i; ++j)
					if (bmGs[j] == m)
						bmGs[j] = m - 1 - i;
		for (i = 0; i <= m - 2; ++i)
			bmGs[m - 1 - suff[i]] = m - 1 - i;
	}
	free(suff);
	return prep;
}