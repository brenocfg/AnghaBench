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
struct tegra20_cpufreq {int /*<<< orphan*/  pll_p_clk; } ;
struct cpufreq_policy {unsigned int cur; } ;
struct TYPE_2__ {unsigned int frequency; } ;

/* Variables and functions */
 int clk_get_rate (int /*<<< orphan*/ ) ; 
 struct tegra20_cpufreq* cpufreq_get_driver_data () ; 
 TYPE_1__* freq_table ; 

__attribute__((used)) static unsigned int tegra_get_intermediate(struct cpufreq_policy *policy,
					   unsigned int index)
{
	struct tegra20_cpufreq *cpufreq = cpufreq_get_driver_data();
	unsigned int ifreq = clk_get_rate(cpufreq->pll_p_clk) / 1000;

	/*
	 * Don't switch to intermediate freq if:
	 * - we are already at it, i.e. policy->cur == ifreq
	 * - index corresponds to ifreq
	 */
	if (freq_table[index].frequency == ifreq || policy->cur == ifreq)
		return 0;

	return ifreq;
}