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
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  void* u_long ;
typedef  int phandle_t ;

/* Variables and functions */
 int ENXIO ; 
 int OF_finddevice (char*) ; 
 int fdt_find_compatible (int,char*,int /*<<< orphan*/ ) ; 
 int fdt_get_range (int,int /*<<< orphan*/ ,void**,void**) ; 
 void* fdt_immr_pa ; 
 void* fdt_immr_size ; 
 int /*<<< orphan*/  fdt_immr_va ; 
 scalar_t__ ofw_bus_node_is_compatible (int,char*) ; 

int
fdt_immr_addr(vm_offset_t immr_va)
{
	phandle_t node;
	u_long base, size;
	int r;

	/*
	 * Try to access the SOC node directly i.e. through /aliases/.
	 */
	if ((node = OF_finddevice("soc")) != -1)
		if (ofw_bus_node_is_compatible(node, "simple-bus"))
			goto moveon;
	/*
	 * Find the node the long way.
	 */
	if ((node = OF_finddevice("/")) == -1)
		return (ENXIO);

	if ((node = fdt_find_compatible(node, "simple-bus", 0)) == 0)
		return (ENXIO);

moveon:
	if ((r = fdt_get_range(node, 0, &base, &size)) == 0) {
		fdt_immr_pa = base;
		fdt_immr_va = immr_va;
		fdt_immr_size = size;
	}

	return (r);
}