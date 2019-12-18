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
typedef  int uint64_t ;
struct mem_region {int mr_start; int mr_size; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  size_cells ;
typedef  int phandle_t ;
typedef  int cell_t ;
typedef  int /*<<< orphan*/  address_cells ;
typedef  int /*<<< orphan*/  OFmem ;

/* Variables and functions */
 int BUS_SPACE_MAXADDR ; 
 int OF_finddevice (char*) ; 
 int OF_getencprop (int,char const*,int*,int) ; 
 int PHYS_AVAIL_SZ ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static int
parse_ofw_memory(phandle_t node, const char *prop, struct mem_region *output)
{
	cell_t address_cells, size_cells;
	cell_t OFmem[4 * PHYS_AVAIL_SZ];
	int sz, i, j;
	phandle_t phandle;

	sz = 0;

	/*
	 * Get #address-cells from root node, defaulting to 1 if it cannot
	 * be found.
	 */
	phandle = OF_finddevice("/");
	if (OF_getencprop(phandle, "#address-cells", &address_cells, 
	    sizeof(address_cells)) < (ssize_t)sizeof(address_cells))
		address_cells = 1;
	if (OF_getencprop(phandle, "#size-cells", &size_cells, 
	    sizeof(size_cells)) < (ssize_t)sizeof(size_cells))
		size_cells = 1;

	/*
	 * Get memory.
	 */
	if (node == -1 || (sz = OF_getencprop(node, prop,
	    OFmem, sizeof(OFmem))) <= 0)
		panic("Physical memory map not found");

	i = 0;
	j = 0;
	while (i < sz/sizeof(cell_t)) {
		output[j].mr_start = OFmem[i++];
		if (address_cells == 2) {
			output[j].mr_start <<= 32;
			output[j].mr_start += OFmem[i++];
		}
			
		output[j].mr_size = OFmem[i++];
		if (size_cells == 2) {
			output[j].mr_size <<= 32;
			output[j].mr_size += OFmem[i++];
		}

		if (output[j].mr_start > BUS_SPACE_MAXADDR)
			continue;

		/*
		 * Constrain memory to that which we can access.
		 * 32-bit AIM can only reference 32 bits of address currently,
		 * but Book-E can access 36 bits.
		 */
		if (((uint64_t)output[j].mr_start +
		    (uint64_t)output[j].mr_size - 1) >
		    BUS_SPACE_MAXADDR) {
			output[j].mr_size = BUS_SPACE_MAXADDR -
			    output[j].mr_start + 1;
		}

		j++;
	}

	return (j);
}