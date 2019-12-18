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
 float fabsf (float) ; 
 float huge ; 
 float one ; 
 float pS0 ; 
 float pS1 ; 
 float pS2 ; 
 float pio2 ; 
 float qS1 ; 
 double sqrt (float) ; 

float
__ieee754_asinf(float x)
{
	double s;
	float t,w,p,q;
	int32_t hx,ix;
	GET_FLOAT_WORD(hx,x);
	ix = hx&0x7fffffff;
	if(ix>=0x3f800000) {		/* |x| >= 1 */
	    if(ix==0x3f800000)		/* |x| == 1 */
		return x*pio2;		/* asin(+-1) = +-pi/2 with inexact */
	    return (x-x)/(x-x);		/* asin(|x|>1) is NaN */
	} else if (ix<0x3f000000) {	/* |x|<0.5 */
	    if(ix<0x39800000) {		/* |x| < 2**-12 */
		if(huge+x>one) return x;/* return x with inexact if x!=0*/
	    }
	    t = x*x;
	    p = t*(pS0+t*(pS1+t*pS2));
	    q = one+t*qS1;
	    w = p/q;
	    return x+x*w;
	}
	/* 1> |x|>= 0.5 */
	w = one-fabsf(x);
	t = w*(float)0.5;
	p = t*(pS0+t*(pS1+t*pS2));
	q = one+t*qS1;
	s = sqrt(t);
	w = p/q;
	t = pio2-2.0*(s+s*w);
	if(hx>0) return t; else return -t;
}