#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
struct TYPE_2__ {int y; } ;

/* Variables and functions */
 int D_MINIMAL ; 
 scalar_t__ MAX (int,int) ; 
 scalar_t__ UINT_MAX ; 
 TYPE_1__* clist ; 
 int isqrt (int) ; 
 int newcand (int,int,int) ; 
 int search (int*,int,int) ; 

__attribute__((used)) static int
stone(int *a, int n, int *b, int *c, int flags)
{
	int i, k, y, j, l;
	int oldc, tc, oldl, sq;
	u_int numtries, bound;

	if (flags & D_MINIMAL)
		bound = UINT_MAX;
	else {
		sq = isqrt(n);
		bound = MAX(256, sq);
	}

	k = 0;
	c[0] = newcand(0, 0, 0);
	for (i = 1; i <= n; i++) {
		j = a[i];
		if (j == 0)
			continue;
		y = -b[j];
		oldl = 0;
		oldc = c[0];
		numtries = 0;
		do {
			if (y <= clist[oldc].y)
				continue;
			l = search(c, k, y);
			if (l != oldl + 1)
				oldc = c[l - 1];
			if (l <= k) {
				if (clist[c[l]].y <= y)
					continue;
				tc = c[l];
				c[l] = newcand(i, y, oldc);
				oldc = tc;
				oldl = l;
				numtries++;
			} else {
				c[l] = newcand(i, y, oldc);
				k++;
				break;
			}
		} while ((y = b[++j]) > 0 && numtries < bound);
	}
	return (k);
}