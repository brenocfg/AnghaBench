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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  portnode ;
typedef  scalar_t__ phandle_t ;

/* Variables and functions */
 scalar_t__ OF_child (scalar_t__) ; 
 scalar_t__ OF_getencprop (scalar_t__,char*,int*,int) ; 
 scalar_t__ OF_peer (scalar_t__) ; 
 int PORT_MAX_NAME ; 
 scalar_t__ ofw_bus_find_child (scalar_t__,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

phandle_t
ofw_graph_get_port_by_idx(phandle_t node, uint32_t idx)
{
	phandle_t ports, child;
	uint32_t reg;
	char portnode[PORT_MAX_NAME];

	/* First try to find a port@<idx> node */
	snprintf(portnode, sizeof(portnode), "port@%d", idx);
	child = ofw_bus_find_child(node, portnode);
	if (child != 0)
		return (child);

	/* Next try to look under ports */
	ports = ofw_bus_find_child(node, "ports");
	if (ports == 0)
		return (0);

	for (child = OF_child(ports); child != 0; child = OF_peer(child)) {
		if (OF_getencprop(child, "reg", &reg, sizeof(uint32_t)) <= 0 ||
		    reg != idx)
			continue;

		return (child);
	}

	return (0);
}