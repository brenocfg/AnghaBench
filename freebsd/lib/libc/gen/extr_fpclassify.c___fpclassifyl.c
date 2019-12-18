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
struct TYPE_2__ {int exp; int manl; int manh; } ;
union IEEEl2bits {long double e; TYPE_1__ bits; } ;

/* Variables and functions */
 int FP_INFINITE ; 
 int FP_NAN ; 
 int FP_NORMAL ; 
 int FP_SUBNORMAL ; 
 int FP_ZERO ; 
 int /*<<< orphan*/  mask_nbit_l (union IEEEl2bits) ; 

int
__fpclassifyl(long double e)
{
	union IEEEl2bits u;

	u.e = e;
	if (u.bits.exp == 0) {
		if ((u.bits.manl | u.bits.manh) == 0)
			return (FP_ZERO);
		return (FP_SUBNORMAL);
	}
	mask_nbit_l(u);		/* Mask normalization bit if applicable. */
#if LDBL_MANT_DIG == 53
	if (u.bits.exp == 2047) {
		if ((u.bits.manl | u.bits.manh) == 0)
			return (FP_INFINITE);
		return (FP_NAN);
	}
#else
	if (u.bits.exp == 32767) {
		if ((u.bits.manl | u.bits.manh) == 0)
			return (FP_INFINITE);
		return (FP_NAN);
	}
#endif
	return (FP_NORMAL);
}