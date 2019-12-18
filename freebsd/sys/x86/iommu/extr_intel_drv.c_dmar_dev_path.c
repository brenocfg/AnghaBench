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
typedef  int /*<<< orphan*/  device_t ;
typedef  scalar_t__ devclass_t ;
struct TYPE_2__ {int /*<<< orphan*/  Function; int /*<<< orphan*/  Device; } ;
typedef  TYPE_1__ ACPI_DMAR_PCI_PATH ;

/* Variables and functions */
 scalar_t__ devclass_find (char*) ; 
 scalar_t__ device_get_devclass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  pci_get_function (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_slot (int /*<<< orphan*/ ) ; 
 int pcib_get_bus (int /*<<< orphan*/ ) ; 

void
dmar_dev_path(device_t child, int *busno, void *path1, int depth)
{
	devclass_t pci_class;
	device_t bus, pcib;
	ACPI_DMAR_PCI_PATH *path;

	pci_class = devclass_find("pci");
	path = path1;
	for (depth--; depth != -1; depth--) {
		path[depth].Device = pci_get_slot(child);
		path[depth].Function = pci_get_function(child);
		bus = device_get_parent(child);
		pcib = device_get_parent(bus);
		if (device_get_devclass(device_get_parent(pcib)) !=
		    pci_class) {
			/* reached a host bridge */
			*busno = pcib_get_bus(bus);
			return;
		}
		child = pcib;
	}
	panic("wrong depth");
}