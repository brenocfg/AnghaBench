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
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  ACPI_HANDLE ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiGetHandle (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int ENXIO ; 
 scalar_t__ acpi_disabled (char*) ; 
 int /*<<< orphan*/  acpi_get_handle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
acpi_dock_probe(device_t dev)
{
	ACPI_HANDLE	h, tmp;

	h = acpi_get_handle(dev);
	if (acpi_disabled("dock") ||
	    ACPI_FAILURE(AcpiGetHandle(h, "_DCK", &tmp)))
		return (ENXIO);

	device_set_desc(dev, "ACPI Docking Station");

	/*
	 * XXX Somewhere else in the kernel panics on "sysctl kern" if we
	 * return a negative value here (reprobe ok).
	 */
	return (0);
}