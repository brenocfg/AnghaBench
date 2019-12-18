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
 int /*<<< orphan*/  ENTERI () ; 
 int EXP_TINY ; 
 int /*<<< orphan*/  GET_LDBL_EXPSIGN (int,long double) ; 
 int /*<<< orphan*/  RETURNI (long double) ; 
 int /*<<< orphan*/  SET_LDBL_EXPSIGN (long double,int) ; 
 int fabsl (long double) ; 
 long double huge ; 
 double log1pl (long double) ; 
 long double one ; 
 long double zero ; 

long double
atanhl(long double x)
{
	long double t;
	uint16_t hx, ix;

	ENTERI();
	GET_LDBL_EXPSIGN(hx, x);
	ix = hx & 0x7fff;
	if (ix >= 0x3fff)		/* |x| >= 1, or NaN or misnormal */
	    RETURNI(fabsl(x) == 1 ? x / zero : (x - x) / (x - x));
	if (ix < BIAS + EXP_TINY && (huge + x) > zero)
	    RETURNI(x);			/* x is tiny */
	SET_LDBL_EXPSIGN(x, ix);
	if (ix < 0x3ffe) {		/* |x| < 0.5, or misnormal */
	    t = x+x;
	    t = 0.5*log1pl(t+t*x/(one-x));
	} else 
	    t = 0.5*log1pl((x+x)/(one-x));
	RETURNI((hx & 0x8000) == 0 ? t : -t);
}