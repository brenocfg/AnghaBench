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
typedef  int /*<<< orphan*/  pcell_t ;
typedef  int /*<<< orphan*/  addr_cells ;

/* Variables and functions */
 int /*<<< orphan*/  OF_parent (int /*<<< orphan*/ ) ; 
 scalar_t__ OF_searchprop (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ fdt32_to_cpu (int /*<<< orphan*/ ) ; 

int
fdt_parent_addr_cells(phandle_t node)
{
	pcell_t addr_cells;

	/* Find out #address-cells of the superior bus. */
	if (OF_searchprop(OF_parent(node), "#address-cells", &addr_cells,
	    sizeof(addr_cells)) <= 0)
		return (2);

	return ((int)fdt32_to_cpu(addr_cells));
}