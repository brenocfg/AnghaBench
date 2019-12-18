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
typedef  int uint32_t ;
typedef  int u_long ;
struct hme_softc {int sc_burst; int /*<<< orphan*/  sc_lock; scalar_t__ sc_flags; int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_enaddr; void* sc_mifh; void* sc_mift; void* sc_mach; void* sc_mact; void* sc_erxh; void* sc_erxt; void* sc_etxh; void* sc_etxt; void* sc_sebh; void* sc_sebt; } ;
struct hme_sbus_softc {int /*<<< orphan*/ * hsc_seb_res; int /*<<< orphan*/ * hsc_etx_res; int /*<<< orphan*/ * hsc_erx_res; int /*<<< orphan*/ * hsc_mac_res; int /*<<< orphan*/ * hsc_mif_res; int /*<<< orphan*/ * hsc_ires; int /*<<< orphan*/  hsc_ih; struct hme_softc hsc_hme; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_NET ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  MTX_NETWORK_LOCK ; 
 int /*<<< orphan*/  OF_getetheraddr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int SBUS_BURST_16 ; 
 int SBUS_BURST_32 ; 
 int SBUS_BURST_64 ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 scalar_t__ bus_get_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,int*) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct hme_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_space_subregion (void*,void*,int,int,void**) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct hme_sbus_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int hme_config (struct hme_softc*) ; 
 int /*<<< orphan*/  hme_detach (struct hme_softc*) ; 
 int /*<<< orphan*/  hme_intr ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* rman_get_bushandle (int /*<<< orphan*/ *) ; 
 void* rman_get_bustag (int /*<<< orphan*/ *) ; 
 int rman_get_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_rid (int /*<<< orphan*/ *) ; 
 int rman_get_start (int /*<<< orphan*/ *) ; 
 int sbus_get_burstsz (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
hme_sbus_attach(device_t dev)
{
	struct hme_sbus_softc *hsc;
	struct hme_softc *sc;
	u_long start, count;
	uint32_t burst;
	int i, error = 0;

	hsc = device_get_softc(dev);
	sc = &hsc->hsc_hme;
	mtx_init(&sc->sc_lock, device_get_nameunit(dev), MTX_NETWORK_LOCK,
	    MTX_DEF);
	/*
	 * Map five register banks:
	 *
	 *	bank 0: HME SEB registers
	 *	bank 1: HME ETX registers
	 *	bank 2: HME ERX registers
	 *	bank 3: HME MAC registers
	 *	bank 4: HME MIF registers
	 *
	 */
	i = 0;
	hsc->hsc_seb_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY,
	    &i, RF_ACTIVE);
	if (hsc->hsc_seb_res == NULL) {
		device_printf(dev, "cannot map SEB registers\n");
		error = ENXIO;
		goto fail_mtx_res;
	}
	sc->sc_sebt = rman_get_bustag(hsc->hsc_seb_res);
	sc->sc_sebh = rman_get_bushandle(hsc->hsc_seb_res);

	i = 1;
	hsc->hsc_etx_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY,
	    &i, RF_ACTIVE);
	if (hsc->hsc_etx_res == NULL) {
		device_printf(dev, "cannot map ETX registers\n");
		error = ENXIO;
		goto fail_seb_res;
	}
	sc->sc_etxt = rman_get_bustag(hsc->hsc_etx_res);
	sc->sc_etxh = rman_get_bushandle(hsc->hsc_etx_res);

	i = 2;
	hsc->hsc_erx_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY,
	    &i, RF_ACTIVE);
	if (hsc->hsc_erx_res == NULL) {
		device_printf(dev, "cannot map ERX registers\n");
		error = ENXIO;
		goto fail_etx_res;
	}
	sc->sc_erxt = rman_get_bustag(hsc->hsc_erx_res);
	sc->sc_erxh = rman_get_bushandle(hsc->hsc_erx_res);

	i = 3;
	hsc->hsc_mac_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY,
	    &i, RF_ACTIVE);
	if (hsc->hsc_mac_res == NULL) {
		device_printf(dev, "cannot map MAC registers\n");
		error = ENXIO;
		goto fail_erx_res;
	}
	sc->sc_mact = rman_get_bustag(hsc->hsc_mac_res);
	sc->sc_mach = rman_get_bushandle(hsc->hsc_mac_res);

	/*
	 * At least on some HMEs, the MIF registers seem to be inside the MAC
	 * range, so try to kludge around it.
	 */
	i = 4;
	hsc->hsc_mif_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY,
	    &i, RF_ACTIVE);
	if (hsc->hsc_mif_res == NULL) {
		if (bus_get_resource(dev, SYS_RES_MEMORY, i,
		    &start, &count) != 0) {
			device_printf(dev, "cannot get MIF registers\n");
			error = ENXIO;
			goto fail_mac_res;
		}
		if (start < rman_get_start(hsc->hsc_mac_res) ||
		    start + count - 1 > rman_get_end(hsc->hsc_mac_res)) {
			device_printf(dev, "cannot move MIF registers to MAC "
			    "bank\n");
			error = ENXIO;
			goto fail_mac_res;
		}
		sc->sc_mift = sc->sc_mact;
		bus_space_subregion(sc->sc_mact, sc->sc_mach,
		    start - rman_get_start(hsc->hsc_mac_res), count,
		    &sc->sc_mifh);
	} else {
		sc->sc_mift = rman_get_bustag(hsc->hsc_mif_res);
		sc->sc_mifh = rman_get_bushandle(hsc->hsc_mif_res);
	}

	i = 0;
	hsc->hsc_ires = bus_alloc_resource_any(dev, SYS_RES_IRQ,
	    &i, RF_SHAREABLE | RF_ACTIVE);
	if (hsc->hsc_ires == NULL) {
		device_printf(dev, "could not allocate interrupt\n");
		error = ENXIO;
		goto fail_mif_res;
	}

	OF_getetheraddr(dev, sc->sc_enaddr);

	burst = sbus_get_burstsz(dev);
	/* Translate into plain numerical format */
	if ((burst & SBUS_BURST_64))
		sc->sc_burst = 64;
	else if ((burst & SBUS_BURST_32))
		sc->sc_burst = 32;
	else if ((burst & SBUS_BURST_16))
		sc->sc_burst = 16;
	else
		 sc->sc_burst = 0;

	sc->sc_dev = dev;
	sc->sc_flags = 0;

	if ((error = hme_config(sc)) != 0) {
		device_printf(dev, "could not be configured\n");
		goto fail_ires;
	}

	if ((error = bus_setup_intr(dev, hsc->hsc_ires, INTR_TYPE_NET |
	    INTR_MPSAFE, NULL, hme_intr, sc, &hsc->hsc_ih)) != 0) {
		device_printf(dev, "couldn't establish interrupt\n");
		hme_detach(sc);
		goto fail_ires;
	}
	return (0);

fail_ires:
	bus_release_resource(dev, SYS_RES_IRQ,
	    rman_get_rid(hsc->hsc_ires), hsc->hsc_ires);
fail_mif_res:
	if (hsc->hsc_mif_res != NULL) {
		bus_release_resource(dev, SYS_RES_MEMORY,
		    rman_get_rid(hsc->hsc_mif_res), hsc->hsc_mif_res);
	}
fail_mac_res:
	bus_release_resource(dev, SYS_RES_MEMORY,
	    rman_get_rid(hsc->hsc_mac_res), hsc->hsc_mac_res);
fail_erx_res:
	bus_release_resource(dev, SYS_RES_MEMORY,
	    rman_get_rid(hsc->hsc_erx_res), hsc->hsc_erx_res);
fail_etx_res:
	bus_release_resource(dev, SYS_RES_MEMORY,
	    rman_get_rid(hsc->hsc_etx_res), hsc->hsc_etx_res);
fail_seb_res:
	bus_release_resource(dev, SYS_RES_MEMORY,
	    rman_get_rid(hsc->hsc_seb_res), hsc->hsc_seb_res);
fail_mtx_res:
	mtx_destroy(&sc->sc_lock);
	return (error);
}