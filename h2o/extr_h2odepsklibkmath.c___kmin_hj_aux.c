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
typedef  double (* kmin_f ) (int,double*,void*) ;

/* Variables and functions */

__attribute__((used)) static double __kmin_hj_aux(kmin_f func, int n, double *x1, void *data, double fx1, double *dx, int *n_calls)
{
	int k, j = *n_calls;
	double ftmp;
	for (k = 0; k != n; ++k) {
		x1[k] += dx[k];
		ftmp = func(n, x1, data); ++j;
		if (ftmp < fx1) fx1 = ftmp;
		else { /* search the opposite direction */
			dx[k] = 0.0 - dx[k];
			x1[k] += dx[k] + dx[k];
			ftmp = func(n, x1, data); ++j;
			if (ftmp < fx1) fx1 = ftmp;
			else x1[k] -= dx[k]; /* back to the original x[k] */
		}
	}
	*n_calls = j;
	return fx1; /* here: fx1=f(n,x1) */
}