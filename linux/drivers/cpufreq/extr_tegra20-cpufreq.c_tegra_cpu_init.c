#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tegra20_cpufreq {int /*<<< orphan*/  cpu_clk; } ;
struct cpufreq_policy {int /*<<< orphan*/  suspend_freq; int /*<<< orphan*/  clk; } ;
struct TYPE_3__ {int /*<<< orphan*/  frequency; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpufreq_generic_init (struct cpufreq_policy*,TYPE_1__*,int) ; 
 struct tegra20_cpufreq* cpufreq_get_driver_data () ; 
 TYPE_1__* freq_table ; 

__attribute__((used)) static int tegra_cpu_init(struct cpufreq_policy *policy)
{
	struct tegra20_cpufreq *cpufreq = cpufreq_get_driver_data();

	clk_prepare_enable(cpufreq->cpu_clk);

	/* FIXME: what's the actual transition time? */
	cpufreq_generic_init(policy, freq_table, 300 * 1000);
	policy->clk = cpufreq->cpu_clk;
	policy->suspend_freq = freq_table[0].frequency;
	return 0;
}