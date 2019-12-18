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
struct ieee80211com {scalar_t__ ic_nrunning; } ;
struct ath_softc {int sc_resume_up; int /*<<< orphan*/  sc_ah; int /*<<< orphan*/  sc_cal_ch; int /*<<< orphan*/  sc_tq; struct ieee80211com sc_ic; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH_LOCK (struct ath_softc*) ; 
 int /*<<< orphan*/  ATH_UNLOCK (struct ath_softc*) ; 
 int /*<<< orphan*/  ath_hal_enablepcie (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ath_hal_intrset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_suspend_all (struct ieee80211com*) ; 
 int /*<<< orphan*/  taskqueue_block (int /*<<< orphan*/ ) ; 

void
ath_suspend(struct ath_softc *sc)
{
	struct ieee80211com *ic = &sc->sc_ic;

	sc->sc_resume_up = ic->ic_nrunning != 0;

	ieee80211_suspend_all(ic);
	/*
	 * NB: don't worry about putting the chip in low power
	 * mode; pci will power off our socket on suspend and
	 * CardBus detaches the device.
	 *
	 * XXX TODO: well, that's great, except for non-cardbus
	 * devices!
	 */

	/*
	 * XXX This doesn't wait until all pending taskqueue
	 * items and parallel transmit/receive/other threads
	 * are running!
	 */
	ath_hal_intrset(sc->sc_ah, 0);
	taskqueue_block(sc->sc_tq);

	ATH_LOCK(sc);
	callout_stop(&sc->sc_cal_ch);
	ATH_UNLOCK(sc);

	/*
	 * XXX ensure sc_invalid is 1
	 */

	/* Disable the PCIe PHY, complete with workarounds */
	ath_hal_enablepcie(sc->sc_ah, 1, 1);
}