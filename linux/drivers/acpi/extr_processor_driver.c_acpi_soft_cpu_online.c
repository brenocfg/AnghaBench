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
struct TYPE_2__ {scalar_t__ need_hotplug_init; } ;
struct acpi_processor {int /*<<< orphan*/  id; TYPE_1__ flags; int /*<<< orphan*/  handle; } ;
struct acpi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN (int,char*,int /*<<< orphan*/ ) ; 
 int __acpi_processor_start (struct acpi_device*) ; 
 scalar_t__ acpi_bus_get_device (int /*<<< orphan*/ ,struct acpi_device**) ; 
 int /*<<< orphan*/  acpi_processor_hotplug (struct acpi_processor*) ; 
 int /*<<< orphan*/  acpi_processor_ppc_has_changed (struct acpi_processor*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_processor_reevaluate_tstate (struct acpi_processor*,int) ; 
 int /*<<< orphan*/  acpi_processor_tstate_has_changed (struct acpi_processor*) ; 
 struct acpi_processor* per_cpu (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  processors ; 

__attribute__((used)) static int acpi_soft_cpu_online(unsigned int cpu)
{
	struct acpi_processor *pr = per_cpu(processors, cpu);
	struct acpi_device *device;

	if (!pr || acpi_bus_get_device(pr->handle, &device))
		return 0;
	/*
	 * CPU got physically hotplugged and onlined for the first time:
	 * Initialize missing things.
	 */
	if (pr->flags.need_hotplug_init) {
		int ret;

		pr_info("Will online and init hotplugged CPU: %d\n",
			pr->id);
		pr->flags.need_hotplug_init = 0;
		ret = __acpi_processor_start(device);
		WARN(ret, "Failed to start CPU: %d\n", pr->id);
	} else {
		/* Normal CPU soft online event. */
		acpi_processor_ppc_has_changed(pr, 0);
		acpi_processor_hotplug(pr);
		acpi_processor_reevaluate_tstate(pr, false);
		acpi_processor_tstate_has_changed(pr);
	}
	return 0;
}