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
struct ieee80211com {struct run_softc* ic_softc; } ;
struct run_softc {int sc_detached; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  ratectl_task; int /*<<< orphan*/  cmdq_task; int /*<<< orphan*/  ratectl_ch; struct ieee80211com sc_ic; int /*<<< orphan*/ * sc_epq; int /*<<< orphan*/  cmdq_key_set; int /*<<< orphan*/  cmdq_run; int /*<<< orphan*/  ratectl_run; int /*<<< orphan*/  sc_xfer; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  RUN_CMDQ_ABORT ; 
 int RUN_EP_QUEUES ; 
 int /*<<< orphan*/  RUN_LOCK (struct run_softc*) ; 
 int /*<<< orphan*/  RUN_N_XFER ; 
 int /*<<< orphan*/  RUN_RATECTL_OFF ; 
 int /*<<< orphan*/  RUN_UNLOCK (struct run_softc*) ; 
 struct run_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_draintask (struct ieee80211com*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_ifdetach (struct ieee80211com*) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  run_drain_mbufq (struct run_softc*) ; 
 int /*<<< orphan*/  run_unsetup_tx_list (struct run_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbd_transfer_unsetup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
run_detach(device_t self)
{
	struct run_softc *sc = device_get_softc(self);
	struct ieee80211com *ic = &sc->sc_ic;
	int i;

	RUN_LOCK(sc);
	sc->sc_detached = 1;
	RUN_UNLOCK(sc);

	/* stop all USB transfers */
	usbd_transfer_unsetup(sc->sc_xfer, RUN_N_XFER);

	RUN_LOCK(sc);
	sc->ratectl_run = RUN_RATECTL_OFF;
	sc->cmdq_run = sc->cmdq_key_set = RUN_CMDQ_ABORT;

	/* free TX list, if any */
	for (i = 0; i != RUN_EP_QUEUES; i++)
		run_unsetup_tx_list(sc, &sc->sc_epq[i]);

	/* Free TX queue */
	run_drain_mbufq(sc);
	RUN_UNLOCK(sc);

	if (sc->sc_ic.ic_softc == sc) {
		/* drain tasks */
		usb_callout_drain(&sc->ratectl_ch);
		ieee80211_draintask(ic, &sc->cmdq_task);
		ieee80211_draintask(ic, &sc->ratectl_task);
		ieee80211_ifdetach(ic);
	}

	mtx_destroy(&sc->sc_mtx);

	return (0);
}