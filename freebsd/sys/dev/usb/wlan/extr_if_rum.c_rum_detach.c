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
struct ieee80211com {struct rum_softc* ic_softc; } ;
struct rum_softc {int sc_detached; int /*<<< orphan*/  sc_snd; int /*<<< orphan*/  cmdq_task; int /*<<< orphan*/  sc_xfer; struct ieee80211com sc_ic; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  RUM_CMDQ_LOCK_DESTROY (struct rum_softc*) ; 
 int /*<<< orphan*/  RUM_LOCK (struct rum_softc*) ; 
 int /*<<< orphan*/  RUM_LOCK_DESTROY (struct rum_softc*) ; 
 int /*<<< orphan*/  RUM_N_TRANSFER ; 
 int /*<<< orphan*/  RUM_UNLOCK (struct rum_softc*) ; 
 struct rum_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_draintask (struct ieee80211com*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_ifdetach (struct ieee80211com*) ; 
 int /*<<< orphan*/  mbufq_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rum_unsetup_tx_list (struct rum_softc*) ; 
 int /*<<< orphan*/  usbd_transfer_unsetup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
rum_detach(device_t self)
{
	struct rum_softc *sc = device_get_softc(self);
	struct ieee80211com *ic = &sc->sc_ic;

	/* Prevent further ioctls */
	RUM_LOCK(sc);
	sc->sc_detached = 1;
	RUM_UNLOCK(sc);

	/* stop all USB transfers */
	usbd_transfer_unsetup(sc->sc_xfer, RUM_N_TRANSFER);

	/* free TX list, if any */
	RUM_LOCK(sc);
	rum_unsetup_tx_list(sc);
	RUM_UNLOCK(sc);

	if (ic->ic_softc == sc) {
		ieee80211_draintask(ic, &sc->cmdq_task);
		ieee80211_ifdetach(ic);
	}

	mbufq_drain(&sc->sc_snd);
	RUM_CMDQ_LOCK_DESTROY(sc);
	RUM_LOCK_DESTROY(sc);

	return (0);
}