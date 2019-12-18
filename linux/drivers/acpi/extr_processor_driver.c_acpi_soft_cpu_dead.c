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
struct acpi_processor {int /*<<< orphan*/  handle; } ;
struct acpi_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ acpi_bus_get_device (int /*<<< orphan*/ ,struct acpi_device**) ; 
 int /*<<< orphan*/  acpi_processor_reevaluate_tstate (struct acpi_processor*,int) ; 
 struct acpi_processor* per_cpu (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  processors ; 

__attribute__((used)) static int acpi_soft_cpu_dead(unsigned int cpu)
{
	struct acpi_processor *pr = per_cpu(processors, cpu);
	struct acpi_device *device;

	if (!pr || acpi_bus_get_device(pr->handle, &device))
		return 0;

	acpi_processor_reevaluate_tstate(pr, true);
	return 0;
}