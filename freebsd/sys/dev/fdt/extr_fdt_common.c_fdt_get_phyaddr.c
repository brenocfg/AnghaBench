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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  phy_reg ;
typedef  int /*<<< orphan*/  phy_handle ;
typedef  scalar_t__ phandle_t ;
typedef  int pcell_t ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ OF_getencprop (scalar_t__,char*,void*,int) ; 
 scalar_t__ OF_getprop (scalar_t__,char*,void*,int) ; 
 scalar_t__ OF_node_from_xref (int) ; 
 scalar_t__ OF_parent (scalar_t__) ; 
 int /*<<< orphan*/ * device_find_child (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * device_get_parent (int /*<<< orphan*/ *) ; 
 scalar_t__ device_get_softc (int /*<<< orphan*/ *) ; 
 scalar_t__ ofw_bus_get_node (int /*<<< orphan*/ *) ; 

int
fdt_get_phyaddr(phandle_t node, device_t dev, int *phy_addr, void **phy_sc)
{
	phandle_t phy_node;
	pcell_t phy_handle, phy_reg;
	uint32_t i;
	device_t parent, child;

	if (OF_getencprop(node, "phy-handle", (void *)&phy_handle,
	    sizeof(phy_handle)) <= 0)
		return (ENXIO);

	phy_node = OF_node_from_xref(phy_handle);

	if (OF_getencprop(phy_node, "reg", (void *)&phy_reg,
	    sizeof(phy_reg)) <= 0)
		return (ENXIO);

	*phy_addr = phy_reg;

	if (phy_sc == NULL)
		return (0);

	/*
	 * Search for softc used to communicate with phy.
	 */

	/*
	 * Step 1: Search for ancestor of the phy-node with a "phy-handle"
	 * property set.
	 */
	phy_node = OF_parent(phy_node);
	while (phy_node != 0) {
		if (OF_getprop(phy_node, "phy-handle", (void *)&phy_handle,
		    sizeof(phy_handle)) > 0)
			break;
		phy_node = OF_parent(phy_node);
	}
	if (phy_node == 0)
		return (ENXIO);

	/*
	 * Step 2: For each device with the same parent and name as ours
	 * compare its node with the one found in step 1, ancestor of phy
	 * node (stored in phy_node).
	 */
	parent = device_get_parent(dev);
	i = 0;
	child = device_find_child(parent, device_get_name(dev), i);
	while (child != NULL) {
		if (ofw_bus_get_node(child) == phy_node)
			break;
		i++;
		child = device_find_child(parent, device_get_name(dev), i);
	}
	if (child == NULL)
		return (ENXIO);

	/*
	 * Use softc of the device found.
	 */
	*phy_sc = (void *)device_get_softc(child);

	return (0);
}