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
struct mv_pci_range {int base_parent; int len; int base_pci; } ;
typedef  int /*<<< orphan*/  ranges ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int pcell_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int ERANGE ; 
 int FDT_RANGES_CELLS ; 
 scalar_t__ OF_getprop (int /*<<< orphan*/ ,char*,int*,int) ; 
 int OF_getproplen (int /*<<< orphan*/ ,char*) ; 
 int PCI_SPACE_LEN ; 
 int /*<<< orphan*/  bzero (struct mv_pci_range*,int) ; 
 scalar_t__ fdt_addrsize_cells (int /*<<< orphan*/ ,int*,int*) ; 
 void* fdt_data_get (void*,int) ; 
 int fdt_immr_va ; 
 int fdt_parent_addr_cells (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mv_pci_ranges_decode(phandle_t node, struct mv_pci_range *io_space,
    struct mv_pci_range *mem_space)
{
	pcell_t ranges[FDT_RANGES_CELLS];
	struct mv_pci_range *pci_space;
	pcell_t addr_cells, size_cells, par_addr_cells;
	pcell_t *rangesptr;
	pcell_t cell0, cell1, cell2;
	int tuple_size, tuples, i, rv, offset_cells, len;
	int  portid, is_io_space;

	/*
	 * Retrieve 'ranges' property.
	 */
	if ((fdt_addrsize_cells(node, &addr_cells, &size_cells)) != 0)
		return (EINVAL);
	if (addr_cells != 3 || size_cells != 2)
		return (ERANGE);

	par_addr_cells = fdt_parent_addr_cells(node);
	if (par_addr_cells > 3)
		return (ERANGE);

	len = OF_getproplen(node, "ranges");
	if (len > sizeof(ranges))
		return (ENOMEM);

	if (OF_getprop(node, "ranges", ranges, sizeof(ranges)) <= 0)
		return (EINVAL);

	tuple_size = sizeof(pcell_t) * (addr_cells + par_addr_cells +
	    size_cells);
	tuples = len / tuple_size;

	/*
	 * Initialize the ranges so that we don't have to worry about
	 * having them all defined in the FDT. In particular, it is
	 * perfectly fine not to want I/O space on PCI buses.
	 */
	bzero(io_space, sizeof(*io_space));
	bzero(mem_space, sizeof(*mem_space));

	rangesptr = &ranges[0];
	offset_cells = 0;
	for (i = 0; i < tuples; i++) {
		cell0 = fdt_data_get((void *)rangesptr, 1);
		rangesptr++;
		cell1 = fdt_data_get((void *)rangesptr, 1);
		rangesptr++;
		cell2 = fdt_data_get((void *)rangesptr, 1);
		rangesptr++;
		portid = fdt_data_get((void *)(rangesptr+1), 1);

		if (cell0 & 0x02000000) {
			pci_space = mem_space;
			is_io_space = 0;
		} else if (cell0 & 0x01000000) {
			pci_space = io_space;
			is_io_space = 1;
		} else {
			rv = ERANGE;
			goto out;
		}

		if (par_addr_cells == 3) {
			/*
			 * This is a PCI subnode 'ranges'. Skip cell0 and
			 * cell1 of this entry and only use cell2.
			 */
			offset_cells = 2;
			rangesptr += offset_cells;
		}

		if ((par_addr_cells - offset_cells) > 2) {
			rv = ERANGE;
			goto out;
		}
		pci_space->base_parent = fdt_data_get((void *)rangesptr,
		    par_addr_cells - offset_cells);
		rangesptr += par_addr_cells - offset_cells;

		if (size_cells > 2) {
			rv = ERANGE;
			goto out;
		}
		pci_space->len = fdt_data_get((void *)rangesptr, size_cells);
		rangesptr += size_cells;

		pci_space->base_pci = cell2;

		if (pci_space->len == 0) {
			pci_space->len = PCI_SPACE_LEN;
			pci_space->base_parent = fdt_immr_va +
			    PCI_SPACE_LEN * ( 2 * portid + is_io_space);
		}
	}
	rv = 0;
out:
	return (rv);
}