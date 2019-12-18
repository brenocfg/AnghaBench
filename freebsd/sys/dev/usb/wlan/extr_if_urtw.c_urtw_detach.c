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
struct urtw_softc {int sc_flags; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_snd; int /*<<< orphan*/ * sc_xfer; int /*<<< orphan*/  sc_rx_inactive; int /*<<< orphan*/  sc_rx_active; int /*<<< orphan*/  sc_tx_pending; int /*<<< orphan*/  sc_tx_inactive; int /*<<< orphan*/  sc_tx_active; int /*<<< orphan*/  sc_watchdog_ch; int /*<<< orphan*/  sc_led_ch; int /*<<< orphan*/  sc_led_task; int /*<<< orphan*/  sc_updateslot_task; struct ieee80211com sc_ic; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 unsigned int URTW_8187B_N_XFERS ; 
 unsigned int URTW_8187L_N_XFERS ; 
 int URTW_DETACHED ; 
 int /*<<< orphan*/  URTW_LOCK (struct urtw_softc*) ; 
 int URTW_RTL8187B ; 
 int /*<<< orphan*/  URTW_UNLOCK (struct urtw_softc*) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 struct urtw_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_draintask (struct ieee80211com*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_ifdetach (struct ieee80211com*) ; 
 int /*<<< orphan*/  mbufq_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  urtw_free_rx_data_list (struct urtw_softc*) ; 
 int /*<<< orphan*/  urtw_free_tx_data_list (struct urtw_softc*) ; 
 int /*<<< orphan*/  urtw_stop (struct urtw_softc*) ; 
 int /*<<< orphan*/  usb_callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbd_transfer_drain (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_transfer_unsetup (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static int
urtw_detach(device_t dev)
{
	struct urtw_softc *sc = device_get_softc(dev);
	struct ieee80211com *ic = &sc->sc_ic;
	unsigned int x;
	unsigned int n_xfers;

	/* Prevent further ioctls */
	URTW_LOCK(sc);
	sc->sc_flags |= URTW_DETACHED;
	urtw_stop(sc);
	URTW_UNLOCK(sc);

	ieee80211_draintask(ic, &sc->sc_updateslot_task);
	ieee80211_draintask(ic, &sc->sc_led_task);

	usb_callout_drain(&sc->sc_led_ch);
	callout_drain(&sc->sc_watchdog_ch);

	n_xfers = (sc->sc_flags & URTW_RTL8187B) ?
	    URTW_8187B_N_XFERS : URTW_8187L_N_XFERS;

	/* prevent further allocations from RX/TX data lists */
	URTW_LOCK(sc);
	STAILQ_INIT(&sc->sc_tx_active);
	STAILQ_INIT(&sc->sc_tx_inactive);
	STAILQ_INIT(&sc->sc_tx_pending);

	STAILQ_INIT(&sc->sc_rx_active);
	STAILQ_INIT(&sc->sc_rx_inactive);
	URTW_UNLOCK(sc);

	/* drain USB transfers */
	for (x = 0; x != n_xfers; x++)
		usbd_transfer_drain(sc->sc_xfer[x]);

	/* free data buffers */
	URTW_LOCK(sc);
	urtw_free_tx_data_list(sc);
	urtw_free_rx_data_list(sc);
	URTW_UNLOCK(sc);

	/* free USB transfers and some data buffers */
	usbd_transfer_unsetup(sc->sc_xfer, n_xfers);

	ieee80211_ifdetach(ic);
	mbufq_drain(&sc->sc_snd);
	mtx_destroy(&sc->sc_mtx);
	return (0);
}