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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_HP_WMI_BIOS_GUID ; 
 int /*<<< orphan*/  ACPI_WMI_PROVIDES_GUID_STRING (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * BUS_ADD_CHILD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ acpi_disabled (char*) ; 
 int /*<<< orphan*/ * device_find_child (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
acpi_hp_identify(driver_t *driver, device_t parent)
{

	/* Don't do anything if driver is disabled. */
	if (acpi_disabled("hp"))
		return;

	/* Add only a single device instance. */
	if (device_find_child(parent, "acpi_hp", -1) != NULL)
		return;

	/* Check BIOS GUID to see whether system is compatible. */
	if (!ACPI_WMI_PROVIDES_GUID_STRING(parent,
	    ACPI_HP_WMI_BIOS_GUID))
		return;

	if (BUS_ADD_CHILD(parent, 0, "acpi_hp", -1) == NULL)
		device_printf(parent, "add acpi_hp child failed\n");
}