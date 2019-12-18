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
struct subsys_interface {int dummy; } ;
struct device {unsigned int id; } ;
struct cpufreq_policy {int /*<<< orphan*/  real_cpus; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* exit ) (struct cpufreq_policy*) ;scalar_t__ offline; } ;

/* Variables and functions */
 scalar_t__ cpu_online (unsigned int) ; 
 int /*<<< orphan*/  cpufreq_cpu_data ; 
 TYPE_1__* cpufreq_driver ; 
 int /*<<< orphan*/  cpufreq_offline (unsigned int) ; 
 int /*<<< orphan*/  cpufreq_policy_free (struct cpufreq_policy*) ; 
 int /*<<< orphan*/  cpumask_clear_cpu (unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ cpumask_empty (int /*<<< orphan*/ ) ; 
 struct cpufreq_policy* per_cpu (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  remove_cpu_dev_symlink (struct cpufreq_policy*,struct device*) ; 
 int /*<<< orphan*/  stub1 (struct cpufreq_policy*) ; 

__attribute__((used)) static void cpufreq_remove_dev(struct device *dev, struct subsys_interface *sif)
{
	unsigned int cpu = dev->id;
	struct cpufreq_policy *policy = per_cpu(cpufreq_cpu_data, cpu);

	if (!policy)
		return;

	if (cpu_online(cpu))
		cpufreq_offline(cpu);

	cpumask_clear_cpu(cpu, policy->real_cpus);
	remove_cpu_dev_symlink(policy, dev);

	if (cpumask_empty(policy->real_cpus)) {
		/* We did light-weight exit earlier, do full tear down now */
		if (cpufreq_driver->offline)
			cpufreq_driver->exit(policy);

		cpufreq_policy_free(policy);
	}
}