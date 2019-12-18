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
typedef  void* u_long ;
struct devmap_entry {void* pd_size; void* pd_pa; int /*<<< orphan*/  pd_va; } ;
typedef  int /*<<< orphan*/  phandle_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int ENXIO ; 
 int /*<<< orphan*/  MV_CESA_SRAM_BASE ; 
 int /*<<< orphan*/  OF_finddevice (char*) ; 
 int /*<<< orphan*/  fdt_find_compatible (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ fdt_regsize (int /*<<< orphan*/ ,void**,void**) ; 
 scalar_t__ ofw_bus_node_is_compatible (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
platform_sram_devmap(struct devmap_entry *map)
{
	phandle_t child, root;
	u_long base, size;
	/*
	 * SRAM range.
	 */
	if ((root = OF_finddevice("/")) == 0)
		return (ENXIO);

	if ((child = OF_finddevice("/sram")) != 0)
		if (ofw_bus_node_is_compatible(child, "mrvl,cesa-sram") ||
		    ofw_bus_node_is_compatible(child, "mrvl,scratchpad"))
			goto moveon;

	if ((child = fdt_find_compatible(root, "mrvl,cesa-sram", 0)) == 0 &&
	    (child = fdt_find_compatible(root, "mrvl,scratchpad", 0)) == 0)
			goto out;

moveon:
	if (fdt_regsize(child, &base, &size) != 0)
		return (EINVAL);

	map->pd_va = MV_CESA_SRAM_BASE; /* XXX */
	map->pd_pa = base;
	map->pd_size = size;

	return (0);
out:
	return (ENOENT);

}