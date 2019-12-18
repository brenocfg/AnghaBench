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
struct cpufreq_policy {int /*<<< orphan*/  cpus; int /*<<< orphan*/  suspend_freq; int /*<<< orphan*/  clk; } ;
struct TYPE_2__ {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 size_t ARM ; 
 TYPE_1__* clks ; 
 int /*<<< orphan*/  cpufreq_generic_init (struct cpufreq_policy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_pm_opp_of_register_em (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  freq_table ; 
 int /*<<< orphan*/  max_freq ; 
 int /*<<< orphan*/  transition_latency ; 

__attribute__((used)) static int imx6q_cpufreq_init(struct cpufreq_policy *policy)
{
	policy->clk = clks[ARM].clk;
	cpufreq_generic_init(policy, freq_table, transition_latency);
	policy->suspend_freq = max_freq;
	dev_pm_opp_of_register_em(policy->cpus);

	return 0;
}