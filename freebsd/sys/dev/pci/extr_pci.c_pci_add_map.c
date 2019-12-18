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
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int u_long ;
struct resource_list {int dummy; } ;
struct resource {int dummy; } ;
struct pci_map {int pm_value; } ;
typedef  int pci_addr_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int PCIM_BAR_IO_RESERVED ; 
 int PCIM_BAR_MEM_PREFETCH ; 
 int /*<<< orphan*/  PCIM_CMD_MEMEN ; 
 int /*<<< orphan*/  PCIM_CMD_PORTEN ; 
 int /*<<< orphan*/  PCIR_COMMAND ; 
 scalar_t__ PCI_BAR_IO (int) ; 
 scalar_t__ PCI_BAR_MEM (int) ; 
 int /*<<< orphan*/  PCI_QUIRK_REALLOC_BAR ; 
 int RF_ALIGNMENT_LOG2 (int) ; 
 int RF_PREFETCHABLE ; 
 int SYS_RES_IOPORT ; 
 int SYS_RES_MEMORY ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct pci_map* pci_add_bar (int /*<<< orphan*/ ,int,int,int) ; 
 scalar_t__ pci_clear_bars ; 
 int /*<<< orphan*/  pci_disable_io (int /*<<< orphan*/ ,int) ; 
 scalar_t__ pci_do_realloc_bars ; 
 scalar_t__ pci_enable_io_modes ; 
 struct pci_map* pci_find_bar (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_get_bus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_devid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_domain (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_function (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_slot (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_has_quirk (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pci_mapbase (int) ; 
 int pci_maprange (int) ; 
 int pci_mapsize (int) ; 
 char* pci_maptype (int) ; 
 int /*<<< orphan*/  pci_memen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_porten (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_bar (int /*<<< orphan*/ ,int,int*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_write_bar (int /*<<< orphan*/ ,struct pci_map*,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  resource_list_add (struct resource_list*,int,int,int,int,int) ; 
 int /*<<< orphan*/  resource_list_delete (struct resource_list*,int,int) ; 
 struct resource* resource_list_reserve (struct resource_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,int,int,int,int) ; 
 int rman_get_start (struct resource*) ; 

__attribute__((used)) static int
pci_add_map(device_t bus, device_t dev, int reg, struct resource_list *rl,
    int force, int prefetch)
{
	struct pci_map *pm;
	pci_addr_t base, map, testval;
	pci_addr_t start, end, count;
	int barlen, basezero, flags, maprange, mapsize, type;
	uint16_t cmd;
	struct resource *res;

	/*
	 * The BAR may already exist if the device is a CardBus card
	 * whose CIS is stored in this BAR.
	 */
	pm = pci_find_bar(dev, reg);
	if (pm != NULL) {
		maprange = pci_maprange(pm->pm_value);
		barlen = maprange == 64 ? 2 : 1;
		return (barlen);
	}

	pci_read_bar(dev, reg, &map, &testval, NULL);
	if (PCI_BAR_MEM(map)) {
		type = SYS_RES_MEMORY;
		if (map & PCIM_BAR_MEM_PREFETCH)
			prefetch = 1;
	} else
		type = SYS_RES_IOPORT;
	mapsize = pci_mapsize(testval);
	base = pci_mapbase(map);
#ifdef __PCI_BAR_ZERO_VALID
	basezero = 0;
#else
	basezero = base == 0;
#endif
	maprange = pci_maprange(map);
	barlen = maprange == 64 ? 2 : 1;

	/*
	 * For I/O registers, if bottom bit is set, and the next bit up
	 * isn't clear, we know we have a BAR that doesn't conform to the
	 * spec, so ignore it.  Also, sanity check the size of the data
	 * areas to the type of memory involved.  Memory must be at least
	 * 16 bytes in size, while I/O ranges must be at least 4.
	 */
	if (PCI_BAR_IO(testval) && (testval & PCIM_BAR_IO_RESERVED) != 0)
		return (barlen);
	if ((type == SYS_RES_MEMORY && mapsize < 4) ||
	    (type == SYS_RES_IOPORT && mapsize < 2))
		return (barlen);

	/* Save a record of this BAR. */
	pm = pci_add_bar(dev, reg, map, mapsize);
	if (bootverbose) {
		printf("\tmap[%02x]: type %s, range %2d, base %#jx, size %2d",
		    reg, pci_maptype(map), maprange, (uintmax_t)base, mapsize);
		if (type == SYS_RES_IOPORT && !pci_porten(dev))
			printf(", port disabled\n");
		else if (type == SYS_RES_MEMORY && !pci_memen(dev))
			printf(", memory disabled\n");
		else
			printf(", enabled\n");
	}

	/*
	 * If base is 0, then we have problems if this architecture does
	 * not allow that.  It is best to ignore such entries for the
	 * moment.  These will be allocated later if the driver specifically
	 * requests them.  However, some removable buses look better when
	 * all resources are allocated, so allow '0' to be overriden.
	 *
	 * Similarly treat maps whose values is the same as the test value
	 * read back.  These maps have had all f's written to them by the
	 * BIOS in an attempt to disable the resources.
	 */
	if (!force && (basezero || map == testval))
		return (barlen);
	if ((u_long)base != base) {
		device_printf(bus,
		    "pci%d:%d:%d:%d bar %#x too many address bits",
		    pci_get_domain(dev), pci_get_bus(dev), pci_get_slot(dev),
		    pci_get_function(dev), reg);
		return (barlen);
	}

	/*
	 * This code theoretically does the right thing, but has
	 * undesirable side effects in some cases where peripherals
	 * respond oddly to having these bits enabled.  Let the user
	 * be able to turn them off (since pci_enable_io_modes is 1 by
	 * default).
	 */
	if (pci_enable_io_modes) {
		/* Turn on resources that have been left off by a lazy BIOS */
		if (type == SYS_RES_IOPORT && !pci_porten(dev)) {
			cmd = pci_read_config(dev, PCIR_COMMAND, 2);
			cmd |= PCIM_CMD_PORTEN;
			pci_write_config(dev, PCIR_COMMAND, cmd, 2);
		}
		if (type == SYS_RES_MEMORY && !pci_memen(dev)) {
			cmd = pci_read_config(dev, PCIR_COMMAND, 2);
			cmd |= PCIM_CMD_MEMEN;
			pci_write_config(dev, PCIR_COMMAND, cmd, 2);
		}
	} else {
		if (type == SYS_RES_IOPORT && !pci_porten(dev))
			return (barlen);
		if (type == SYS_RES_MEMORY && !pci_memen(dev))
			return (barlen);
	}

	count = (pci_addr_t)1 << mapsize;
	flags = RF_ALIGNMENT_LOG2(mapsize);
	if (prefetch)
		flags |= RF_PREFETCHABLE;
	if (basezero || base == pci_mapbase(testval) || pci_clear_bars) {
		start = 0;	/* Let the parent decide. */
		end = ~0;
	} else {
		start = base;
		end = base + count - 1;
	}
	resource_list_add(rl, type, reg, start, end, count);

	/*
	 * Try to allocate the resource for this BAR from our parent
	 * so that this resource range is already reserved.  The
	 * driver for this device will later inherit this resource in
	 * pci_alloc_resource().
	 */
	res = resource_list_reserve(rl, bus, dev, type, &reg, start, end, count,
	    flags);
	if ((pci_do_realloc_bars
		|| pci_has_quirk(pci_get_devid(dev), PCI_QUIRK_REALLOC_BAR))
	    && res == NULL && (start != 0 || end != ~0)) {
		/*
		 * If the allocation fails, try to allocate a resource for
		 * this BAR using any available range.  The firmware felt
		 * it was important enough to assign a resource, so don't
		 * disable decoding if we can help it.
		 */
		resource_list_delete(rl, type, reg);
		resource_list_add(rl, type, reg, 0, ~0, count);
		res = resource_list_reserve(rl, bus, dev, type, &reg, 0, ~0,
		    count, flags);
	}
	if (res == NULL) {
		/*
		 * If the allocation fails, delete the resource list entry
		 * and disable decoding for this device.
		 *
		 * If the driver requests this resource in the future,
		 * pci_reserve_map() will try to allocate a fresh
		 * resource range.
		 */
		resource_list_delete(rl, type, reg);
		pci_disable_io(dev, type);
		if (bootverbose)
			device_printf(bus,
			    "pci%d:%d:%d:%d bar %#x failed to allocate\n",
			    pci_get_domain(dev), pci_get_bus(dev),
			    pci_get_slot(dev), pci_get_function(dev), reg);
	} else {
		start = rman_get_start(res);
		pci_write_bar(dev, pm, start);
	}
	return (barlen);
}