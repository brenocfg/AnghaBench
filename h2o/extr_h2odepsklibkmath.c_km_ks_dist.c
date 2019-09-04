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

/* Variables and functions */
 double fabs (double) ; 

double km_ks_dist(int na, const double a[], int nb, const double b[]) // a[] and b[] MUST BE sorted
{
	int ia = 0, ib = 0;
	double fa = 0, fb = 0, sup = 0, na1 = 1. / na, nb1 = 1. / nb;
	while (ia < na || ib < nb) {
		if (ia == na) fb += nb1, ++ib;
		else if (ib == nb) fa += na1, ++ia;
		else if (a[ia] < b[ib]) fa += na1, ++ia;
		else if (a[ia] > b[ib]) fb += nb1, ++ib;
		else fa += na1, fb += nb1, ++ia, ++ib;
		if (sup < fabs(fa - fb)) sup = fabs(fa - fb);
	}
	return sup;
}