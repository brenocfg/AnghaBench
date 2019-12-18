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
struct tegra20_cpufreq {int pll_x_prepared; int /*<<< orphan*/  pll_x_clk; int /*<<< orphan*/  pll_p_clk; int /*<<< orphan*/  cpu_clk; } ;
struct cpufreq_policy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int clk_set_parent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tegra20_cpufreq* cpufreq_get_driver_data () ; 

__attribute__((used)) static int tegra_target_intermediate(struct cpufreq_policy *policy,
				     unsigned int index)
{
	struct tegra20_cpufreq *cpufreq = cpufreq_get_driver_data();
	int ret;

	/*
	 * Take an extra reference to the main pll so it doesn't turn
	 * off when we move the cpu off of it as enabling it again while we
	 * switch to it from tegra_target() would take additional time.
	 *
	 * When target-freq is equal to intermediate freq we don't need to
	 * switch to an intermediate freq and so this routine isn't called.
	 * Also, we wouldn't be using pll_x anymore and must not take extra
	 * reference to it, as it can be disabled now to save some power.
	 */
	clk_prepare_enable(cpufreq->pll_x_clk);

	ret = clk_set_parent(cpufreq->cpu_clk, cpufreq->pll_p_clk);
	if (ret)
		clk_disable_unprepare(cpufreq->pll_x_clk);
	else
		cpufreq->pll_x_prepared = true;

	return ret;
}