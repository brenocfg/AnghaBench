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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  reg ;
typedef  int /*<<< orphan*/  phandle_t ;

/* Variables and functions */
 int ENOENT ; 
 int OF_getencprop (int /*<<< orphan*/ ,char*,int*,int) ; 
 scalar_t__ bootverbose ; 
 int nvmem_get_cell_node (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int ofw_bus_find_string_index (int /*<<< orphan*/ ,char*,char const*,int*) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 

int
nvmem_get_cell_len(phandle_t node, const char *name)
{
	phandle_t cell_node;
	uint32_t reg[2];
	int rv, idx;

	rv = ofw_bus_find_string_index(node, "nvmem-cell-names", name, &idx);
	if (rv != 0)
		return (rv);

	rv = nvmem_get_cell_node(node, idx, &cell_node);
	if (rv != 0)
		return (rv);

	if (OF_getencprop(cell_node, "reg", reg, sizeof(reg)) != sizeof(reg)) {
		if (bootverbose)
			printf("nvmem_get_cell_len: Cannot parse reg property of cell %s\n",
			    name);
		return (ENOENT);
	}

	return (reg[1]);
}