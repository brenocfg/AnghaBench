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
 int __softfloat_float_rounding_mode ; 
 int* map ; 

int
__flt_rounds()
{
	int mode;

#ifdef __mips_soft_float
	mode = __softfloat_float_rounding_mode;
#else
	__asm __volatile("cfc1 %0,$31" : "=r" (mode));
#endif

	return map[mode & 0x03];
}