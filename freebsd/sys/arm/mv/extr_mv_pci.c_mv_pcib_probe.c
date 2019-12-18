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
 int BUS_PROBE_DEFAULT ; 
 int ENXIO ; 
 int /*<<< orphan*/  OF_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mv_fdt_is_type (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 scalar_t__ ofw_bus_is_compatible (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ofw_bus_node_is_compatible (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ofw_bus_status_okay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mv_pcib_probe(device_t self)
{
	phandle_t node;

	node = ofw_bus_get_node(self);
	if (!mv_fdt_is_type(node, "pci"))
		return (ENXIO);

	if (!(ofw_bus_is_compatible(self, "mrvl,pcie") ||
	    ofw_bus_is_compatible(self, "mrvl,pci") ||
	    ofw_bus_node_is_compatible(
	    OF_parent(node), "marvell,armada-370-pcie")))
		return (ENXIO);

	if (!ofw_bus_status_okay(self))
		return (ENXIO);

	device_set_desc(self, "Marvell Integrated PCI/PCI-E Controller");
	return (BUS_PROBE_DEFAULT);
}