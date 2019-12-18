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
typedef  int /*<<< orphan*/  u_long ;
struct mem_region {int /*<<< orphan*/  mr_size; int /*<<< orphan*/  mr_start; } ;
typedef  int /*<<< orphan*/  reserve ;
typedef  int phandle_t ;
typedef  int /*<<< orphan*/  pcell_t ;

/* Variables and functions */
 int ENXIO ; 
 int ERANGE ; 
 int FDT_MEM_REGIONS ; 
 int FDT_REG_CELLS ; 
 int OF_finddevice (char*) ; 
 scalar_t__ OF_getprop (int,char*,int /*<<< orphan*/ *,int) ; 
 int OF_getproplen (int,char*) ; 
 int /*<<< orphan*/  OF_parent (int) ; 
 int fdt_addrsize_cells (int /*<<< orphan*/ ,int*,int*) ; 
 int fdt_data_to_res (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
fdt_get_reserved_regions(struct mem_region *mr, int *mrcnt)
{
	pcell_t reserve[FDT_REG_CELLS * FDT_MEM_REGIONS];
	pcell_t *reservep;
	phandle_t memory, root;
	int addr_cells, size_cells;
	int i, res_len, rv, tuple_size, tuples;

	root = OF_finddevice("/");
	memory = OF_finddevice("/memory");
	if (memory == -1) {
		rv = ENXIO;
		goto out;
	}

	if ((rv = fdt_addrsize_cells(OF_parent(memory), &addr_cells,
	    &size_cells)) != 0)
		goto out;

	if (addr_cells > 2) {
		rv = ERANGE;
		goto out;
	}

	tuple_size = sizeof(pcell_t) * (addr_cells + size_cells);

	res_len = OF_getproplen(root, "memreserve");
	if (res_len <= 0 || res_len > sizeof(reserve)) {
		rv = ERANGE;
		goto out;
	}

	if (OF_getprop(root, "memreserve", reserve, res_len) <= 0) {
		rv = ENXIO;
		goto out;
	}

	tuples = res_len / tuple_size;
	reservep = (pcell_t *)&reserve;
	for (i = 0; i < tuples; i++) {

		rv = fdt_data_to_res(reservep, addr_cells, size_cells,
			(u_long *)&mr[i].mr_start, (u_long *)&mr[i].mr_size);

		if (rv != 0)
			goto out;

		reservep += addr_cells + size_cells;
	}

	*mrcnt = i;
	rv = 0;
out:
	return (rv);
}