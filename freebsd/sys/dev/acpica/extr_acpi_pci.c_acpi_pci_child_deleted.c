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
struct acpi_pci_devinfo {int /*<<< orphan*/  ap_handle; } ;
typedef  scalar_t__ device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AcpiDetachData (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_fake_objhandler ; 
 scalar_t__ acpi_get_device (int /*<<< orphan*/ ) ; 
 struct acpi_pci_devinfo* device_get_ivars (scalar_t__) ; 
 int /*<<< orphan*/  pci_child_deleted (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
acpi_pci_child_deleted(device_t dev, device_t child)
{
	struct acpi_pci_devinfo *dinfo = device_get_ivars(child);

	if (acpi_get_device(dinfo->ap_handle) == child)
		AcpiDetachData(dinfo->ap_handle, acpi_fake_objhandler);
	pci_child_deleted(dev, child);
}