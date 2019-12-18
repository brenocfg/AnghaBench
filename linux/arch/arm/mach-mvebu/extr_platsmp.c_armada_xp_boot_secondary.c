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
struct task_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  arch_send_wakeup_ipi_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  armada_xp_secondary_startup ; 
 int cpu_logical_map (unsigned int) ; 
 int /*<<< orphan*/  cpumask_of (unsigned int) ; 
 int mvebu_cpu_reset_deassert (int) ; 
 int /*<<< orphan*/  mvebu_pmsu_set_cpu_boot_addr (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,unsigned int) ; 
 int /*<<< orphan*/  pr_warn (char*,int) ; 

__attribute__((used)) static int armada_xp_boot_secondary(unsigned int cpu, struct task_struct *idle)
{
	int ret, hw_cpu;

	pr_info("Booting CPU %d\n", cpu);

	hw_cpu = cpu_logical_map(cpu);
	mvebu_pmsu_set_cpu_boot_addr(hw_cpu, armada_xp_secondary_startup);

	/*
	 * This is needed to wake up CPUs in the offline state after
	 * using CPU hotplug.
	 */
	arch_send_wakeup_ipi_mask(cpumask_of(cpu));

	/*
	 * This is needed to take secondary CPUs out of reset on the
	 * initial boot.
	 */
	ret = mvebu_cpu_reset_deassert(hw_cpu);
	if (ret) {
		pr_warn("unable to boot CPU: %d\n", ret);
		return ret;
	}

	return 0;
}