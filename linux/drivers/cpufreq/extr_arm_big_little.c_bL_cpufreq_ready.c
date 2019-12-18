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
struct cpufreq_policy {int /*<<< orphan*/  cpu; } ;

/* Variables and functions */
 int MAX_CLUSTERS ; 
 int /*<<< orphan*/ * cdev ; 
 int cpu_to_cluster (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_cpufreq_cooling_register (struct cpufreq_policy*) ; 

__attribute__((used)) static void bL_cpufreq_ready(struct cpufreq_policy *policy)
{
	int cur_cluster = cpu_to_cluster(policy->cpu);

	/* Do not register a cpu_cooling device if we are in IKS mode */
	if (cur_cluster >= MAX_CLUSTERS)
		return;

	cdev[cur_cluster] = of_cpufreq_cooling_register(policy);
}