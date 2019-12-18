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
 unsigned int cpu_logical_map (unsigned int) ; 
 scalar_t__ cpumask_test_cpu (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flowctrl_write_cpu_csr (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flowctrl_write_cpu_halt (unsigned int,int /*<<< orphan*/ ) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  tegra_cpu_init_mask ; 
 int /*<<< orphan*/  tegra_cpu_out_of_reset (unsigned int) ; 
 int /*<<< orphan*/  tegra_enable_cpu_clock (unsigned int) ; 
 scalar_t__ tegra_pmc_cpu_is_powered (unsigned int) ; 
 int tegra_pmc_cpu_power_on (unsigned int) ; 
 int tegra_pmc_cpu_remove_clamping (unsigned int) ; 
 int /*<<< orphan*/  tegra_put_cpu_in_reset (unsigned int) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int tegra30_boot_secondary(unsigned int cpu, struct task_struct *idle)
{
	int ret;
	unsigned long timeout;

	cpu = cpu_logical_map(cpu);
	tegra_put_cpu_in_reset(cpu);
	flowctrl_write_cpu_halt(cpu, 0);

	/*
	 * The power up sequence of cold boot CPU and warm boot CPU
	 * was different.
	 *
	 * For warm boot CPU that was resumed from CPU hotplug, the
	 * power will be resumed automatically after un-halting the
	 * flow controller of the warm boot CPU. We need to wait for
	 * the confirmaiton that the CPU is powered then removing
	 * the IO clamps.
	 * For cold boot CPU, do not wait. After the cold boot CPU be
	 * booted, it will run to tegra_secondary_init() and set
	 * tegra_cpu_init_mask which influences what tegra30_boot_secondary()
	 * next time around.
	 */
	if (cpumask_test_cpu(cpu, &tegra_cpu_init_mask)) {
		timeout = jiffies + msecs_to_jiffies(50);
		do {
			if (tegra_pmc_cpu_is_powered(cpu))
				goto remove_clamps;
			udelay(10);
		} while (time_before(jiffies, timeout));
	}

	/*
	 * The power status of the cold boot CPU is power gated as
	 * default. To power up the cold boot CPU, the power should
	 * be un-gated by un-toggling the power gate register
	 * manually.
	 */
	ret = tegra_pmc_cpu_power_on(cpu);
	if (ret)
		return ret;

remove_clamps:
	/* CPU partition is powered. Enable the CPU clock. */
	tegra_enable_cpu_clock(cpu);
	udelay(10);

	/* Remove I/O clamps. */
	ret = tegra_pmc_cpu_remove_clamping(cpu);
	if (ret)
		return ret;

	udelay(10);

	flowctrl_write_cpu_csr(cpu, 0); /* Clear flow controller CSR. */
	tegra_cpu_out_of_reset(cpu);
	return 0;
}