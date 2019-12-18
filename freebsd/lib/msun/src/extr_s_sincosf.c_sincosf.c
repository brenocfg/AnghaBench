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
 int /*<<< orphan*/  __kernel_sincosdf (double,float*,float*) ; 
 float p1pio2 ; 
 float p2pio2 ; 
 float p3pio2 ; 
 float p4pio2 ; 

void
sincosf(float x, float *sn, float *cs)
{
	float c, s;
	double y;
	int32_t n, hx, ix;

	GET_FLOAT_WORD(hx, x);
	ix = hx & 0x7fffffff;

	if (ix <= 0x3f490fda) {		/* |x| ~<= pi/4 */
		if (ix < 0x39800000) {	/* |x| < 2**-12 */
			if ((int)x == 0) {
				*sn = x;	/* x with inexact if x != 0 */
				*cs = 1;
				return;
			}
		}
		__kernel_sincosdf(x, sn, cs);
		return;
	}

	if (ix <= 0x407b53d1) {		/* |x| ~<= 5*pi/4 */
		if (ix <= 0x4016cbe3) {	/* |x| ~<= 3pi/4 */
			if (hx > 0) {
				__kernel_sincosdf(x - p1pio2, cs, sn);
				*cs = -*cs;
			} else {
				__kernel_sincosdf(x + p1pio2, cs, sn);
				*sn = -*sn;
			}
		} else {
			if (hx > 0)
				__kernel_sincosdf(x - p2pio2, sn, cs);
			else
				__kernel_sincosdf(x + p2pio2, sn, cs);
			*sn = -*sn;
			*cs = -*cs;
		}
		return;
	}

	if (ix <= 0x40e231d5) {		/* |x| ~<= 9*pi/4 */
		if (ix <= 0x40afeddf) {	/* |x| ~<= 7*pi/4 */
			if (hx > 0) {
				__kernel_sincosdf(x - p3pio2, cs, sn);
				*sn = -*sn;
			} else {
				__kernel_sincosdf(x + p3pio2, cs, sn);
				*cs = -*cs;
			}
		} else {
			if (hx > 0)
				__kernel_sincosdf(x - p4pio2, sn, cs);
			else
				__kernel_sincosdf(x + p4pio2, sn, cs);
		}
		return;
	}

	/* If x = Inf or NaN, then sin(x) = NaN and cos(x) = NaN. */
	if (ix >= 0x7f800000) {
		*sn = x - x;
		*cs = x - x;
		return;
	}

	/* Argument reduction. */
	n = __ieee754_rem_pio2f(x, &y);
	__kernel_sincosdf(y, &s, &c);

	switch(n & 3) {
	case 0:
		*sn = s;
		*cs = c;
		break;
	case 1:
		*sn = c;
		*cs = -s;
		break;
	case 2:
		*sn = -s;
		*cs = -c;
		break;
	default:
		*sn = -c;
		*cs = s;
	}
}