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
 int nvmem_write_cell_by_idx (int /*<<< orphan*/ ,int,void*,size_t) ; 
 int ofw_bus_find_string_index (int /*<<< orphan*/ ,char*,char const*,int*) ; 

int
nvmem_write_cell_by_name(phandle_t node, const char *name, void *cell, size_t buflen)
{
	int rv, idx;

	rv = ofw_bus_find_string_index(node, "nvmem-cell-names", name, &idx);
	if (rv != 0)
		return (rv);

	return (nvmem_write_cell_by_idx(node, idx, cell, buflen));
}