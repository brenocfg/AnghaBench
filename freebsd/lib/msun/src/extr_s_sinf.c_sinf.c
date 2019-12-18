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
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  GET_FLOAT_WORD (int,float) ; 
 int __ieee754_rem_pio2f (float,double*) ; 
 float __kernel_cosdf (double) ; 
 float __kernel_sindf (double) ; 
 double s1pio2 ; 
 float s2pio2 ; 
 double s3pio2 ; 
 float s4pio2 ; 

float
sinf(float x)
{
	double y;
	int32_t n, hx, ix;

	GET_FLOAT_WORD(hx,x);
	ix = hx & 0x7fffffff;

	if(ix <= 0x3f490fda) {		/* |x| ~<= pi/4 */
	    if(ix<0x39800000)		/* |x| < 2**-12 */
		if(((int)x)==0) return x;	/* x with inexact if x != 0 */
	    return __kernel_sindf(x);
	}
	if(ix<=0x407b53d1) {		/* |x| ~<= 5*pi/4 */
	    if(ix<=0x4016cbe3) {	/* |x| ~<= 3pi/4 */
		if(hx>0)
		    return __kernel_cosdf(x - s1pio2);
		else
		    return -__kernel_cosdf(x + s1pio2);
	    } else
		return __kernel_sindf((hx > 0 ? s2pio2 : -s2pio2) - x);
	}
	if(ix<=0x40e231d5) {		/* |x| ~<= 9*pi/4 */
	    if(ix<=0x40afeddf) {	/* |x| ~<= 7*pi/4 */
		if(hx>0)
		    return -__kernel_cosdf(x - s3pio2);
		else
		    return __kernel_cosdf(x + s3pio2);
	    } else
		return __kernel_sindf(x + (hx > 0 ? -s4pio2 : s4pio2));
	}

    /* sin(Inf or NaN) is NaN */
	else if (ix>=0x7f800000) return x-x;

    /* general argument reduction needed */
	else {
	    n = __ieee754_rem_pio2f(x,&y);
	    switch(n&3) {
		case 0: return  __kernel_sindf(y);
		case 1: return  __kernel_cosdf(y);
		case 2: return  __kernel_sindf(-y);
		default:
			return -__kernel_cosdf(y);
	    }
	}
}