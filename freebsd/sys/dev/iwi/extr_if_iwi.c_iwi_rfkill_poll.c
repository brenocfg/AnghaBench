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
struct iwi_softc {int /*<<< orphan*/  sc_rftimer; int /*<<< orphan*/  sc_radiontask; int /*<<< orphan*/  sc_ic; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWI_LOCK_ASSERT (struct iwi_softc*) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,void (*) (void*),struct iwi_softc*) ; 
 int hz ; 
 int /*<<< orphan*/  ieee80211_runtask (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwi_getrfkill (struct iwi_softc*) ; 

__attribute__((used)) static void
iwi_rfkill_poll(void *arg)
{
	struct iwi_softc *sc = arg;

	IWI_LOCK_ASSERT(sc);

	/*
	 * Check for a change in rfkill state.  We get an
	 * interrupt when a radio is disabled but not when
	 * it is enabled so we must poll for the latter.
	 */
	if (!iwi_getrfkill(sc)) {
		ieee80211_runtask(&sc->sc_ic, &sc->sc_radiontask);
		return;
	}
	callout_reset(&sc->sc_rftimer, 2*hz, iwi_rfkill_poll, sc);
}