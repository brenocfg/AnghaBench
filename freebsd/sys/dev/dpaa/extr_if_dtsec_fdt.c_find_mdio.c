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
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  OF_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_find_child_device_by_phandle (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ofw_bus_node_is_compatible (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
find_mdio(phandle_t phy_node, device_t mac, device_t *mdio_dev)
{
	device_t bus;

	while (phy_node > 0) {
		if (ofw_bus_node_is_compatible(phy_node, "fsl,fman-mdio"))
			break;
		phy_node = OF_parent(phy_node);
	}

	if (phy_node <= 0)
		return (ENOENT);

	bus = device_get_parent(mac);
	*mdio_dev = ofw_bus_find_child_device_by_phandle(bus, phy_node);

	return (0);
}