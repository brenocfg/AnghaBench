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
struct ieee80211com {struct zyd_softc* ic_softc; } ;
struct zyd_softc {int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/ * sc_xfer; int /*<<< orphan*/  tx_free; int /*<<< orphan*/  tx_q; int /*<<< orphan*/  sc_flags; struct ieee80211com sc_ic; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZYD_FLAG_DETACHED ; 
 int /*<<< orphan*/  ZYD_LOCK (struct zyd_softc*) ; 
 unsigned int ZYD_N_TRANSFER ; 
 int /*<<< orphan*/  ZYD_UNLOCK (struct zyd_softc*) ; 
 struct zyd_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_ifdetach (struct ieee80211com*) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbd_transfer_drain (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_transfer_unsetup (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  zyd_drain_mbufq (struct zyd_softc*) ; 
 int /*<<< orphan*/  zyd_unsetup_tx_list (struct zyd_softc*) ; 

__attribute__((used)) static int
zyd_detach(device_t dev)
{
	struct zyd_softc *sc = device_get_softc(dev);
	struct ieee80211com *ic = &sc->sc_ic;
	unsigned int x;

	/*
	 * Prevent further allocations from RX/TX data
	 * lists and ioctls:
	 */
	ZYD_LOCK(sc);
	sc->sc_flags |= ZYD_FLAG_DETACHED;
	zyd_drain_mbufq(sc);
	STAILQ_INIT(&sc->tx_q);
	STAILQ_INIT(&sc->tx_free);
	ZYD_UNLOCK(sc);

	/* drain USB transfers */
	for (x = 0; x != ZYD_N_TRANSFER; x++)
		usbd_transfer_drain(sc->sc_xfer[x]);

	/* free TX list, if any */
	ZYD_LOCK(sc);
	zyd_unsetup_tx_list(sc);
	ZYD_UNLOCK(sc);

	/* free USB transfers and some data buffers */
	usbd_transfer_unsetup(sc->sc_xfer, ZYD_N_TRANSFER);

	if (ic->ic_softc == sc)
		ieee80211_ifdetach(ic);
	mtx_destroy(&sc->sc_mtx);

	return (0);
}