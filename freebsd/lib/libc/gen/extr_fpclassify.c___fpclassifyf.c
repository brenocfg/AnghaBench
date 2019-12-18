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
struct TYPE_2__ {int exp; scalar_t__ man; } ;
union IEEEf2bits {float f; TYPE_1__ bits; } ;

/* Variables and functions */
 int FP_INFINITE ; 
 int FP_NAN ; 
 int FP_NORMAL ; 
 int FP_SUBNORMAL ; 
 int FP_ZERO ; 

int
__fpclassifyf(float f)
{
	union IEEEf2bits u;

	u.f = f;
	if (u.bits.exp == 0) {
		if (u.bits.man == 0)
			return (FP_ZERO);
		return (FP_SUBNORMAL);
	}
	if (u.bits.exp == 255) {
		if (u.bits.man == 0)
			return (FP_INFINITE);
		return (FP_NAN);
	}
	return (FP_NORMAL);
}