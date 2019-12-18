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
typedef  int uint16_t ;
typedef  int u_int ;
struct resource_list {int dummy; } ;
struct resource {int dummy; } ;
struct pci_map {int pm_size; int pm_value; } ;
struct pci_devinfo {int /*<<< orphan*/  cfg; struct resource_list resources; } ;
typedef  int rman_res_t ;
typedef  int pci_addr_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int PCIM_BAR_MEM_PREFETCH ; 
 int PCIM_CMD_MEMEN ; 
 int PCIM_CMD_PORTEN ; 
 int /*<<< orphan*/  PCIR_COMMAND ; 
 scalar_t__ PCIR_IS_BIOS (int /*<<< orphan*/ *,int) ; 
 scalar_t__ PCI_BAR_MEM (int) ; 
 int RF_ACTIVE ; 
 int RF_ALIGNMENT (int) ; 
 int RF_ALIGNMENT_LOG2 (int) ; 
 int RF_ALIGNMENT_MASK ; 
 int RF_PREFETCHABLE ; 
 int SYS_RES_IOPORT ; 
 int SYS_RES_MEMORY ; 
 scalar_t__ bootverbose ; 
 struct pci_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,int,int,...) ; 
 struct pci_map* pci_add_bar (int /*<<< orphan*/ ,int,int,int) ; 
 scalar_t__ pci_ea_is_enabled (int /*<<< orphan*/ ,int) ; 
 struct pci_map* pci_find_bar (int /*<<< orphan*/ ,int) ; 
 int pci_mapsize (int) ; 
 int /*<<< orphan*/  pci_read_bar (int /*<<< orphan*/ ,int,int*,int*,int /*<<< orphan*/ *) ; 
 int pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int pci_romsize (int) ; 
 int /*<<< orphan*/  pci_write_bar (int /*<<< orphan*/ ,struct pci_map*,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  resource_list_add (struct resource_list*,int,int,int,int,int) ; 
 int /*<<< orphan*/  resource_list_delete (struct resource_list*,int,int) ; 
 struct resource* resource_list_reserve (struct resource_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,int,int,int,int) ; 
 int rman_get_start (struct resource*) ; 

__attribute__((used)) static struct resource *
pci_reserve_map(device_t dev, device_t child, int type, int *rid,
    rman_res_t start, rman_res_t end, rman_res_t count, u_int num,
    u_int flags)
{
	struct pci_devinfo *dinfo = device_get_ivars(child);
	struct resource_list *rl = &dinfo->resources;
	struct resource *res;
	struct pci_map *pm;
	uint16_t cmd;
	pci_addr_t map, testval;
	int mapsize;

	res = NULL;

	/* If rid is managed by EA, ignore it */
	if (pci_ea_is_enabled(child, *rid))
		goto out;

	pm = pci_find_bar(child, *rid);
	if (pm != NULL) {
		/* This is a BAR that we failed to allocate earlier. */
		mapsize = pm->pm_size;
		map = pm->pm_value;
	} else {
		/*
		 * Weed out the bogons, and figure out how large the
		 * BAR/map is.  BARs that read back 0 here are bogus
		 * and unimplemented.  Note: atapci in legacy mode are
		 * special and handled elsewhere in the code.  If you
		 * have a atapci device in legacy mode and it fails
		 * here, that other code is broken.
		 */
		pci_read_bar(child, *rid, &map, &testval, NULL);

		/*
		 * Determine the size of the BAR and ignore BARs with a size
		 * of 0.  Device ROM BARs use a different mask value.
		 */
		if (PCIR_IS_BIOS(&dinfo->cfg, *rid))
			mapsize = pci_romsize(testval);
		else
			mapsize = pci_mapsize(testval);
		if (mapsize == 0)
			goto out;
		pm = pci_add_bar(child, *rid, map, mapsize);
	}

	if (PCI_BAR_MEM(map) || PCIR_IS_BIOS(&dinfo->cfg, *rid)) {
		if (type != SYS_RES_MEMORY) {
			if (bootverbose)
				device_printf(dev,
				    "child %s requested type %d for rid %#x,"
				    " but the BAR says it is an memio\n",
				    device_get_nameunit(child), type, *rid);
			goto out;
		}
	} else {
		if (type != SYS_RES_IOPORT) {
			if (bootverbose)
				device_printf(dev,
				    "child %s requested type %d for rid %#x,"
				    " but the BAR says it is an ioport\n",
				    device_get_nameunit(child), type, *rid);
			goto out;
		}
	}

	/*
	 * For real BARs, we need to override the size that
	 * the driver requests, because that's what the BAR
	 * actually uses and we would otherwise have a
	 * situation where we might allocate the excess to
	 * another driver, which won't work.
	 */
	count = ((pci_addr_t)1 << mapsize) * num;
	if (RF_ALIGNMENT(flags) < mapsize)
		flags = (flags & ~RF_ALIGNMENT_MASK) | RF_ALIGNMENT_LOG2(mapsize);
	if (PCI_BAR_MEM(map) && (map & PCIM_BAR_MEM_PREFETCH))
		flags |= RF_PREFETCHABLE;

	/*
	 * Allocate enough resource, and then write back the
	 * appropriate BAR for that resource.
	 */
	resource_list_add(rl, type, *rid, start, end, count);
	res = resource_list_reserve(rl, dev, child, type, rid, start, end,
	    count, flags & ~RF_ACTIVE);
	if (res == NULL) {
		resource_list_delete(rl, type, *rid);
		device_printf(child,
		    "%#jx bytes of rid %#x res %d failed (%#jx, %#jx).\n",
		    count, *rid, type, start, end);
		goto out;
	}
	if (bootverbose)
		device_printf(child,
		    "Lazy allocation of %#jx bytes rid %#x type %d at %#jx\n",
		    count, *rid, type, rman_get_start(res));

	/* Disable decoding via the CMD register before updating the BAR */
	cmd = pci_read_config(child, PCIR_COMMAND, 2);
	pci_write_config(child, PCIR_COMMAND,
	    cmd & ~(PCI_BAR_MEM(map) ? PCIM_CMD_MEMEN : PCIM_CMD_PORTEN), 2);

	map = rman_get_start(res);
	pci_write_bar(child, pm, map);

	/* Restore the original value of the CMD register */
	pci_write_config(child, PCIR_COMMAND, cmd, 2);
out:
	return (res);
}