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
struct TYPE_2__ {int /*<<< orphan*/  (* cpu_die ) (int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_KILL_ME ; 
 int /*<<< orphan*/  CPU_STUCK_IN_KERNEL ; 
 TYPE_1__** cpu_ops ; 
 int /*<<< orphan*/  cpu_park_loop () ; 
 int /*<<< orphan*/  pr_crit (char*,int) ; 
 int /*<<< orphan*/  set_cpu_present (int,int /*<<< orphan*/ ) ; 
 int smp_processor_id () ; 
 int /*<<< orphan*/  stub1 (int) ; 
 int /*<<< orphan*/  update_cpu_boot_status (int /*<<< orphan*/ ) ; 

void cpu_die_early(void)
{
	int cpu = smp_processor_id();

	pr_crit("CPU%d: will not boot\n", cpu);

	/* Mark this CPU absent */
	set_cpu_present(cpu, 0);

#ifdef CONFIG_HOTPLUG_CPU
	update_cpu_boot_status(CPU_KILL_ME);
	/* Check if we can park ourselves */
	if (cpu_ops[cpu] && cpu_ops[cpu]->cpu_die)
		cpu_ops[cpu]->cpu_die(cpu);
#endif
	update_cpu_boot_status(CPU_STUCK_IN_KERNEL);

	cpu_park_loop();
}