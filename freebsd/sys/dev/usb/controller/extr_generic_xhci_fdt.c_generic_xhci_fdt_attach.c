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
typedef  int /*<<< orphan*/  phy_t ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int generic_xhci_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 scalar_t__ phy_enable (int /*<<< orphan*/ ) ; 
 scalar_t__ phy_get_by_ofw_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
generic_xhci_fdt_attach(device_t dev)
{
#ifdef EXT_RESOURCES
	phandle_t node;
	phy_t phy;

	node = ofw_bus_get_node(dev);
	if (phy_get_by_ofw_property(dev, node, "usb-phy", &phy) == 0)
		if (phy_enable(phy) != 0)
			device_printf(dev, "Cannot enable phy\n");
#endif

	return (generic_xhci_attach(dev));
}