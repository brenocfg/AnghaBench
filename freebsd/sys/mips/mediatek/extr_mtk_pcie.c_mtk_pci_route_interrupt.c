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

/* Variables and functions */
 int MTK_PCIE0_IRQ ; 
 int /*<<< orphan*/  panic (char*,int) ; 
 int pci_get_bus (int /*<<< orphan*/ ) ; 
 int pci_get_device (int /*<<< orphan*/ ) ; 
 int pci_get_slot (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mtk_pci_route_interrupt(device_t pcib, device_t device, int pin)
{
	int bus, sl, dev;

	bus = pci_get_bus(device);
	sl = pci_get_slot(device);
	dev = pci_get_device(device);

	if (bus != 0)
		panic("Unexpected bus number %d\n", bus);

	/* PCIe only */
	switch (sl) {
	case 0: return MTK_PCIE0_IRQ;
	case 1: return MTK_PCIE0_IRQ + 1;
	case 2: return MTK_PCIE0_IRQ + 2;
	default: return (-1);
	}

	return (-1);
}