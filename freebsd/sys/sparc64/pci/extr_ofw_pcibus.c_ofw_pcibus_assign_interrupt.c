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
typedef  int ofw_pci_intr_t ;
typedef  int /*<<< orphan*/  intr ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int INTINO (int) ; 
 int OF_getprop (int /*<<< orphan*/ ,char*,int*,int) ; 
 int PCIB_ROUTE_INTERRUPT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int pci_get_intpin (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ofw_pcibus_assign_interrupt(device_t dev, device_t child)
{
	ofw_pci_intr_t intr;
	int isz;

	isz = OF_getprop(ofw_bus_get_node(child), "interrupts", &intr,
	    sizeof(intr));
	if (isz != sizeof(intr)) {
		/* No property; our best guess is the intpin. */
		intr = pci_get_intpin(child);
#ifndef SUN4V
	} else if (intr >= 255) {
		/*
		 * A fully specified interrupt (including IGN), as present on
		 * SPARCengine Ultra AX and E450.  Extract the INO and return
		 * it.
		 */
		return (INTINO(intr));
#endif
	}
	/*
	 * If we got intr from a property, it may or may not be an intpin.
	 * For on-board devices, it frequently is not, and is completely out
	 * of the valid intpin range.  For PCI slots, it hopefully is,
	 * otherwise we will have trouble interfacing with non-OFW buses
	 * such as cardbus.
	 * Since we cannot tell which it is without violating layering, we
	 * will always use the route_interrupt method, and treat exceptions
	 * on the level they become apparent.
	 */
	return (PCIB_ROUTE_INTERRUPT(device_get_parent(dev), child, intr));
}