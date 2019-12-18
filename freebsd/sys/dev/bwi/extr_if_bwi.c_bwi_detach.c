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
struct bwi_softc {int sc_nmac; int /*<<< orphan*/  sc_snd; int /*<<< orphan*/  sc_tq; int /*<<< orphan*/ * sc_mac; int /*<<< orphan*/  sc_watchdog_timer; int /*<<< orphan*/  sc_calib_ch; int /*<<< orphan*/  sc_led_blink_ch; struct ieee80211com sc_ic; } ;

/* Variables and functions */
 int /*<<< orphan*/  BWI_LOCK_DESTROY (struct bwi_softc*) ; 
 int /*<<< orphan*/  bwi_dma_free (struct bwi_softc*) ; 
 int /*<<< orphan*/  bwi_mac_detach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bwi_stop (struct bwi_softc*,int) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_ifdetach (struct ieee80211com*) ; 
 int /*<<< orphan*/  mbufq_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_free (int /*<<< orphan*/ ) ; 

int
bwi_detach(struct bwi_softc *sc)
{
	struct ieee80211com *ic = &sc->sc_ic;
	int i;

	bwi_stop(sc, 1);
	callout_drain(&sc->sc_led_blink_ch);
	callout_drain(&sc->sc_calib_ch);
	callout_drain(&sc->sc_watchdog_timer);
	ieee80211_ifdetach(ic);

	for (i = 0; i < sc->sc_nmac; ++i)
		bwi_mac_detach(&sc->sc_mac[i]);
	bwi_dma_free(sc);
	taskqueue_free(sc->sc_tq);
	mbufq_drain(&sc->sc_snd);

	BWI_LOCK_DESTROY(sc);

	return (0);
}