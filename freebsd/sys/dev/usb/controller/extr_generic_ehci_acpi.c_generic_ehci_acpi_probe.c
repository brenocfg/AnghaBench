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
typedef  int /*<<< orphan*/ * ACPI_HANDLE ;

/* Variables and functions */
 int BUS_PROBE_DEFAULT ; 
 int ENXIO ; 
 int /*<<< orphan*/  acpi_MatchHid (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * acpi_get_handle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
generic_ehci_acpi_probe(device_t self)
{
	ACPI_HANDLE h;

	if ((h = acpi_get_handle(self)) == NULL ||
	    !acpi_MatchHid(h, "PNP0D20"))
		return (ENXIO);

	device_set_desc(self, "Generic EHCI Controller");
	return (BUS_PROBE_DEFAULT);
}