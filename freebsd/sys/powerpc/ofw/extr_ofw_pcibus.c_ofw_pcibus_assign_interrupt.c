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
typedef  int phandle_t ;
typedef  int ofw_pci_intr_t ;
typedef  int /*<<< orphan*/  iparent ;
typedef  int /*<<< orphan*/  intr ;
typedef  int /*<<< orphan*/  icells ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int OF_getencprop (int,char*,int*,int) ; 
 int OF_node_from_xref (int) ; 
 int PCIB_ROUTE_INTERRUPT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int ofw_bus_map_intr (int /*<<< orphan*/ ,int,int,int*) ; 
 int pci_get_intpin (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ofw_pcibus_assign_interrupt(device_t dev, device_t child)
{
	ofw_pci_intr_t intr[2];
	phandle_t node, iparent;
	int isz, icells;

	node = ofw_bus_get_node(child);

	if (node == -1) {
		/* Non-firmware enumerated child, use standard routing */
	
		intr[0] = pci_get_intpin(child);
		return (PCIB_ROUTE_INTERRUPT(device_get_parent(dev), child, 
		    intr[0]));
	}
	
	/*
	 * Try to determine the node's interrupt parent so we know which
	 * PIC to use.
	 */

	iparent = -1;
	if (OF_getencprop(node, "interrupt-parent", &iparent,
	    sizeof(iparent)) < 0)
		iparent = -1;
	icells = 1;
	if (iparent != -1)
		OF_getencprop(OF_node_from_xref(iparent), "#interrupt-cells",
		    &icells, sizeof(icells));
	
	/*
	 * Any AAPL,interrupts property gets priority and is
	 * fully specified (i.e. does not need routing)
	 */

	isz = OF_getencprop(node, "AAPL,interrupts", intr, sizeof(intr));
	if (isz == sizeof(intr[0])*icells)
		return ((iparent == -1) ? intr[0] : ofw_bus_map_intr(dev,
		    iparent, icells, intr));

	isz = OF_getencprop(node, "interrupts", intr, sizeof(intr));
	if (isz == sizeof(intr[0])*icells) {
		if (iparent != -1)
			intr[0] = ofw_bus_map_intr(dev, iparent, icells, intr);
	} else {
		/* No property: our best guess is the intpin. */
		intr[0] = pci_get_intpin(child);
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
	return (PCIB_ROUTE_INTERRUPT(device_get_parent(dev), child, intr[0]));
}