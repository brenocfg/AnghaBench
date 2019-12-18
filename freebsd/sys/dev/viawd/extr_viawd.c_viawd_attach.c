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
typedef  scalar_t__ uint32_t ;
struct viawd_softc {int /*<<< orphan*/ * wd_res; int /*<<< orphan*/  wd_rid; int /*<<< orphan*/  ev_tag; int /*<<< orphan*/ * sb_dev; int /*<<< orphan*/ * dev; } ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  EVENTHANDLER_REGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct viawd_softc*,int /*<<< orphan*/ ) ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  VIAWD_CONFIG_BASE ; 
 int /*<<< orphan*/  VIAWD_MEM_CTRL ; 
 scalar_t__ VIAWD_MEM_CTRL_FIRED ; 
 scalar_t__ VIAWD_MEM_LEN ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * device_get_parent (int /*<<< orphan*/ *) ; 
 struct viawd_softc* device_get_softc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ pci_read_config (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ rman_get_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  viawd_event ; 
 scalar_t__ viawd_read_4 (struct viawd_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  viawd_write_4 (struct viawd_softc*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  watchdog_list ; 

__attribute__((used)) static int
viawd_attach(device_t dev)
{
	device_t sb_dev;
	struct viawd_softc *sc;
	uint32_t pmbase, reg;

	sc = device_get_softc(dev);
	sc->dev = dev;

	sb_dev = device_get_parent(dev);
	if (sb_dev == NULL) {
		device_printf(dev, "Can not find watchdog device.\n");
		goto fail;
	}
	sc->sb_dev = sb_dev;

	/* Get watchdog memory base. */
	pmbase = pci_read_config(sb_dev, VIAWD_CONFIG_BASE, 4);
	if (pmbase == 0) {
		device_printf(dev,
		    "Watchdog disabled in BIOS or hardware\n");
		goto fail;
	}

	/* Allocate I/O register space. */
	sc->wd_rid = VIAWD_CONFIG_BASE;
	sc->wd_res = bus_alloc_resource_any(sb_dev, SYS_RES_MEMORY, &sc->wd_rid,
	    RF_ACTIVE | RF_SHAREABLE);
	if (sc->wd_res == NULL) {
		device_printf(dev, "Unable to map watchdog memory\n");
		goto fail;
	}
	if (rman_get_size(sc->wd_res) < VIAWD_MEM_LEN) {
		device_printf(dev, "Bad size for watchdog memory: %#x\n",
		    (unsigned)rman_get_size(sc->wd_res));
		goto fail;
	}

	/* Check if watchdog fired last boot. */
	reg = viawd_read_4(sc, VIAWD_MEM_CTRL);
	if (reg & VIAWD_MEM_CTRL_FIRED) {
		device_printf(dev,
		    "ERROR: watchdog rebooted the system\n");
		/* Reset bit state. */
		viawd_write_4(sc, VIAWD_MEM_CTRL, reg);
	}

	/* Register the watchdog event handler. */
	sc->ev_tag = EVENTHANDLER_REGISTER(watchdog_list, viawd_event, sc, 0);

	return (0);
fail:
	if (sc->wd_res != NULL)
		bus_release_resource(sb_dev, SYS_RES_MEMORY,
		    sc->wd_rid, sc->wd_res);
	return (ENXIO);
}