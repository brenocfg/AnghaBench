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
struct cpufreq_policy {int /*<<< orphan*/  clk; } ;
struct TYPE_2__ {int /*<<< orphan*/  transition_latency; int /*<<< orphan*/  freq_tbl; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpufreq_generic_init (struct cpufreq_policy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ spear_cpufreq ; 

__attribute__((used)) static int spear_cpufreq_init(struct cpufreq_policy *policy)
{
	policy->clk = spear_cpufreq.clk;
	cpufreq_generic_init(policy, spear_cpufreq.freq_tbl,
			spear_cpufreq.transition_latency);
	return 0;
}