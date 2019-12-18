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
struct ieee80211com {int dummy; } ;
struct ipw_softc {int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/ * sc_firmware; int /*<<< orphan*/  mem; int /*<<< orphan*/  irq; int /*<<< orphan*/  sc_snd; int /*<<< orphan*/  sc_wdtimer; int /*<<< orphan*/  sc_init_task; int /*<<< orphan*/  sc_ih; struct ieee80211com sc_ic; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  FIRMWARE_UNLOAD ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 struct ipw_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  firmware_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_draintask (struct ieee80211com*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_ifdetach (struct ieee80211com*) ; 
 int /*<<< orphan*/  ipw_release (struct ipw_softc*) ; 
 int /*<<< orphan*/  ipw_stop (struct ipw_softc*) ; 
 int /*<<< orphan*/  mbufq_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_rid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ipw_detach(device_t dev)
{
	struct ipw_softc *sc = device_get_softc(dev);
	struct ieee80211com *ic = &sc->sc_ic;

	bus_teardown_intr(dev, sc->irq, sc->sc_ih);

	ieee80211_draintask(ic, &sc->sc_init_task);
	ipw_stop(sc);

	ieee80211_ifdetach(ic);

	callout_drain(&sc->sc_wdtimer);
	mbufq_drain(&sc->sc_snd);

	ipw_release(sc);

	bus_release_resource(dev, SYS_RES_IRQ, rman_get_rid(sc->irq), sc->irq);

	bus_release_resource(dev, SYS_RES_MEMORY, rman_get_rid(sc->mem),
	    sc->mem);

	if (sc->sc_firmware != NULL) {
		firmware_put(sc->sc_firmware, FIRMWARE_UNLOAD);
		sc->sc_firmware = NULL;
	}

	mtx_destroy(&sc->sc_mtx);

	return 0;
}