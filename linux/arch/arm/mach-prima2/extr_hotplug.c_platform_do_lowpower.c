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
 scalar_t__ cpu_logical_map (unsigned int) ; 
 scalar_t__ prima2_pen_release ; 

__attribute__((used)) static inline void platform_do_lowpower(unsigned int cpu)
{
	/* we put the platform to just WFI */
	for (;;) {
		__asm__ __volatile__("dsb\n\t" "wfi\n\t"
			: : : "memory");
		if (prima2_pen_release == cpu_logical_map(cpu)) {
			/*
			 * OK, proper wakeup, we're done
			 */
			break;
		}
	}
}