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
struct TYPE_2__ {int driver_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_set_rate (int /*<<< orphan*/ ,unsigned int) ; 
 int cpu_clock_freq ; 
 TYPE_1__* loongson2_clockmod_table ; 

__attribute__((used)) static int loongson2_cpufreq_target(struct cpufreq_policy *policy,
				     unsigned int index)
{
	unsigned int freq;

	freq =
	    ((cpu_clock_freq / 1000) *
	     loongson2_clockmod_table[index].driver_data) / 8;

	/* setting the cpu frequency */
	clk_set_rate(policy->clk, freq * 1000);

	return 0;
}