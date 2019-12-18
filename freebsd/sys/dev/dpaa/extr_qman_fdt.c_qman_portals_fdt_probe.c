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
 int BUS_PROBE_DEFAULT ; 
 int ENXIO ; 
 scalar_t__ OF_child (scalar_t__) ; 
 scalar_t__ OF_peer (scalar_t__) ; 
 int /*<<< orphan*/  QMAN_PORT_DEVSTR ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 scalar_t__ ofw_bus_is_compatible (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ofw_bus_node_is_compatible (scalar_t__,char*) ; 

__attribute__((used)) static int
qman_portals_fdt_probe(device_t dev)
{
	phandle_t node;

	if (ofw_bus_is_compatible(dev, "simple-bus")) {
		node = ofw_bus_get_node(dev);
		for (node = OF_child(node); node > 0; node = OF_peer(node)) {
			if (ofw_bus_node_is_compatible(node, "fsl,qman-portal"))
				break;
		}
		if (node <= 0)
			return (ENXIO);
	} else if (!ofw_bus_is_compatible(dev, "fsl,qman-portals"))
		return (ENXIO);

	device_set_desc(dev, QMAN_PORT_DEVSTR);

	return (BUS_PROBE_DEFAULT);
}