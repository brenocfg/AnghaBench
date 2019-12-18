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
struct cpufreq_policy {size_t cpu; struct cpufreq_acpi_io* freq_table; } ;
struct cpufreq_acpi_io {int dummy; } ;

/* Variables and functions */
 struct cpufreq_acpi_io** acpi_io_data ; 
 int /*<<< orphan*/  acpi_processor_unregister_performance (size_t) ; 
 int /*<<< orphan*/  kfree (struct cpufreq_acpi_io*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

__attribute__((used)) static int
acpi_cpufreq_cpu_exit (
	struct cpufreq_policy   *policy)
{
	struct cpufreq_acpi_io *data = acpi_io_data[policy->cpu];

	pr_debug("acpi_cpufreq_cpu_exit\n");

	if (data) {
		acpi_io_data[policy->cpu] = NULL;
		acpi_processor_unregister_performance(policy->cpu);
		kfree(policy->freq_table);
		kfree(data);
	}

	return (0);
}