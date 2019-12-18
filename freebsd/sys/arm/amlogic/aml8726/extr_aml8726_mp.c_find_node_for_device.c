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

/* Variables and functions */
 int OF_finddevice (char const*) ; 
 int fdt_find_compatible (int,char const*,int) ; 
 scalar_t__ fdt_is_compatible_strict (int,char const*) ; 

__attribute__((used)) static phandle_t
find_node_for_device(const char *device, const char **compatible)
{
	int i;
	phandle_t node;

	/*
	 * Try to access the node directly i.e. through /aliases/.
	 */

	if ((node = OF_finddevice(device)) != -1)
		for (i = 0; compatible[i]; i++)
			if (fdt_is_compatible_strict(node, compatible[i]))
				return node;

	/*
	 * Find the node the long way.
	 */

	for (i = 0; compatible[i]; i++) {
		if ((node = OF_finddevice("/soc")) == -1)
			return (0);

		if ((node = fdt_find_compatible(node, compatible[i], 1)) != 0)
			return node;
	}

	return (0);
}