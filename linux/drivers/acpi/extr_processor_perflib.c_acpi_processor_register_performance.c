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
struct acpi_processor_performance {int dummy; } ;
struct acpi_processor {struct acpi_processor_performance* performance; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int EIO ; 
 int ENODEV ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  acpi_processor_cpufreq_init ; 
 scalar_t__ acpi_processor_get_performance_info (struct acpi_processor*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct acpi_processor* per_cpu (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  performance_mutex ; 
 int /*<<< orphan*/  processors ; 

int
acpi_processor_register_performance(struct acpi_processor_performance
				    *performance, unsigned int cpu)
{
	struct acpi_processor *pr;

	if (!acpi_processor_cpufreq_init)
		return -EINVAL;

	mutex_lock(&performance_mutex);

	pr = per_cpu(processors, cpu);
	if (!pr) {
		mutex_unlock(&performance_mutex);
		return -ENODEV;
	}

	if (pr->performance) {
		mutex_unlock(&performance_mutex);
		return -EBUSY;
	}

	WARN_ON(!performance);

	pr->performance = performance;

	if (acpi_processor_get_performance_info(pr)) {
		pr->performance = NULL;
		mutex_unlock(&performance_mutex);
		return -EIO;
	}

	mutex_unlock(&performance_mutex);
	return 0;
}