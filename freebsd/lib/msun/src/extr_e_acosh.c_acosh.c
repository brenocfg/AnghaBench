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
typedef  int u_int32_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXTRACT_WORDS (int,int,double) ; 
 double __ieee754_log (double) ; 
 double ln2 ; 
 double log1p (double) ; 
 double one ; 
 double sqrt (double) ; 

double
__ieee754_acosh(double x)
{
	double t;
	int32_t hx;
	u_int32_t lx;
	EXTRACT_WORDS(hx,lx,x);
	if(hx<0x3ff00000) {		/* x < 1 */
	    return (x-x)/(x-x);
	} else if(hx >=0x41b00000) {	/* x > 2**28 */
	    if(hx >=0x7ff00000) {	/* x is inf of NaN */
	        return x+x;
	    } else 
		return __ieee754_log(x)+ln2;	/* acosh(huge)=log(2x) */
	} else if(((hx-0x3ff00000)|lx)==0) {
	    return 0.0;			/* acosh(1) = 0 */
	} else if (hx > 0x40000000) {	/* 2**28 > x > 2 */
	    t=x*x;
	    return __ieee754_log(2.0*x-one/(x+sqrt(t-one)));
	} else {			/* 1<x<2 */
	    t = x-one;
	    return log1p(t+sqrt(2.0*t+t*t));
	}
}