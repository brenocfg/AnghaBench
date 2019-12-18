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
typedef  union ieee754sp {int dummy; } ieee754sp ;
typedef  union ieee754dp {int dummy; } ieee754dp ;
typedef  int u64 ;

/* Variables and functions */
 int /*<<< orphan*/  COMPXSP ; 
 scalar_t__ DP_EBIAS ; 
 int DP_FBITS ; 
 int /*<<< orphan*/  EXPLODEXSP ; 
 int /*<<< orphan*/  FLUSHXSP ; 
#define  IEEE754_CLASS_DNORM 133 
#define  IEEE754_CLASS_INF 132 
#define  IEEE754_CLASS_NORM 131 
#define  IEEE754_CLASS_QNAN 130 
#define  IEEE754_CLASS_SNAN 129 
#define  IEEE754_CLASS_ZERO 128 
 int SP_FBITS ; 
 int SP_HIDDEN_BIT ; 
 union ieee754dp builddp (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  ieee754_clearcx () ; 
 union ieee754dp ieee754dp_inf (int /*<<< orphan*/ ) ; 
 union ieee754dp ieee754dp_nan_fsp (int /*<<< orphan*/ ,int) ; 
 union ieee754dp ieee754dp_nanxcpt (union ieee754dp) ; 
 union ieee754dp ieee754dp_zero (int /*<<< orphan*/ ) ; 
 int xc ; 
 scalar_t__ xe ; 
 int xm ; 
 int /*<<< orphan*/  xs ; 

union ieee754dp ieee754dp_fsp(union ieee754sp x)
{
	COMPXSP;

	EXPLODEXSP;

	ieee754_clearcx();

	FLUSHXSP;

	switch (xc) {
	case IEEE754_CLASS_SNAN:
		return ieee754dp_nanxcpt(ieee754dp_nan_fsp(xs, xm));

	case IEEE754_CLASS_QNAN:
		return ieee754dp_nan_fsp(xs, xm);

	case IEEE754_CLASS_INF:
		return ieee754dp_inf(xs);

	case IEEE754_CLASS_ZERO:
		return ieee754dp_zero(xs);

	case IEEE754_CLASS_DNORM:
		/* normalize */
		while ((xm >> SP_FBITS) == 0) {
			xm <<= 1;
			xe--;
		}
		break;

	case IEEE754_CLASS_NORM:
		break;
	}

	/*
	 * Can't possibly overflow,underflow, or need rounding
	 */

	/* drop the hidden bit */
	xm &= ~SP_HIDDEN_BIT;

	return builddp(xs, xe + DP_EBIAS,
		       (u64) xm << (DP_FBITS - SP_FBITS));
}