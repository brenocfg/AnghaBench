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
struct tegra20_cpufreq {int pll_x_prepared; int /*<<< orphan*/  pll_x_clk; int /*<<< orphan*/  cpu_clk; int /*<<< orphan*/  dev; int /*<<< orphan*/  pll_p_clk; } ;
struct cpufreq_policy {int dummy; } ;
struct TYPE_2__ {unsigned long frequency; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_get_rate (int /*<<< orphan*/ ) ; 
 int clk_set_parent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int clk_set_rate (int /*<<< orphan*/ ,unsigned long) ; 
 struct tegra20_cpufreq* cpufreq_get_driver_data () ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned long) ; 
 TYPE_1__* freq_table ; 

__attribute__((used)) static int tegra_target(struct cpufreq_policy *policy, unsigned int index)
{
	struct tegra20_cpufreq *cpufreq = cpufreq_get_driver_data();
	unsigned long rate = freq_table[index].frequency;
	unsigned int ifreq = clk_get_rate(cpufreq->pll_p_clk) / 1000;
	int ret;

	/*
	 * target freq == pll_p, don't need to take extra reference to pll_x_clk
	 * as it isn't used anymore.
	 */
	if (rate == ifreq)
		return clk_set_parent(cpufreq->cpu_clk, cpufreq->pll_p_clk);

	ret = clk_set_rate(cpufreq->pll_x_clk, rate * 1000);
	/* Restore to earlier frequency on error, i.e. pll_x */
	if (ret)
		dev_err(cpufreq->dev, "Failed to change pll_x to %lu\n", rate);

	ret = clk_set_parent(cpufreq->cpu_clk, cpufreq->pll_x_clk);
	/* This shouldn't fail while changing or restoring */
	WARN_ON(ret);

	/*
	 * Drop count to pll_x clock only if we switched to intermediate freq
	 * earlier while transitioning to a target frequency.
	 */
	if (cpufreq->pll_x_prepared) {
		clk_disable_unprepare(cpufreq->pll_x_clk);
		cpufreq->pll_x_prepared = false;
	}

	return ret;
}