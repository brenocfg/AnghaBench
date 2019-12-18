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
struct TYPE_2__ {int exp; size_t sign; int manh; int manl; } ;
union IEEEl2bits {long double e; TYPE_1__ bits; } ;

/* Variables and functions */
 int GETFRAC (int,int) ; 
 int HIBITS ; 
 int LDBL_MANT_DIG ; 
 int LDBL_MAX_EXP ; 
 long double* zero ; 

long double
modfl(long double x, long double *iptr)
{
	union IEEEl2bits ux;
	int e;

	ux.e = x;
	e = ux.bits.exp - LDBL_MAX_EXP + 1;
	if (e < HIBITS) {			/* Integer part is in manh. */
		if (e < 0) {			/* |x|<1 */
			*iptr = zero[ux.bits.sign];
			return (x);
		} else {
			if ((GETFRAC(ux.bits.manh, HIBITS - 1 - e) |
			     ux.bits.manl) == 0) {	/* X is an integer. */
				*iptr = x;
				return (zero[ux.bits.sign]);
			} else {
				/* Clear all but the top e+1 bits. */
				ux.bits.manh >>= HIBITS - 1 - e;
				ux.bits.manh <<= HIBITS - 1 - e;
				ux.bits.manl = 0;
				*iptr = ux.e;
				return (x - ux.e);
			}
		}
	} else if (e >= LDBL_MANT_DIG - 1) {	/* x has no fraction part. */
		*iptr = x;
		if (x != x)			/* Handle NaNs. */
			return (x);
		return (zero[ux.bits.sign]);
	} else {				/* Fraction part is in manl. */
		if (GETFRAC(ux.bits.manl, LDBL_MANT_DIG - 1 - e) == 0) {
			/* x is integral. */
			*iptr = x;
			return (zero[ux.bits.sign]);
		} else {
			/* Clear all but the top e+1 bits. */
			ux.bits.manl >>= LDBL_MANT_DIG - 1 - e;
			ux.bits.manl <<= LDBL_MANT_DIG - 1 - e;
			*iptr = ux.e;
			return (x - ux.e);
		}
	}
}