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

/* Variables and functions */
 scalar_t__ OF_child (scalar_t__) ; 
 scalar_t__ OF_peer (scalar_t__) ; 
 scalar_t__ ofw_bus_node_is_compatible (scalar_t__,char const*) ; 

phandle_t
ofw_bus_find_compatible(phandle_t node, const char *onecompat)
{
	phandle_t child, ret;

	/*
	 * Traverse all children of 'start' node, and find first with
	 * matching 'compatible' property.
	 */
	for (child = OF_child(node); child != 0; child = OF_peer(child)) {
		if (ofw_bus_node_is_compatible(child, onecompat) != 0)
			return (child);

		ret = ofw_bus_find_compatible(child, onecompat);
		if (ret != 0)
			return (ret);
	}
	return (0);
}