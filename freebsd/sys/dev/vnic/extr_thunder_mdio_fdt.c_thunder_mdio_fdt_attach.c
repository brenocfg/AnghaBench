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
 int /*<<< orphan*/  OF_device_register_xref (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OF_xref_from_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int thunder_mdio_attach (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
thunder_mdio_fdt_attach(device_t dev)
{
	phandle_t node;
	int ret;

	/* Call core attach */
	ret = thunder_mdio_attach(dev);
	if (ret != 0)
		return (ret);
	/*
	 * Register device to this node/xref.
	 * Thanks to that we will be able to retrieve device_t structure
	 * while holding only node reference acquired from FDT.
	 */
	node = ofw_bus_get_node(dev);
	OF_device_register_xref(OF_xref_from_node(node), dev);

	return (0);
}