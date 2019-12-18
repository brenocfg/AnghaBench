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
 float expm1f (float) ; 
 float fabsf (float) ; 
 float huge ; 
 float one ; 
 float tiny ; 
 float two ; 

float
tanhf(float x)
{
	float t,z;
	int32_t jx,ix;

	GET_FLOAT_WORD(jx,x);
	ix = jx&0x7fffffff;

    /* x is INF or NaN */
	if(ix>=0x7f800000) {
	    if (jx>=0) return one/x+one;    /* tanh(+-inf)=+-1 */
	    else       return one/x-one;    /* tanh(NaN) = NaN */
	}

    /* |x| < 9 */
	if (ix < 0x41100000) {		/* |x|<9 */
	    if (ix<0x39800000) {	/* |x|<2**-12 */
		if(huge+x>one) return x; /* tanh(tiny) = tiny with inexact */
	    }
	    if (ix>=0x3f800000) {	/* |x|>=1  */
		t = expm1f(two*fabsf(x));
		z = one - two/(t+two);
	    } else {
	        t = expm1f(-two*fabsf(x));
	        z= -t/(t+two);
	    }
    /* |x| >= 9, return +-1 */
	} else {
	    z = one - tiny;		/* raise inexact flag */
	}
	return (jx>=0)? z: -z;
}