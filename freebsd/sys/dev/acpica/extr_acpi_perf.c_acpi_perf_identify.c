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
typedef  int /*<<< orphan*/  driver_t ;
typedef  int /*<<< orphan*/ * device_t ;
typedef  int /*<<< orphan*/ * ACPI_HANDLE ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiEvaluateObject (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BUS_ADD_CHILD (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/ * acpi_get_handle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * device_find_child (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  device_probe_and_attach (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
acpi_perf_identify(driver_t *driver, device_t parent)
{
	ACPI_HANDLE handle;
	device_t dev;

	/* Make sure we're not being doubly invoked. */
	if (device_find_child(parent, "acpi_perf", -1) != NULL)
		return;

	/* Get the handle for the Processor object and check for perf states. */
	handle = acpi_get_handle(parent);
	if (handle == NULL)
		return;
	if (ACPI_FAILURE(AcpiEvaluateObject(handle, "_PSS", NULL, NULL)))
		return;

	/*
	 * Add a child to every CPU that has the right methods.  In future
	 * versions of the ACPI spec, CPUs can have different settings.
	 * We probe this child now so that other devices that depend
	 * on it (i.e., for info about supported states) will see it.
	 */
	if ((dev = BUS_ADD_CHILD(parent, 0, "acpi_perf", -1)) != NULL)
		device_probe_and_attach(dev);
	else
		device_printf(parent, "add acpi_perf child failed\n");
}