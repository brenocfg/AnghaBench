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
 int EXP_LARGE ; 
 int /*<<< orphan*/  GET_LDBL_EXPSIGN (int,long double) ; 
 int /*<<< orphan*/  RETURNI (double) ; 
 double ln2 ; 
 double log1pl (long double) ; 
 double logl (double) ; 
 long double one ; 
 long double sqrtl (double) ; 

long double
acoshl(long double x)
{
	long double t;
	int16_t hx;

	ENTERI();
	GET_LDBL_EXPSIGN(hx, x);
	if (hx < 0x3fff) {		/* x < 1, or misnormal */
	    RETURNI((x-x)/(x-x));
	} else if (hx >= BIAS + EXP_LARGE) { /* x >= LARGE */
	    if (hx >= 0x7fff) {		/* x is inf, NaN or misnormal */
	        RETURNI(x+x);
	    } else 
		RETURNI(logl(x)+ln2);	/* acosh(huge)=log(2x), or misnormal */
	} else if (hx == 0x3fff && x == 1) {
	    RETURNI(0.0);		/* acosh(1) = 0 */
	} else if (hx >= 0x4000) {	/* LARGE > x >= 2, or misnormal */
	    t=x*x;
	    RETURNI(logl(2.0*x-one/(x+sqrtl(t-one))));
	} else {			/* 1<x<2 */
	    t = x-one;
	    RETURNI(log1pl(t+sqrtl(2.0*t+t*t)));
	}
}