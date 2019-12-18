#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct cpufreq_policy {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  shared_cpu_map; } ;

/* Variables and functions */
 TYPE_1__* acpi_processor_perf ; 
 int /*<<< orphan*/  acpi_processor_unregister_performance (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_cpumask_var (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 TYPE_1__* powernow_table ; 

__attribute__((used)) static int powernow_cpu_exit(struct cpufreq_policy *policy)
{
#ifdef CONFIG_X86_POWERNOW_K7_ACPI
	if (acpi_processor_perf) {
		acpi_processor_unregister_performance(0);
		free_cpumask_var(acpi_processor_perf->shared_cpu_map);
		kfree(acpi_processor_perf);
	}
#endif

	kfree(powernow_table);
	return 0;
}