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
 int /*<<< orphan*/  pr_warn (char*,unsigned int,int) ; 
 int /*<<< orphan*/  versatile_immitation_do_lowpower (unsigned int,int*) ; 
 int /*<<< orphan*/  versatile_immitation_enter_lowpower (unsigned int) ; 
 int /*<<< orphan*/  versatile_immitation_leave_lowpower (unsigned int) ; 

void versatile_immitation_cpu_die(unsigned int cpu, unsigned int actrl_mask)
{
	int spurious = 0;

	versatile_immitation_enter_lowpower(actrl_mask);
	versatile_immitation_do_lowpower(cpu, &spurious);
	versatile_immitation_leave_lowpower(actrl_mask);

	if (spurious)
		pr_warn("CPU%u: %u spurious wakeup calls\n", cpu, spurious);
}