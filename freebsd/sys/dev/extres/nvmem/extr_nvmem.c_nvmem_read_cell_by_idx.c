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
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  reg ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int ENXIO ; 
 int NVMEM_READ (int /*<<< orphan*/ *,size_t,size_t,void*) ; 
 int /*<<< orphan*/ * OF_device_from_xref (int /*<<< orphan*/ ) ; 
 int OF_getencprop (int /*<<< orphan*/ ,char*,size_t*,int) ; 
 int /*<<< orphan*/  OF_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OF_xref_from_node (int /*<<< orphan*/ ) ; 
 scalar_t__ bootverbose ; 
 int nvmem_get_cell_node (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

int
nvmem_read_cell_by_idx(phandle_t node, int idx, void *cell, size_t buflen)
{
	phandle_t cell_node;
	device_t provider;
	uint32_t reg[2];
	int rv;

	rv = nvmem_get_cell_node(node, idx, &cell_node);
	if (rv != 0)
		return (rv);

	/* Validate the reg property */
	if (OF_getencprop(cell_node, "reg", reg, sizeof(reg)) != sizeof(reg)) {
		if (bootverbose)
			printf("nvmem_get_cell_by_name: Cannot parse reg property of cell %d\n",
			    idx);
		return (ENOENT);
	}

	if (buflen != reg[1])
		return (EINVAL);

	provider = OF_device_from_xref(OF_xref_from_node(OF_parent(cell_node)));
	if (provider == NULL) {
		if (bootverbose)
			printf("nvmem_get_cell_by_idx: Cannot find the nvmem device\n");
		return (ENXIO);
	}

	rv = NVMEM_READ(provider, reg[0], reg[1], cell);
	if (rv != 0) {
		return (rv);
	}

	return (0);
}