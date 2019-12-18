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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  enum pci_id_type { ____Placeholder_pci_id_type } pci_id_type ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int PCI_ID_RID ; 
 uintptr_t PCI_RID (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_bus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_function (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_slot (int /*<<< orphan*/ ) ; 

int
pcib_get_id(device_t pcib, device_t dev, enum pci_id_type type, uintptr_t *id)
{
	uint8_t bus, slot, func;

	if (type != PCI_ID_RID)
		return (ENXIO);

	bus = pci_get_bus(dev);
	slot = pci_get_slot(dev);
	func = pci_get_function(dev);

	*id = (PCI_RID(bus, slot, func));
	return (0);
}