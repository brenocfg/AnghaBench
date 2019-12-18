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
struct upgt_softc {int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_snd; int /*<<< orphan*/ * sc_xfer; int /*<<< orphan*/  sc_watchdog_ch; int /*<<< orphan*/  sc_led_ch; int /*<<< orphan*/  sc_rx_inactive; int /*<<< orphan*/  sc_rx_active; int /*<<< orphan*/  sc_tx_pending; int /*<<< orphan*/  sc_tx_inactive; int /*<<< orphan*/  sc_tx_active; int /*<<< orphan*/  sc_flags; struct ieee80211com sc_ic; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UPGT_FLAG_DETACHED ; 
 int /*<<< orphan*/  UPGT_LOCK (struct upgt_softc*) ; 
 unsigned int UPGT_N_XFERS ; 
 int /*<<< orphan*/  UPGT_UNLOCK (struct upgt_softc*) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 struct upgt_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_ifdetach (struct ieee80211com*) ; 
 int /*<<< orphan*/  mbufq_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  upgt_free_rx (struct upgt_softc*) ; 
 int /*<<< orphan*/  upgt_free_tx (struct upgt_softc*) ; 
 int /*<<< orphan*/  upgt_stop (struct upgt_softc*) ; 
 int /*<<< orphan*/  usbd_transfer_drain (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_transfer_unsetup (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static int
upgt_detach(device_t dev)
{
	struct upgt_softc *sc = device_get_softc(dev);
	struct ieee80211com *ic = &sc->sc_ic;
	unsigned int x;

	/*
	 * Prevent further allocations from RX/TX/CMD
	 * data lists and ioctls
	 */
	UPGT_LOCK(sc);
	sc->sc_flags |= UPGT_FLAG_DETACHED;

	STAILQ_INIT(&sc->sc_tx_active);
	STAILQ_INIT(&sc->sc_tx_inactive);
	STAILQ_INIT(&sc->sc_tx_pending);

	STAILQ_INIT(&sc->sc_rx_active);
	STAILQ_INIT(&sc->sc_rx_inactive);

	upgt_stop(sc);
	UPGT_UNLOCK(sc);

	callout_drain(&sc->sc_led_ch);
	callout_drain(&sc->sc_watchdog_ch);

	/* drain USB transfers */
	for (x = 0; x != UPGT_N_XFERS; x++)
		usbd_transfer_drain(sc->sc_xfer[x]);

	/* free data buffers */
	UPGT_LOCK(sc);
	upgt_free_rx(sc);
	upgt_free_tx(sc);
	UPGT_UNLOCK(sc);

	/* free USB transfers and some data buffers */
	usbd_transfer_unsetup(sc->sc_xfer, UPGT_N_XFERS);

	ieee80211_ifdetach(ic);
	mbufq_drain(&sc->sc_snd);
	mtx_destroy(&sc->sc_mtx);

	return (0);
}