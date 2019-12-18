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
typedef  int phandle_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int OF_hasprop (int,char const*) ; 
 int ofw_bus_get_node (int /*<<< orphan*/ ) ; 

int
ofw_bus_has_prop(device_t dev, const char *propname)
{
	phandle_t node;

	if ((node = ofw_bus_get_node(dev)) == -1)
		return (0);

	return (OF_hasprop(node, propname));
}