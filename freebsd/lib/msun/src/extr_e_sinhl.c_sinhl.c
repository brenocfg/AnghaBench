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
typedef  int int16_t ;

/* Variables and functions */
 int BIAS ; 
 int /*<<< orphan*/  ENTERI () ; 
 int /*<<< orphan*/  GET_LDBL_EXPSIGN (int,long double) ; 
 int LDBL_MANT_DIG ; 
 int /*<<< orphan*/  RETURNI (double) ; 
 long double S11 ; 
 long double S13 ; 
 long double S15 ; 
 long double S17 ; 
 double S19 ; 
 double S21 ; 
 double S23 ; 
 double S25 ; 
 long double S3 ; 
 long double S5 ; 
 long double S7 ; 
 long double S9 ; 
 scalar_t__ fabsl (long double) ; 
 double hexpl (scalar_t__) ; 
 int /*<<< orphan*/  k_hexpl (scalar_t__,long double*,long double*) ; 
 scalar_t__ o_threshold ; 
 long double shuge ; 

long double
sinhl(long double x)
{
	long double hi,lo,x2,x4;
#if LDBL_MANT_DIG == 113
	double dx2;
#endif
	double s;
	int16_t ix,jx;

	GET_LDBL_EXPSIGN(jx,x);
	ix = jx&0x7fff;

    /* x is INF or NaN */
	if(ix>=0x7fff) return x+x;

	ENTERI();

	s = 1;
	if (jx<0) s = -1;

    /* |x| < 64, return x, s(x), or accurate s*(exp(|x|)/2-1/exp(|x|)/2) */
	if (ix<0x4005) {		/* |x|<64 */
	    if (ix<BIAS-(LDBL_MANT_DIG+1)/2) 	/* |x|<TINY */
		if(shuge+x>1) RETURNI(x);  /* sinh(tiny) = tiny with inexact */
	    if (ix<0x3fff) {		/* |x|<1 */
		x2 = x*x;
#if LDBL_MANT_DIG == 64
		x4 = x2*x2;
		RETURNI(((S17*x2 + S15)*x4 + (S13*x2 + S11))*(x2*x*x4*x4) +
		    ((S9*x2 + S7)*x2 + S5)*(x2*x*x2) + S3*(x2*x) + x);
#elif LDBL_MANT_DIG == 113
		dx2 = x2;
		RETURNI(((((((((((S25*dx2 + S23)*dx2 +
		    S21)*x2 + S19)*x2 +
		    S17)*x2 + S15)*x2 + S13)*x2 + S11)*x2 + S9)*x2 + S7)*x2 +
		    S5)* (x2*x*x2) +
		    S3*(x2*x) + x);
#endif
	    }
	    k_hexpl(fabsl(x), &hi, &lo);
	    RETURNI(s*(lo - 0.25/(hi + lo) + hi));
	}

    /* |x| in [64, o_threshold], return correctly-overflowing s*exp(|x|)/2 */
	if (fabsl(x) <= o_threshold)
	    RETURNI(s*hexpl(fabsl(x)));

    /* |x| > o_threshold, sinh(x) overflow */
	return x*shuge;
}