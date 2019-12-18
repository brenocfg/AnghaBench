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
struct TYPE_2__ {int exp; scalar_t__ manl; scalar_t__ manh; } ;
union IEEEl2bits {long double e; TYPE_1__ bits; } ;

/* Variables and functions */
 int /*<<< orphan*/  mask_nbit_l (union IEEEl2bits) ; 

int
__isinfl(long double e)
{
	union IEEEl2bits u;

	u.e = e;
	mask_nbit_l(u);
#if LDBL_MANT_DIG == 53
	return (u.bits.exp == 2047 && u.bits.manl == 0 && u.bits.manh == 0);
#else
	return (u.bits.exp == 32767 && u.bits.manl == 0 && u.bits.manh == 0);
#endif
}