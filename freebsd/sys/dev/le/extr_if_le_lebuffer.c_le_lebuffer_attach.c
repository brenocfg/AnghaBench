#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct lance_softc {int sc_conf3; int /*<<< orphan*/  sc_defaultmedia; int /*<<< orphan*/  sc_nsupmedia; int /*<<< orphan*/ * sc_supmedia; int /*<<< orphan*/ * sc_mediastatus; int /*<<< orphan*/ * sc_mediachange; int /*<<< orphan*/ * sc_nocarrier; int /*<<< orphan*/ * sc_hwintr; int /*<<< orphan*/ * sc_hwinit; int /*<<< orphan*/ * sc_hwreset; int /*<<< orphan*/  sc_wrcsr; int /*<<< orphan*/  sc_rdcsr; int /*<<< orphan*/  sc_zerobuf; int /*<<< orphan*/  sc_copyfrombuf; int /*<<< orphan*/  sc_copytobuf; int /*<<< orphan*/  sc_copyfromdesc; int /*<<< orphan*/  sc_copytodesc; int /*<<< orphan*/  sc_enaddr; scalar_t__ sc_flags; int /*<<< orphan*/  sc_memsize; scalar_t__ sc_addr; } ;
struct TYPE_3__ {struct lance_softc lsc; } ;
struct le_lebuffer_softc {int /*<<< orphan*/ * sc_bres; int /*<<< orphan*/ * sc_rres; int /*<<< orphan*/ * sc_ires; TYPE_1__ sc_am7990; int /*<<< orphan*/  sc_ih; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_NET ; 
 int LE_C3_ACON ; 
 int LE_C3_BCON ; 
 int LE_C3_BSWP ; 
 int /*<<< orphan*/  LE_LOCK_DESTROY (struct lance_softc*) ; 
 int /*<<< orphan*/  LE_LOCK_INIT (struct lance_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NLEMEDIA ; 
 int /*<<< orphan*/  OF_getetheraddr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int OF_getprop (int /*<<< orphan*/ ,char*,int*,int) ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int am7990_config (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  am7990_detach (TYPE_1__*) ; 
 int /*<<< orphan*/  am7990_intr ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct lance_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct le_lebuffer_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  le_lebuffer_copyfrombuf ; 
 int /*<<< orphan*/  le_lebuffer_copyfromdesc ; 
 int /*<<< orphan*/  le_lebuffer_copytobuf ; 
 int /*<<< orphan*/  le_lebuffer_copytodesc ; 
 int /*<<< orphan*/ * le_lebuffer_media ; 
 int /*<<< orphan*/  le_lebuffer_rdcsr ; 
 int /*<<< orphan*/  le_lebuffer_wrcsr ; 
 int /*<<< orphan*/  le_lebuffer_zerobuf ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_rid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_size (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
le_lebuffer_attach(device_t dev)
{
	struct le_lebuffer_softc *lesc;
	struct lance_softc *sc;
	int error, i;

	lesc = device_get_softc(dev);
	sc = &lesc->sc_am7990.lsc;

	LE_LOCK_INIT(sc, device_get_nameunit(dev));

	/*
	 * The "register space" of the parent is just a buffer where the
	 * the LANCE descriptor rings and the RX/TX buffers can be stored.
	 */
	i = 0;
	lesc->sc_bres = bus_alloc_resource_any(device_get_parent(dev),
	    SYS_RES_MEMORY, &i, RF_ACTIVE);
	if (lesc->sc_bres == NULL) {
		device_printf(dev, "cannot allocate LANCE buffer\n");
		error = ENXIO;
		goto fail_mtx;
	}

	/* Allocate LANCE registers. */
	i = 0;
	lesc->sc_rres = bus_alloc_resource_any(dev, SYS_RES_MEMORY,
	    &i, RF_ACTIVE);
	if (lesc->sc_rres == NULL) {
		device_printf(dev, "cannot allocate LANCE registers\n");
		error = ENXIO;
		goto fail_bres;
	}

	/* Allocate LANCE interrupt. */
	i = 0;
	if ((lesc->sc_ires = bus_alloc_resource_any(dev, SYS_RES_IRQ,
	    &i, RF_SHAREABLE | RF_ACTIVE)) == NULL) {
		device_printf(dev, "cannot allocate interrupt\n");
		error = ENXIO;
		goto fail_rres;
	}

	/*
	 * LANCE view is offset by buffer location.
	 * Note that we don't use sc->sc_mem.
	 */
	sc->sc_addr = 0;
	sc->sc_memsize = rman_get_size(lesc->sc_bres);
	sc->sc_flags = 0;

	/* That old black magic... */
	if (OF_getprop(ofw_bus_get_node(dev), "busmaster-regval",
	    &sc->sc_conf3, sizeof(sc->sc_conf3)) == -1)
		sc->sc_conf3 = LE_C3_ACON | LE_C3_BCON;
	/*
	 * Make sure LE_C3_BSWP is cleared so that for cards where
	 * that flag actually works le_lebuffer_copy{from,to}buf()
	 * don't fail...
	 */
	sc->sc_conf3 &= ~LE_C3_BSWP;

	OF_getetheraddr(dev, sc->sc_enaddr);

	sc->sc_copytodesc = le_lebuffer_copytodesc;
	sc->sc_copyfromdesc = le_lebuffer_copyfromdesc;
	sc->sc_copytobuf = le_lebuffer_copytobuf;
	sc->sc_copyfrombuf = le_lebuffer_copyfrombuf;
	sc->sc_zerobuf = le_lebuffer_zerobuf;

	sc->sc_rdcsr = le_lebuffer_rdcsr;
	sc->sc_wrcsr = le_lebuffer_wrcsr;
	sc->sc_hwreset = NULL;
	sc->sc_hwinit = NULL;
	sc->sc_hwintr = NULL;
	sc->sc_nocarrier = NULL;
	sc->sc_mediachange = NULL;
	sc->sc_mediastatus = NULL;
	sc->sc_supmedia = le_lebuffer_media;
	sc->sc_nsupmedia = NLEMEDIA;
	sc->sc_defaultmedia = le_lebuffer_media[0];

	error = am7990_config(&lesc->sc_am7990, device_get_name(dev),
	    device_get_unit(dev));
	if (error != 0) {
		device_printf(dev, "cannot attach Am7990\n");
		goto fail_ires;
	}

	error = bus_setup_intr(dev, lesc->sc_ires, INTR_TYPE_NET | INTR_MPSAFE,
	    NULL, am7990_intr, sc, &lesc->sc_ih);
	if (error != 0) {
		device_printf(dev, "cannot set up interrupt\n");
		goto fail_am7990;
	}

	return (0);

 fail_am7990:
	am7990_detach(&lesc->sc_am7990);
 fail_ires:
	bus_release_resource(dev, SYS_RES_IRQ,
	    rman_get_rid(lesc->sc_ires), lesc->sc_ires);
 fail_rres:
	bus_release_resource(dev, SYS_RES_MEMORY,
	    rman_get_rid(lesc->sc_rres), lesc->sc_rres);
 fail_bres:
	bus_release_resource(device_get_parent(dev), SYS_RES_MEMORY,
	    rman_get_rid(lesc->sc_bres), lesc->sc_bres);
 fail_mtx:
	LE_LOCK_DESTROY(sc);
	return (error);
}