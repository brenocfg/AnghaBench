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
struct TYPE_2__ {int exp; int manh; int manl; scalar_t__ sign; } ;
union IEEEl2bits {long double e; TYPE_1__ bits; } ;

/* Variables and functions */
 int /*<<< orphan*/  mask_nbit_l (union IEEEl2bits) ; 

long double
fmaxl(long double x, long double y)
{
	union IEEEl2bits u[2];

	u[0].e = x;
	mask_nbit_l(u[0]);
	u[1].e = y;
	mask_nbit_l(u[1]);

	/* Check for NaNs to avoid raising spurious exceptions. */
	if (u[0].bits.exp == 32767 && (u[0].bits.manh | u[0].bits.manl) != 0)
		return (y);
	if (u[1].bits.exp == 32767 && (u[1].bits.manh | u[1].bits.manl) != 0)
		return (x);

	/* Handle comparisons of signed zeroes. */
	if (u[0].bits.sign != u[1].bits.sign)
		return (u[0].bits.sign ? y : x);

	return (x > y ? x : y);
}