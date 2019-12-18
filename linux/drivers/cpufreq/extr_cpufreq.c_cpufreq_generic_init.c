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
struct TYPE_2__ {unsigned int transition_latency; } ;
struct cpufreq_policy {int /*<<< orphan*/  cpus; TYPE_1__ cpuinfo; struct cpufreq_frequency_table* freq_table; } ;
struct cpufreq_frequency_table {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpumask_setall (int /*<<< orphan*/ ) ; 

void cpufreq_generic_init(struct cpufreq_policy *policy,
		struct cpufreq_frequency_table *table,
		unsigned int transition_latency)
{
	policy->freq_table = table;
	policy->cpuinfo.transition_latency = transition_latency;

	/*
	 * The driver only supports the SMP configuration where all processors
	 * share the clock and voltage and clock.
	 */
	cpumask_setall(policy->cpus);
}