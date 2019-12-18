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
struct bhndb_pci_softc {int /*<<< orphan*/  dev; } ;
struct bhndb_devinfo {int /*<<< orphan*/  addrspace; } ;
typedef  int /*<<< orphan*/ * device_t ;
typedef  scalar_t__ bus_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  BHNDB_ADDRSPACE_NATIVE ; 
 scalar_t__ BHND_PROBE_ORDER_EARLY ; 
 scalar_t__ BHND_PROBE_ROOT ; 
 int /*<<< orphan*/ * BUS_ADD_CHILD (int /*<<< orphan*/ ,scalar_t__,char*,int) ; 
 int ENXIO ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bhndb_pci_sprom_addr (struct bhndb_pci_softc*) ; 
 scalar_t__ bhndb_pci_sprom_size (struct bhndb_pci_softc*) ; 
 scalar_t__ bootverbose ; 
 int bus_set_resource (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 struct bhndb_devinfo* device_get_ivars (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int
bhndb_pci_add_children(struct bhndb_pci_softc *sc)
{
	bus_size_t		 nv_sz;
	int			 error;

	/**
	 * If SPROM is mapped directly into BAR0, add child NVRAM
	 * device.
	 */
	nv_sz = bhndb_pci_sprom_size(sc);
	if (nv_sz > 0) {
		struct bhndb_devinfo	*dinfo;
		device_t		 child;

		if (bootverbose) {
			device_printf(sc->dev, "found SPROM (%ju bytes)\n",
			    (uintmax_t)nv_sz);
		}

		/* Add sprom device, ordered early enough to be available
		 * before the bridged bhnd(4) bus is attached. */
		child = BUS_ADD_CHILD(sc->dev,
		    BHND_PROBE_ROOT + BHND_PROBE_ORDER_EARLY, "bhnd_nvram", -1);
		if (child == NULL) {
			device_printf(sc->dev, "failed to add sprom device\n");
			return (ENXIO);
		}

		/* Initialize device address space and resource covering the
		 * BAR0 SPROM shadow. */
		dinfo = device_get_ivars(child);
		dinfo->addrspace = BHNDB_ADDRSPACE_NATIVE;

		error = bus_set_resource(child, SYS_RES_MEMORY, 0,
		    bhndb_pci_sprom_addr(sc), nv_sz);
		if (error) {
			device_printf(sc->dev,
			    "failed to register sprom resources\n");
			return (error);
		}
	}

	return (0);
}