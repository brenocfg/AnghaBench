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
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,int,int,int) ; 
 int pci_get_bus (int /*<<< orphan*/ ) ; 
 int pci_get_function (int /*<<< orphan*/ ) ; 
 int pci_get_slot (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
gt_pci_route_interrupt(device_t pcib, device_t dev, int pin)
{
	int bus;
	int device;
	int func;
	/* struct gt_pci_softc *sc = device_get_softc(pcib); */
	bus = pci_get_bus(dev);
	device = pci_get_slot(dev);
	func = pci_get_function(dev);
	/* 
	 * XXXMIPS: We need routing logic. This is just a stub .
	 */
	switch (device) {
	case 9: /*
		 * PIIX4 IDE adapter. HW IRQ0
		 */
		return 0;
	case 11: /* Ethernet */
		return 10;
	default:
		device_printf(pcib, "no IRQ mapping for %d/%d/%d/%d\n", bus, device, func, pin);
		
	}
	return (0);

}