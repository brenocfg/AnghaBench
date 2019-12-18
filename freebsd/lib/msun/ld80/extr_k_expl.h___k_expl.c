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
struct TYPE_2__ {long double lo; long double hi; } ;

/* Variables and functions */
 long double A2 ; 
 long double A3 ; 
 long double A4 ; 
 long double A5 ; 
 long double A6 ; 
 unsigned int INTERVALS ; 
 long double INV_L ; 
 long double L1 ; 
 long double L2 ; 
 int LOG2_INTERVALS ; 
 int irint (long double) ; 
 long double rnintl (long double) ; 
 TYPE_1__* tbl ; 

__attribute__((used)) static inline void
__k_expl(long double x, long double *hip, long double *lop, int *kp)
{
	long double fn, q, r, r1, r2, t, z;
	int n, n2;

	/* Reduce x to (k*ln2 + endpoint[n2] + r1 + r2). */
	fn = rnintl(x * INV_L);
	r = x - fn * L1 - fn * L2;	/* r = r1 + r2 done independently. */
	n = irint(fn);
	n2 = (unsigned)n % INTERVALS;
	/* Depend on the sign bit being propagated: */
	*kp = n >> LOG2_INTERVALS;
	r1 = x - fn * L1;
	r2 = fn * -L2;

	/* Evaluate expl(endpoint[n2] + r1 + r2) = tbl[n2] * expl(r1 + r2). */
	z = r * r;
#if 0
	q = r2 + z * (A2 + r * A3) + z * z * (A4 + r * A5) + z * z * z * A6;
#else
	q = r2 + z * A2 + z * r * (A3 + r * A4 + z * (A5 + r * A6));
#endif
	t = (long double)tbl[n2].lo + tbl[n2].hi;
	*hip = tbl[n2].hi;
	*lop = tbl[n2].lo + t * (q + r1);
}