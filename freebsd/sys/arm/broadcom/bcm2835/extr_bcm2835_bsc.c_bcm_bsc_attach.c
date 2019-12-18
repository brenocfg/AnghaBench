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
struct bcm_bsc_softc {int /*<<< orphan*/ * sc_iicbus; int /*<<< orphan*/  sc_mtx; void* sc_mem_res; void* sc_irq_res; int /*<<< orphan*/  sc_intrhand; int /*<<< orphan*/  sc_bsh; int /*<<< orphan*/  sc_bst; int /*<<< orphan*/  sc_dev; } ;
typedef  int /*<<< orphan*/  ich_func_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BCM_BSC_LOCK (struct bcm_bsc_softc*) ; 
 int /*<<< orphan*/  BCM_BSC_UNLOCK (struct bcm_bsc_softc*) ; 
 int ENXIO ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_MISC ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bcm_bsc_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm_bsc_intr ; 
 int /*<<< orphan*/  bcm_bsc_reset (struct bcm_bsc_softc*) ; 
 int /*<<< orphan*/  bcm_bsc_sysctl_init (struct bcm_bsc_softc*) ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 scalar_t__ bus_generic_attach ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 scalar_t__ bus_setup_intr (int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct bcm_bsc_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  config_intrhook_oneshot (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * device_add_child (int /*<<< orphan*/ ,char*,int) ; 
 struct bcm_bsc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bushandle (void*) ; 
 int /*<<< orphan*/  rman_get_bustag (void*) ; 

__attribute__((used)) static int
bcm_bsc_attach(device_t dev)
{
	struct bcm_bsc_softc *sc;
	int rid;

	sc = device_get_softc(dev);
	sc->sc_dev = dev;

	rid = 0;
	sc->sc_mem_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid,
	    RF_ACTIVE);
	if (!sc->sc_mem_res) {
		device_printf(dev, "cannot allocate memory window\n");
		return (ENXIO);
	}

	sc->sc_bst = rman_get_bustag(sc->sc_mem_res);
	sc->sc_bsh = rman_get_bushandle(sc->sc_mem_res);

	rid = 0;
	sc->sc_irq_res = bus_alloc_resource_any(dev, SYS_RES_IRQ, &rid,
	    RF_ACTIVE | RF_SHAREABLE);
	if (!sc->sc_irq_res) {
		bus_release_resource(dev, SYS_RES_MEMORY, 0, sc->sc_mem_res);
		device_printf(dev, "cannot allocate interrupt\n");
		return (ENXIO);
	}

	/* Hook up our interrupt handler. */
	if (bus_setup_intr(dev, sc->sc_irq_res, INTR_TYPE_MISC | INTR_MPSAFE,
	    NULL, bcm_bsc_intr, sc, &sc->sc_intrhand)) {
		bus_release_resource(dev, SYS_RES_IRQ, 0, sc->sc_irq_res);
		bus_release_resource(dev, SYS_RES_MEMORY, 0, sc->sc_mem_res);
		device_printf(dev, "cannot setup the interrupt handler\n");
		return (ENXIO);
	}

	mtx_init(&sc->sc_mtx, "bcm_bsc", NULL, MTX_DEF);

	bcm_bsc_sysctl_init(sc);

	/* Enable the BSC controller.  Flush the FIFO. */
	BCM_BSC_LOCK(sc);
	bcm_bsc_reset(sc);
	BCM_BSC_UNLOCK(sc);

	sc->sc_iicbus = device_add_child(dev, "iicbus", -1);
	if (sc->sc_iicbus == NULL) {
		bcm_bsc_detach(dev);
		return (ENXIO);
	}

	/* Probe and attach the iicbus when interrupts are available. */
	config_intrhook_oneshot((ich_func_t)bus_generic_attach, dev);

	return (0);
}