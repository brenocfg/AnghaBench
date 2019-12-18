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
struct bwn_softc {int /*<<< orphan*/  sc_snd; int /*<<< orphan*/  sc_mem_res; int /*<<< orphan*/  sc_mem_rid; int /*<<< orphan*/  sc_tq; int /*<<< orphan*/  sc_watchdog_ch; int /*<<< orphan*/  sc_task_ch; int /*<<< orphan*/  sc_rfswitch_ch; int /*<<< orphan*/  sc_led_blink_ch; int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_flags; struct ieee80211com sc_ic; struct bwn_mac* sc_curmac; } ;
struct bwn_mac {int /*<<< orphan*/  mac_res_irq; int /*<<< orphan*/  mac_rid_irq; int /*<<< orphan*/ * mac_intrhand; int /*<<< orphan*/  mac_intrtask; int /*<<< orphan*/  mac_txpower; int /*<<< orphan*/  mac_hwreset; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BWN_FLAG_INVALID ; 
 int /*<<< orphan*/  BWN_LOCK (struct bwn_softc*) ; 
 int /*<<< orphan*/  BWN_LOCK_DESTROY (struct bwn_softc*) ; 
 int /*<<< orphan*/  BWN_UNLOCK (struct bwn_softc*) ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bhnd_release_pmu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bwn_dma_free (struct bwn_mac*) ; 
 int /*<<< orphan*/  bwn_phy_detach (struct bwn_mac*) ; 
 int /*<<< orphan*/  bwn_release_bus_providers (struct bwn_softc*) ; 
 int /*<<< orphan*/  bwn_release_firmware (struct bwn_mac*) ; 
 int /*<<< orphan*/  bwn_stop (struct bwn_softc*) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 struct bwn_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ device_is_attached (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_draintask (struct ieee80211com*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_ifdetach (struct ieee80211com*) ; 
 int /*<<< orphan*/  mbufq_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_drain (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bwn_detach(device_t dev)
{
	struct bwn_softc *sc = device_get_softc(dev);
	struct bwn_mac *mac = sc->sc_curmac;
	struct ieee80211com *ic = &sc->sc_ic;

	sc->sc_flags |= BWN_FLAG_INVALID;

	if (device_is_attached(sc->sc_dev)) {
		BWN_LOCK(sc);
		bwn_stop(sc);
		BWN_UNLOCK(sc);
		bwn_dma_free(mac);
		callout_drain(&sc->sc_led_blink_ch);
		callout_drain(&sc->sc_rfswitch_ch);
		callout_drain(&sc->sc_task_ch);
		callout_drain(&sc->sc_watchdog_ch);
		bwn_phy_detach(mac);
		ieee80211_draintask(ic, &mac->mac_hwreset);
		ieee80211_draintask(ic, &mac->mac_txpower);
		ieee80211_ifdetach(ic);
	}
	taskqueue_drain(sc->sc_tq, &mac->mac_intrtask);
	taskqueue_free(sc->sc_tq);

	if (mac->mac_intrhand != NULL) {
		bus_teardown_intr(dev, mac->mac_res_irq, mac->mac_intrhand);
		mac->mac_intrhand = NULL;
	}

	bhnd_release_pmu(dev);
	bus_release_resource(dev, SYS_RES_MEMORY, sc->sc_mem_rid,
	    sc->sc_mem_res);
	bus_release_resource(dev, SYS_RES_IRQ, mac->mac_rid_irq,
	    mac->mac_res_irq);
	mbufq_drain(&sc->sc_snd);
	bwn_release_firmware(mac);
	BWN_LOCK_DESTROY(sc);

	bwn_release_bus_providers(sc);

	return (0);
}