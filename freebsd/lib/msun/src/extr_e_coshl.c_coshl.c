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
typedef  int uint16_t ;

/* Variables and functions */
 int BIAS ; 
 long double C10 ; 
 long double C12 ; 
 long double C14 ; 
 long double C16 ; 
 double C18 ; 
 long double C2 ; 
 double C20 ; 
 double C22 ; 
 double C24 ; 
 double C26 ; 
 long double C4 ; 
 long double C6 ; 
 long double C8 ; 
 int /*<<< orphan*/  ENTERI () ; 
 int /*<<< orphan*/  GET_LDBL_EXPSIGN (int,long double) ; 
 int LDBL_MANT_DIG ; 
 int /*<<< orphan*/  RETURNI (long double) ; 
 scalar_t__ fabsl (long double) ; 
 long double hexpl (scalar_t__) ; 
 long double huge ; 
 int /*<<< orphan*/  k_hexpl (scalar_t__,long double*,long double*) ; 
 scalar_t__ o_threshold ; 
 long double tiny ; 

long double
coshl(long double x)
{
	long double hi,lo,x2,x4;
#if LDBL_MANT_DIG == 113
	double dx2;
#endif
	uint16_t ix;

	GET_LDBL_EXPSIGN(ix,x);
	ix &= 0x7fff;

    /* x is INF or NaN */
	if(ix>=0x7fff) return x*x;

	ENTERI();

    /* |x| < 1, return 1 or c(x) */
	if(ix<0x3fff) {
	    if (ix<BIAS-(LDBL_MANT_DIG+1)/2) 	/* |x| < TINY */
		RETURNI(1+tiny);	/* cosh(tiny) = 1(+) with inexact */
	    x2 = x*x;
#if LDBL_MANT_DIG == 64
	    x4 = x2*x2;
	    RETURNI(((C16*x2 + C14)*x4 + (C12*x2 + C10))*(x4*x4*x2) +
		((C8*x2 + C6)*x2 + C4)*x4 + C2*x2 + 1);
#elif LDBL_MANT_DIG == 113
	    dx2 = x2;
	    RETURNI((((((((((((C26*dx2 + C24)*dx2 + C22)*dx2 +
		C20)*x2 + C18)*x2 +
		C16)*x2 + C14)*x2 + C12)*x2 + C10)*x2 + C8)*x2 + C6)*x2 +
		C4)*(x2*x2) + C2*x2 + 1);
#endif
	}

    /* |x| in [1, 64), return accurate exp(|x|)/2+1/exp(|x|)/2 */
	if (ix < 0x4005) {
	    k_hexpl(fabsl(x), &hi, &lo);
	    RETURNI(lo + 0.25/(hi + lo) + hi);
	}

    /* |x| in [64, o_threshold], return correctly-overflowing exp(|x|)/2 */
	if (fabsl(x) <= o_threshold)
	    RETURNI(hexpl(fabsl(x)));

    /* |x| > o_threshold, cosh(x) overflow */
	RETURNI(huge*huge);
}