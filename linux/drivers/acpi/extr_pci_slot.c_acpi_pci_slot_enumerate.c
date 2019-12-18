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
struct pci_bus {int /*<<< orphan*/  bridge; } ;
typedef  scalar_t__ acpi_handle ;

/* Variables and functions */
 scalar_t__ ACPI_HANDLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_TYPE_DEVICE ; 
 int /*<<< orphan*/  acpi_walk_namespace (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct pci_bus*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  register_slot ; 
 int /*<<< orphan*/  slot_list_lock ; 

void acpi_pci_slot_enumerate(struct pci_bus *bus)
{
	acpi_handle handle = ACPI_HANDLE(bus->bridge);

	if (handle) {
		mutex_lock(&slot_list_lock);
		acpi_walk_namespace(ACPI_TYPE_DEVICE, handle, 1,
				    register_slot, NULL, bus, NULL);
		mutex_unlock(&slot_list_lock);
	}
}