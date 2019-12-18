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
struct task_struct {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pgd; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  boot_secondary (unsigned int,struct task_struct*) ; 
 int /*<<< orphan*/  cpu_running ; 
 int /*<<< orphan*/ * current_pgd ; 
 TYPE_1__ init_mm ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  pr_crit (char*,unsigned int) ; 
 int /*<<< orphan*/  pr_warn (char*,unsigned int) ; 
 int /*<<< orphan*/  secondary_thread_info ; 
 int /*<<< orphan*/ * smp_cross_call ; 
 int /*<<< orphan*/  synchronise_count_master (unsigned int) ; 
 int /*<<< orphan*/  task_thread_info (struct task_struct*) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int __cpu_up(unsigned int cpu, struct task_struct *idle)
{
	if (smp_cross_call == NULL) {
		pr_warn("CPU%u: failed to start, IPI controller missing",
			cpu);
		return -EIO;
	}

	secondary_thread_info = task_thread_info(idle);
	current_pgd[cpu] = init_mm.pgd;

	boot_secondary(cpu, idle);
	if (!wait_for_completion_timeout(&cpu_running,
					msecs_to_jiffies(1000))) {
		pr_crit("CPU%u: failed to start\n", cpu);
		return -EIO;
	}
	synchronise_count_master(cpu);

	return 0;
}