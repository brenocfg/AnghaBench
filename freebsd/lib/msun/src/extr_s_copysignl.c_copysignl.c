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
struct TYPE_2__ {int /*<<< orphan*/  sign; } ;
union IEEEl2bits {long double e; TYPE_1__ bits; } ;

/* Variables and functions */

long double
copysignl(long double x, long double y)
{
	union IEEEl2bits ux, uy;

	ux.e = x;
	uy.e = y;
	ux.bits.sign = uy.bits.sign;
	return (ux.e);
}