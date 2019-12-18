#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int expsign; } ;
union IEEEl2bits {long double e; TYPE_1__ xbits; } ;
typedef  int uint32_t ;

/* Variables and functions */
 int BIAS ; 
 int LDBL_MANT_DIG ; 
 int LDBL_MAX_EXP ; 
 scalar_t__* shift ; 
 long double* zero ; 

long double
rintl(long double x)
{
	union IEEEl2bits u;
	uint32_t expsign;
	int ex, sign;

	u.e = x;
	expsign = u.xbits.expsign;
	ex = expsign & 0x7fff;

	if (ex >= BIAS + LDBL_MANT_DIG - 1) {
		if (ex == BIAS + LDBL_MAX_EXP)
			return (x + x);	/* Inf, NaN, or unsupported format */
		return (x);		/* finite and already an integer */
	}
	sign = expsign >> 15;

	/*
	 * The following code assumes that intermediate results are
	 * evaluated in long double precision. If they are evaluated in
	 * greater precision, double rounding may occur, and if they are
	 * evaluated in less precision (as on i386), results will be
	 * wildly incorrect.
	 */
	x += shift[sign];
	x -= shift[sign];

	/*
	 * If the result is +-0, then it must have the same sign as x, but
	 * the above calculation doesn't always give this.  Fix up the sign.
	 */
	if (ex < BIAS && x == 0.0L)
		return (zero[sign]);

	return (x);
}