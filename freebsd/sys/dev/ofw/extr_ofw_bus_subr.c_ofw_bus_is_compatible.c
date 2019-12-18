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
 int OF_getproplen (int,char*) ; 
 char* ofw_bus_get_compat (int /*<<< orphan*/ ) ; 
 int ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int ofw_bus_node_is_compatible_int (char const*,int,char const*) ; 

int
ofw_bus_is_compatible(device_t dev, const char *onecompat)
{
	phandle_t node;
	const char *compat;
	int len;

	if ((compat = ofw_bus_get_compat(dev)) == NULL)
		return (0);

	if ((node = ofw_bus_get_node(dev)) == -1)
		return (0);

	/* Get total 'compatible' prop len */
	if ((len = OF_getproplen(node, "compatible")) <= 0)
		return (0);

	return (ofw_bus_node_is_compatible_int(compat, len, onecompat));
}