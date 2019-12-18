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
struct cpudata {int update_util_set; } ;

/* Variables and functions */
 struct cpudata** all_cpu_data ; 
 int /*<<< orphan*/  cpufreq_remove_update_util_hook (unsigned int) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

__attribute__((used)) static void intel_pstate_clear_update_util_hook(unsigned int cpu)
{
	struct cpudata *cpu_data = all_cpu_data[cpu];

	if (!cpu_data->update_util_set)
		return;

	cpufreq_remove_update_util_hook(cpu);
	cpu_data->update_util_set = false;
	synchronize_rcu();
}