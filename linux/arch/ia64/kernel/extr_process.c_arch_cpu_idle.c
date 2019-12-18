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
 void ia64_mark_idle (int) ; 
 int /*<<< orphan*/  min_xtp () ; 
 int /*<<< orphan*/  normal_xtp () ; 
 int /*<<< orphan*/  rmb () ; 
 int /*<<< orphan*/  safe_halt () ; 
 void stub1 (int) ; 
 void stub2 (int) ; 

void arch_cpu_idle(void)
{
	void (*mark_idle)(int) = ia64_mark_idle;

#ifdef CONFIG_SMP
	min_xtp();
#endif
	rmb();
	if (mark_idle)
		(*mark_idle)(1);

	safe_halt();

	if (mark_idle)
		(*mark_idle)(0);
#ifdef CONFIG_SMP
	normal_xtp();
#endif
}