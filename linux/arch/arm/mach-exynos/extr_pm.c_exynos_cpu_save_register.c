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
 unsigned long* save_arm_register ; 

void exynos_cpu_save_register(void)
{
	unsigned long tmp;

	/* Save Power control register */
	asm ("mrc p15, 0, %0, c15, c0, 0"
	     : "=r" (tmp) : : "cc");

	save_arm_register[0] = tmp;

	/* Save Diagnostic register */
	asm ("mrc p15, 0, %0, c15, c0, 1"
	     : "=r" (tmp) : : "cc");

	save_arm_register[1] = tmp;
}