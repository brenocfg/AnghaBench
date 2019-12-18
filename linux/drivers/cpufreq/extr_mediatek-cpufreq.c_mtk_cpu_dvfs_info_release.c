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
struct mtk_cpu_dvfs_info {int /*<<< orphan*/  cpus; int /*<<< orphan*/  inter_clk; int /*<<< orphan*/  cpu_clk; int /*<<< orphan*/  sram_reg; int /*<<< orphan*/  proc_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_pm_opp_of_cpumask_remove_table (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regulator_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mtk_cpu_dvfs_info_release(struct mtk_cpu_dvfs_info *info)
{
	if (!IS_ERR(info->proc_reg))
		regulator_put(info->proc_reg);
	if (!IS_ERR(info->sram_reg))
		regulator_put(info->sram_reg);
	if (!IS_ERR(info->cpu_clk))
		clk_put(info->cpu_clk);
	if (!IS_ERR(info->inter_clk))
		clk_put(info->inter_clk);

	dev_pm_opp_of_cpumask_remove_table(&info->cpus);
}