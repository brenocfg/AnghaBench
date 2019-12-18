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

/* Variables and functions */
 int OFW_COMPAT_LEN ; 
 scalar_t__ OF_getprop (int /*<<< orphan*/ ,char*,char*,int) ; 
 int OF_getproplen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 int ofw_bus_node_is_compatible_int (char*,int,char const*) ; 

int
ofw_bus_node_is_compatible(phandle_t node, const char *compatstr)
{
	char compat[OFW_COMPAT_LEN];
	int len, rv;

	if ((len = OF_getproplen(node, "compatible")) <= 0)
		return (0);

	bzero(compat, OFW_COMPAT_LEN);

	if (OF_getprop(node, "compatible", compat, OFW_COMPAT_LEN) < 0)
		return (0);

	rv = ofw_bus_node_is_compatible_int(compat, len, compatstr);

	return (rv);
}