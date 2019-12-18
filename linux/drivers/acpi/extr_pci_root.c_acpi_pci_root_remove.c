#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct acpi_pci_root {TYPE_1__* bus; } ;
struct acpi_device {int /*<<< orphan*/  handle; } ;
struct TYPE_3__ {int /*<<< orphan*/  bridge; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 struct acpi_pci_root* acpi_driver_data (struct acpi_device*) ; 
 int /*<<< orphan*/  acpi_ioapic_remove (struct acpi_pci_root*) ; 
 int /*<<< orphan*/  device_set_wakeup_capable (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dmar_device_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct acpi_pci_root*) ; 
 int /*<<< orphan*/  pci_acpi_remove_bus_pm_notifier (struct acpi_device*) ; 
 int /*<<< orphan*/  pci_ioapic_remove (struct acpi_pci_root*) ; 
 int /*<<< orphan*/  pci_lock_rescan_remove () ; 
 int /*<<< orphan*/  pci_remove_root_bus (TYPE_1__*) ; 
 int /*<<< orphan*/  pci_stop_root_bus (TYPE_1__*) ; 
 int /*<<< orphan*/  pci_unlock_rescan_remove () ; 

__attribute__((used)) static void acpi_pci_root_remove(struct acpi_device *device)
{
	struct acpi_pci_root *root = acpi_driver_data(device);

	pci_lock_rescan_remove();

	pci_stop_root_bus(root->bus);

	pci_ioapic_remove(root);
	device_set_wakeup_capable(root->bus->bridge, false);
	pci_acpi_remove_bus_pm_notifier(device);

	pci_remove_root_bus(root->bus);
	WARN_ON(acpi_ioapic_remove(root));

	dmar_device_remove(device->handle);

	pci_unlock_rescan_remove();

	kfree(root);
}