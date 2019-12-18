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
struct notifier_block {int dummy; } ;

/* Variables and functions */
 unsigned long CPU_PM_ENTER ; 
 unsigned long CPU_PM_EXIT ; 
 int NOTIFY_OK ; 
 unsigned int cpu_logical_map (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvebu_cpu_resume ; 
 int /*<<< orphan*/  mvebu_pmsu_set_cpu_boot_addr (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvebu_v7_pmsu_idle_exit () ; 
 int /*<<< orphan*/  smp_processor_id () ; 

__attribute__((used)) static int mvebu_v7_cpu_pm_notify(struct notifier_block *self,
				    unsigned long action, void *hcpu)
{
	if (action == CPU_PM_ENTER) {
		unsigned int hw_cpu = cpu_logical_map(smp_processor_id());
		mvebu_pmsu_set_cpu_boot_addr(hw_cpu, mvebu_cpu_resume);
	} else if (action == CPU_PM_EXIT) {
		mvebu_v7_pmsu_idle_exit();
	}

	return NOTIFY_OK;
}