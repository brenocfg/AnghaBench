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
struct ieee80211com {struct ural_softc* ic_softc; } ;
struct ural_softc {int sc_detached; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_snd; int /*<<< orphan*/  sc_xfer; struct ieee80211com sc_ic; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  RAL_LOCK (struct ural_softc*) ; 
 int /*<<< orphan*/  RAL_UNLOCK (struct ural_softc*) ; 
 int /*<<< orphan*/  URAL_N_TRANSFER ; 
 struct ural_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_ifdetach (struct ieee80211com*) ; 
 int /*<<< orphan*/  mbufq_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ural_unsetup_tx_list (struct ural_softc*) ; 
 int /*<<< orphan*/  usbd_transfer_unsetup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ural_detach(device_t self)
{
	struct ural_softc *sc = device_get_softc(self);
	struct ieee80211com *ic = &sc->sc_ic;

	/* prevent further ioctls */
	RAL_LOCK(sc);
	sc->sc_detached = 1;
	RAL_UNLOCK(sc);

	/* stop all USB transfers */
	usbd_transfer_unsetup(sc->sc_xfer, URAL_N_TRANSFER);

	/* free TX list, if any */
	RAL_LOCK(sc);
	ural_unsetup_tx_list(sc);
	RAL_UNLOCK(sc);

	if (ic->ic_softc == sc)
		ieee80211_ifdetach(ic);
	mbufq_drain(&sc->sc_snd);
	mtx_destroy(&sc->sc_mtx);

	return (0);
}