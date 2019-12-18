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
 float* U0 ; 
 float* V0 ; 
 float __ieee754_j1f (float) ; 
 float __ieee754_logf (float) ; 
 float cosf (float) ; 
 float invsqrtpi ; 
 float one ; 
 float ponef (float) ; 
 float qonef (float) ; 
 int /*<<< orphan*/  sincosf (float,float*,float*) ; 
 float sqrtf (float) ; 
 float tpi ; 
 float vone ; 
 float vzero ; 
 float zero ; 

float
__ieee754_y1f(float x)
{
	float z, s,c,ss,cc,u,v;
	int32_t hx,ix;

	GET_FLOAT_WORD(hx,x);
        ix = 0x7fffffff&hx;
	if(ix>=0x7f800000) return  vone/(x+x*x);
	if(ix==0) return -one/vzero;
	if(hx<0) return vzero/vzero;
        if(ix >= 0x40000000) {  /* |x| >= 2.0 */
                sincosf(x, &s, &c);
                ss = -s-c;
                cc = s-c;
                if(ix<0x7f000000) {  /* make sure x+x not overflow */
                    z = cosf(x+x);
                    if ((s*c)>zero) cc = z/ss;
                    else            ss = z/cc;
                }
        /* y1(x) = sqrt(2/(pi*x))*(p1(x)*sin(x0)+q1(x)*cos(x0))
         * where x0 = x-3pi/4
         *      Better formula:
         *              cos(x0) = cos(x)cos(3pi/4)+sin(x)sin(3pi/4)
         *                      =  1/sqrt(2) * (sin(x) - cos(x))
         *              sin(x0) = sin(x)cos(3pi/4)-cos(x)sin(3pi/4)
         *                      = -1/sqrt(2) * (cos(x) + sin(x))
         * To avoid cancellation, use
         *              sin(x) +- cos(x) = -cos(2x)/(sin(x) -+ cos(x))
         * to compute the worse one.
         */
                if(ix>0x58000000) z = (invsqrtpi*ss)/sqrtf(x); /* |x|>2**49 */
                else {
                    u = ponef(x); v = qonef(x);
                    z = invsqrtpi*(u*ss+v*cc)/sqrtf(x);
                }
                return z;
        }
        if(ix<=0x33000000) {    /* x < 2**-25 */
            return(-tpi/x);
        }
        z = x*x;
        u = U0[0]+z*(U0[1]+z*(U0[2]+z*(U0[3]+z*U0[4])));
        v = one+z*(V0[0]+z*(V0[1]+z*(V0[2]+z*(V0[3]+z*V0[4]))));
        return(x*(u/v) + tpi*(__ieee754_j1f(x)*__ieee754_logf(x)-one/x));
}