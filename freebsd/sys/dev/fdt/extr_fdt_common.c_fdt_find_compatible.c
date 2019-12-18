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
 int /*<<< orphan*/  fdt_is_compatible_strict (scalar_t__,char const*) ; 
 scalar_t__ ofw_bus_node_is_compatible (scalar_t__,char const*) ; 

phandle_t
fdt_find_compatible(phandle_t start, const char *compat, int strict)
{
	phandle_t child;

	/*
	 * Traverse all children of 'start' node, and find first with
	 * matching 'compatible' property.
	 */
	for (child = OF_child(start); child != 0; child = OF_peer(child))
		if (ofw_bus_node_is_compatible(child, compat)) {
			if (strict)
				if (!fdt_is_compatible_strict(child, compat))
					continue;
			return (child);
		}
	return (0);
}