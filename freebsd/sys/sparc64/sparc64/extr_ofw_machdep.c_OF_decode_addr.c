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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  szc ;
typedef  scalar_t__ phandle_t ;
typedef  int pcell_t ;
typedef  int /*<<< orphan*/  paddrc ;
typedef  int /*<<< orphan*/  name ;
typedef  int bus_addr_t ;
typedef  int /*<<< orphan*/  banks ;
typedef  int /*<<< orphan*/  addrc ;

/* Variables and functions */
 int ENXIO ; 
 int MIN (int,int) ; 
 int NEXUS_BUS_SPACE ; 
#define  OFW_PCI_PHYS_HI_SPACE_IO 129 
#define  OFW_PCI_PHYS_HI_SPACE_MEM32 128 
 int OF_getprop (scalar_t__,char*,...) ; 
 scalar_t__ OF_parent (scalar_t__) ; 
 int PCI_IO_BUS_SPACE ; 
 int PCI_MEMORY_BUS_SPACE ; 
 int SBUS_BUS_SPACE ; 
 int phys_hi_mask_space (char*,int) ; 
 scalar_t__ strcmp (char*,char*) ; 

int
OF_decode_addr(phandle_t node, int bank, int *space, bus_addr_t *addr)
{
	char name[32];
	uint64_t cend, cstart, end, phys, pphys, sz, start;
	pcell_t addrc, szc, paddrc;
	phandle_t bus, lbus, pbus;
	uint32_t banks[10 * 5];	/* 10 PCI banks */
	uint32_t cspc, pspc, spc;
	int i, j, nbank;

	/*
	 * In general the addresses are contained in the "reg" property
	 * of a node.  The first address in the "reg" property of a PCI
	 * node however is the address of its configuration registers in
	 * the configuration space of the host bridge.  Additional entries
	 * denote the memory and I/O addresses.  For relocatable addresses
	 * the "reg" property contains the BAR, for non-relocatable
	 * addresses it contains the absolute PCI address.  The PCI-only
	 * "assigned-addresses" property however always contains the
	 * absolute PCI addresses.
	 * The "assigned-addresses" and "reg" properties are arrays of
	 * address structures consisting of #address-cells 32-bit phys
	 * cells and #size-cells 32-bit size cells.  If a parent lacks
	 * the "#address-cells" or "#size-cells" property the default
	 * for #address-cells to use is 2 and for #size-cells 1.
	 */
	bus = OF_parent(node);
	if (bus == 0)
		return (ENXIO);
	if (OF_getprop(bus, "name", name, sizeof(name)) == -1)
		return (ENXIO);
	name[sizeof(name) - 1] = '\0';
	if (OF_getprop(bus, "#address-cells", &addrc, sizeof(addrc)) == -1)
		addrc = 2;
	if (OF_getprop(bus, "#size-cells", &szc, sizeof(szc)) == -1)
		szc = 1;
	if (addrc < 2 || addrc > 3 || szc < 1 || szc > 2)
		return (ENXIO);
	if (strcmp(name, "pci") == 0) {
		if (addrc > 3)
			return (ENXIO);
		nbank = OF_getprop(node, "assigned-addresses", &banks,
		    sizeof(banks));
	} else {
		if (addrc > 2)
			return (ENXIO);
		nbank = OF_getprop(node, "reg", &banks, sizeof(banks));
	}
	if (nbank == -1)
		return (ENXIO);
	nbank /= sizeof(banks[0]) * (addrc + szc);
	if (bank < 0 || bank > nbank - 1)
		return (ENXIO);
	bank *= addrc + szc;
	spc = phys_hi_mask_space(name, banks[bank]);
	/* Skip the high cell for 3-cell addresses. */
	bank += addrc - 2;
	phys = 0;
	for (i = 0; i < MIN(2, addrc); i++)
		phys = ((uint64_t)phys << 32) | banks[bank++];
	sz = 0;
	for (i = 0; i < szc; i++)
		sz = ((uint64_t)sz << 32) | banks[bank++];
	start = phys;
	end = phys + sz - 1;

	/*
	 * Map upward in the device tree at every bridge we encounter
	 * using their "ranges" properties.
	 * The "ranges" property of a bridge is an array of a structure
	 * consisting of that bridge's #address-cells 32-bit child-phys
	 * cells, its parent bridge #address-cells 32-bit parent-phys
	 * cells and that bridge's #size-cells 32-bit size cells.
	 * If a bridge doesn't have a "ranges" property no mapping is
	 * necessary at that bridge.
	 */
	cspc = 0;
	lbus = bus;
	while ((pbus = OF_parent(bus)) != 0) {
		if (OF_getprop(pbus, "#address-cells", &paddrc,
		    sizeof(paddrc)) == -1)
			paddrc = 2;
		if (paddrc < 2 || paddrc > 3)
			return (ENXIO);
		nbank = OF_getprop(bus, "ranges", &banks, sizeof(banks));
		if (nbank == -1) {
			if (OF_getprop(pbus, "name", name, sizeof(name)) == -1)
				return (ENXIO);
			name[sizeof(name) - 1] = '\0';
			goto skip;
		}
		if (OF_getprop(bus, "#size-cells", &szc, sizeof(szc)) == -1)
			szc = 1;
		if (szc < 1 || szc > 2)
			return (ENXIO);
		nbank /= sizeof(banks[0]) * (addrc + paddrc + szc);
		bank = 0;
		for (i = 0; i < nbank; i++) {
			cspc = phys_hi_mask_space(name, banks[bank]);
			if (cspc != spc) {
				bank += addrc + paddrc + szc;
				continue;
			}
			/* Skip the high cell for 3-cell addresses. */
			bank += addrc - 2;
			phys = 0;
			for (j = 0; j < MIN(2, addrc); j++)
				phys = ((uint64_t)phys << 32) | banks[bank++];
			pspc = banks[bank];
			/* Skip the high cell for 3-cell addresses. */
			bank += paddrc - 2;
			pphys = 0;
			for (j = 0; j < MIN(2, paddrc); j++)
				pphys =
				    ((uint64_t)pphys << 32) | banks[bank++];
			sz = 0;
			for (j = 0; j < szc; j++)
				sz = ((uint64_t)sz << 32) | banks[bank++];
			cstart = phys;
			cend = phys + sz - 1;
			if (start < cstart || start > cend)
				continue;
			if (end < cstart || end > cend)
				return (ENXIO);
			if (OF_getprop(pbus, "name", name, sizeof(name)) == -1)
				return (ENXIO);
			name[sizeof(name) - 1] = '\0';
			spc = phys_hi_mask_space(name, pspc);
			start += pphys - cstart;
			end += pphys - cstart;
			break;
		}
		if (i == nbank)
			return (ENXIO);
		lbus = bus;
 skip:
		addrc = paddrc;
		bus = pbus;
	}

	*addr = start;
	/* Determine the bus space based on the last bus we mapped. */
	if (OF_parent(lbus) == 0) {
		*space = NEXUS_BUS_SPACE;
		return (0);
	}
	if (OF_getprop(lbus, "name", name, sizeof(name)) == -1)
		return (ENXIO);
	name[sizeof(name) - 1] = '\0';
	if (strcmp(name, "central") == 0 || strcmp(name, "ebus") == 0 ||
	    strcmp(name, "upa") == 0) {
		*space = NEXUS_BUS_SPACE;
		return (0);
	} else if (strcmp(name, "pci") == 0) {
		switch (cspc) {
		case OFW_PCI_PHYS_HI_SPACE_IO:
			*space = PCI_IO_BUS_SPACE;
			return (0);
		case OFW_PCI_PHYS_HI_SPACE_MEM32:
			*space = PCI_MEMORY_BUS_SPACE;
			return (0);
		}
	} else if (strcmp(name, "sbus") == 0) {
		*space = SBUS_BUS_SPACE;
		return (0);
	}
	return (ENXIO);
}