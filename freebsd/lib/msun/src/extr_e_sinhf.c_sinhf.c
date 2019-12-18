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
 float __ieee754_expf (int /*<<< orphan*/ ) ; 
 float __ldexp_expf (int /*<<< orphan*/ ,int) ; 
 float expm1f (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fabsf (float) ; 
 float one ; 
 float shuge ; 

float
__ieee754_sinhf(float x)
{
	float t,h;
	int32_t ix,jx;

	GET_FLOAT_WORD(jx,x);
	ix = jx&0x7fffffff;

    /* x is INF or NaN */
	if(ix>=0x7f800000) return x+x;

	h = 0.5;
	if (jx<0) h = -h;
    /* |x| in [0,9], return sign(x)*0.5*(E+E/(E+1))) */
	if (ix < 0x41100000) {		/* |x|<9 */
	    if (ix<0x39800000) 		/* |x|<2**-12 */
		if(shuge+x>one) return x;/* sinh(tiny) = tiny with inexact */
	    t = expm1f(fabsf(x));
	    if(ix<0x3f800000) return h*((float)2.0*t-t*t/(t+one));
	    return h*(t+t/(t+one));
	}

    /* |x| in [9, logf(maxfloat)] return 0.5*exp(|x|) */
	if (ix < 0x42b17217)  return h*__ieee754_expf(fabsf(x));

    /* |x| in [logf(maxfloat), overflowthresold] */
	if (ix<=0x42b2d4fc)
	    return h*2.0F*__ldexp_expf(fabsf(x), -1);

    /* |x| > overflowthresold, sinh(x) overflow */
	return x*shuge;
}