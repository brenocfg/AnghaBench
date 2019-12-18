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
 int EXP_LARGE ; 
 int EXP_TINY ; 
 int /*<<< orphan*/  GET_LDBL_EXPSIGN (int,long double) ; 
 int /*<<< orphan*/  RETURNI (long double) ; 
 long double fabsl (long double) ; 
 long double huge ; 
 long double ln2 ; 
 long double log1pl (long double) ; 
 long double logl (double) ; 
 long double one ; 
 long double sqrtl (long double) ; 

long double
asinhl(long double x)
{
	long double t, w;
	uint16_t hx, ix;

	ENTERI();
	GET_LDBL_EXPSIGN(hx, x);
	ix = hx & 0x7fff;
	if (ix >= 0x7fff) RETURNI(x+x);	/* x is inf, NaN or misnormal */
	if (ix < BIAS + EXP_TINY) {	/* |x| < TINY, or misnormal */
	    if (huge + x > one) RETURNI(x);	/* return x inexact except 0 */
	}
	if (ix >= BIAS + EXP_LARGE) {	/* |x| >= LARGE, or misnormal */
	    w = logl(fabsl(x))+ln2;
	} else if (ix >= 0x4000) {	/* LARGE > |x| >= 2.0, or misnormal */
	    t = fabsl(x);
	    w = logl(2.0*t+one/(sqrtl(x*x+one)+t));
	} else {		/* 2.0 > |x| >= TINY, or misnormal */
	    t = x*x;
	    w =log1pl(fabsl(x)+t/(one+sqrtl(one+t)));
	}
	RETURNI((hx & 0x8000) == 0 ? w : -w);
}