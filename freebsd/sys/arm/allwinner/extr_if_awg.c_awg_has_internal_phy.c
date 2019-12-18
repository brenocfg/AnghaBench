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
typedef  scalar_t__ phandle_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ OF_hasprop (scalar_t__,char*) ; 
 int /*<<< orphan*/  OF_parent (scalar_t__) ; 
 scalar_t__ awg_get_phy_node (int /*<<< orphan*/ ) ; 
 scalar_t__ ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 scalar_t__ ofw_bus_node_is_compatible (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static bool
awg_has_internal_phy(device_t dev)
{
	phandle_t node, phy_node;

	node = ofw_bus_get_node(dev);
	/* Legacy binding */
	if (OF_hasprop(node, "allwinner,use-internal-phy"))
		return (true);

	phy_node = awg_get_phy_node(dev);
	return (phy_node != 0 && ofw_bus_node_is_compatible(OF_parent(phy_node),
	    "allwinner,sun8i-h3-mdio-internal") != 0);
}