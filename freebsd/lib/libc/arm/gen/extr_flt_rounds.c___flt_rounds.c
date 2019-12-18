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

/* Variables and functions */
#define  FE_DOWNWARD 131 
#define  FE_TONEAREST 130 
#define  FE_TOWARDZERO 129 
#define  FE_UPWARD 128 
 int _ROUND_MASK ; 
 int __softfloat_float_rounding_mode ; 

int
__flt_rounds(void)
{
	int mode;

#ifndef __ARM_PCS_VFP
	/*
	 * Translate our rounding modes to the unnamed
	 * manifest constants required by C99 et. al.
	 */
	mode = __softfloat_float_rounding_mode;
#else /* __ARM_PCS_VFP */
	/*
	 * Read the floating-point status and control register
	 */
	__asm __volatile("vmrs %0, fpscr" : "=&r"(mode));
	mode &= _ROUND_MASK;
#endif /* __ARM_PCS_VFP */

	switch (mode) {
	case FE_TOWARDZERO:
		return (0);
	case FE_TONEAREST:
		return (1);
	case FE_UPWARD:
		return (2);
	case FE_DOWNWARD:
		return (3);
	}
	return (-1);
}