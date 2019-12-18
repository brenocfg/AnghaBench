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
struct notifier_block {int dummy; } ;
struct cpufreq_policy {int dummy; } ;

/* Variables and functions */
 unsigned long CPUFREQ_CREATE_POLICY ; 
 unsigned long CPUFREQ_REMOVE_POLICY ; 
 int /*<<< orphan*/  acpi_processor_ppc_exit (struct cpufreq_policy*) ; 
 int /*<<< orphan*/  acpi_processor_ppc_init (struct cpufreq_policy*) ; 
 int /*<<< orphan*/  acpi_thermal_cpufreq_exit (struct cpufreq_policy*) ; 
 int /*<<< orphan*/  acpi_thermal_cpufreq_init (struct cpufreq_policy*) ; 

__attribute__((used)) static int acpi_processor_notifier(struct notifier_block *nb,
				   unsigned long event, void *data)
{
	struct cpufreq_policy *policy = data;

	if (event == CPUFREQ_CREATE_POLICY) {
		acpi_thermal_cpufreq_init(policy);
		acpi_processor_ppc_init(policy);
	} else if (event == CPUFREQ_REMOVE_POLICY) {
		acpi_processor_ppc_exit(policy);
		acpi_thermal_cpufreq_exit(policy);
	}

	return 0;
}