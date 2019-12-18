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
 int /*<<< orphan*/  CONFIG_ARCH_TEGRA_114_SOC ; 
 int /*<<< orphan*/  CONFIG_ARCH_TEGRA_124_SOC ; 
 int /*<<< orphan*/  CONFIG_ARCH_TEGRA_2x_SOC ; 
 int /*<<< orphan*/  CONFIG_ARCH_TEGRA_3x_SOC ; 
 int EINVAL ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ TEGRA114 ; 
 scalar_t__ TEGRA124 ; 
 scalar_t__ TEGRA20 ; 
 scalar_t__ TEGRA30 ; 
 int tegra114_boot_secondary (unsigned int,struct task_struct*) ; 
 int tegra20_boot_secondary (unsigned int,struct task_struct*) ; 
 int tegra30_boot_secondary (unsigned int,struct task_struct*) ; 
 scalar_t__ tegra_get_chip_id () ; 

__attribute__((used)) static int tegra_boot_secondary(unsigned int cpu,
					  struct task_struct *idle)
{
	if (IS_ENABLED(CONFIG_ARCH_TEGRA_2x_SOC) && tegra_get_chip_id() == TEGRA20)
		return tegra20_boot_secondary(cpu, idle);
	if (IS_ENABLED(CONFIG_ARCH_TEGRA_3x_SOC) && tegra_get_chip_id() == TEGRA30)
		return tegra30_boot_secondary(cpu, idle);
	if (IS_ENABLED(CONFIG_ARCH_TEGRA_114_SOC) && tegra_get_chip_id() == TEGRA114)
		return tegra114_boot_secondary(cpu, idle);
	if (IS_ENABLED(CONFIG_ARCH_TEGRA_124_SOC) && tegra_get_chip_id() == TEGRA124)
		return tegra114_boot_secondary(cpu, idle);

	return -EINVAL;
}