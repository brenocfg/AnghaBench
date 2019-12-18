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
 float __ieee754_j0f (float) ; 
 float __ieee754_logf (float) ; 
 float cosf (float) ; 
 float invsqrtpi ; 
 float one ; 
 float pzerof (float) ; 
 float qzerof (float) ; 
 int /*<<< orphan*/  sincosf (float,float*,float*) ; 
 float sqrtf (float) ; 
 float tpi ; 
 float u00 ; 
 float u01 ; 
 float u02 ; 
 float u03 ; 
 float u04 ; 
 float u05 ; 
 float u06 ; 
 float v01 ; 
 float v02 ; 
 float v03 ; 
 float v04 ; 
 float vone ; 
 float vzero ; 
 float zero ; 

float
__ieee754_y0f(float x)
{
	float z, s,c,ss,cc,u,v;
	int32_t hx,ix;

	GET_FLOAT_WORD(hx,x);
        ix = 0x7fffffff&hx;
	if(ix>=0x7f800000) return  vone/(x+x*x);
	if(ix==0) return -one/vzero;
	if(hx<0) return vzero/vzero;
        if(ix >= 0x40000000) {  /* |x| >= 2.0 */
        /* y0(x) = sqrt(2/(pi*x))*(p0(x)*sin(x0)+q0(x)*cos(x0))
         * where x0 = x-pi/4
         *      Better formula:
         *              cos(x0) = cos(x)cos(pi/4)+sin(x)sin(pi/4)
         *                      =  1/sqrt(2) * (sin(x) + cos(x))
         *              sin(x0) = sin(x)cos(3pi/4)-cos(x)sin(3pi/4)
         *                      =  1/sqrt(2) * (sin(x) - cos(x))
         * To avoid cancellation, use
         *              sin(x) +- cos(x) = -cos(2x)/(sin(x) -+ cos(x))
         * to compute the worse one.
         */
                sincosf(x, &s, &c);
                ss = s-c;
                cc = s+c;
	/*
	 * j0(x) = 1/sqrt(pi) * (P(0,x)*cc - Q(0,x)*ss) / sqrt(x)
	 * y0(x) = 1/sqrt(pi) * (P(0,x)*ss + Q(0,x)*cc) / sqrt(x)
	 */
                if(ix<0x7f000000) {  /* make sure x+x not overflow */
                    z = -cosf(x+x);
                    if ((s*c)<zero) cc = z/ss;
                    else            ss = z/cc;
                }
                if(ix>0x58000000) z = (invsqrtpi*ss)/sqrtf(x); /* |x|>2**49 */
                else {
                    u = pzerof(x); v = qzerof(x);
                    z = invsqrtpi*(u*ss+v*cc)/sqrtf(x);
                }
                return z;
	}
	if(ix<=0x39000000) {	/* x < 2**-13 */
	    return(u00 + tpi*__ieee754_logf(x));
	}
	z = x*x;
	u = u00+z*(u01+z*(u02+z*(u03+z*(u04+z*(u05+z*u06)))));
	v = one+z*(v01+z*(v02+z*(v03+z*v04)));
	return(u/v + tpi*(__ieee754_j0f(x)*__ieee754_logf(x)));
}