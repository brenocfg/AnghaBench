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
struct acpi_processor {TYPE_1__* performance; } ;
struct TYPE_2__ {int /*<<< orphan*/  states; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct acpi_processor* per_cpu (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  performance_mutex ; 
 int /*<<< orphan*/  processors ; 

void acpi_processor_unregister_performance(unsigned int cpu)
{
	struct acpi_processor *pr;

	mutex_lock(&performance_mutex);

	pr = per_cpu(processors, cpu);
	if (!pr) {
		mutex_unlock(&performance_mutex);
		return;
	}

	if (pr->performance)
		kfree(pr->performance->states);
	pr->performance = NULL;

	mutex_unlock(&performance_mutex);

	return;
}