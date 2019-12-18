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
struct uath_softc {int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_snd; int /*<<< orphan*/ * sc_xfer; int /*<<< orphan*/  sc_cmd; int /*<<< orphan*/  watchdog_ch; int /*<<< orphan*/  stat_ch; int /*<<< orphan*/  sc_cmd_inactive; int /*<<< orphan*/  sc_cmd_waiting; int /*<<< orphan*/  sc_cmd_pending; int /*<<< orphan*/  sc_cmd_active; int /*<<< orphan*/  sc_tx_pending; int /*<<< orphan*/  sc_tx_inactive; int /*<<< orphan*/  sc_tx_active; int /*<<< orphan*/  sc_rx_inactive; int /*<<< orphan*/  sc_rx_active; int /*<<< orphan*/  sc_flags; struct ieee80211com sc_ic; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UATH_FLAG_INVALID ; 
 int /*<<< orphan*/  UATH_LOCK (struct uath_softc*) ; 
 unsigned int UATH_N_XFERS ; 
 int /*<<< orphan*/  UATH_UNLOCK (struct uath_softc*) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 struct uath_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_ifdetach (struct ieee80211com*) ; 
 int /*<<< orphan*/  mbufq_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uath_free_cmd_list (struct uath_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uath_free_rx_data_list (struct uath_softc*) ; 
 int /*<<< orphan*/  uath_free_tx_data_list (struct uath_softc*) ; 
 int /*<<< orphan*/  uath_stop (struct uath_softc*) ; 
 int /*<<< orphan*/  usbd_transfer_drain (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_transfer_unsetup (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static int
uath_detach(device_t dev)
{
	struct uath_softc *sc = device_get_softc(dev);
	struct ieee80211com *ic = &sc->sc_ic;
	unsigned int x;

	/*
	 * Prevent further allocations from RX/TX/CMD
	 * data lists and ioctls
	 */
	UATH_LOCK(sc);
	sc->sc_flags |= UATH_FLAG_INVALID;

	STAILQ_INIT(&sc->sc_rx_active);
	STAILQ_INIT(&sc->sc_rx_inactive);

	STAILQ_INIT(&sc->sc_tx_active);
	STAILQ_INIT(&sc->sc_tx_inactive);
	STAILQ_INIT(&sc->sc_tx_pending);

	STAILQ_INIT(&sc->sc_cmd_active);
	STAILQ_INIT(&sc->sc_cmd_pending);
	STAILQ_INIT(&sc->sc_cmd_waiting);
	STAILQ_INIT(&sc->sc_cmd_inactive);

	uath_stop(sc);
	UATH_UNLOCK(sc);

	callout_drain(&sc->stat_ch);
	callout_drain(&sc->watchdog_ch);

	/* drain USB transfers */
	for (x = 0; x != UATH_N_XFERS; x++)
		usbd_transfer_drain(sc->sc_xfer[x]);

	/* free data buffers */
	UATH_LOCK(sc);
	uath_free_rx_data_list(sc);
	uath_free_tx_data_list(sc);
	uath_free_cmd_list(sc, sc->sc_cmd);
	UATH_UNLOCK(sc);

	/* free USB transfers and some data buffers */
	usbd_transfer_unsetup(sc->sc_xfer, UATH_N_XFERS);

	ieee80211_ifdetach(ic);
	mbufq_drain(&sc->sc_snd);
	mtx_destroy(&sc->sc_mtx);
	return (0);
}