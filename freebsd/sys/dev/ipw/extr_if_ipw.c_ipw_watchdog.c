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
struct ieee80211com {int /*<<< orphan*/  ic_vaps; int /*<<< orphan*/  ic_oerrors; } ;
struct ipw_softc {scalar_t__ sc_tx_timer; scalar_t__ sc_scan_timer; int flags; int /*<<< orphan*/  sc_wdtimer; int /*<<< orphan*/  sc_init_task; int /*<<< orphan*/  sc_dev; struct ieee80211com sc_ic; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int,char*) ; 
 int IPW_FLAG_RUNNING ; 
 int IPW_FLAG_SCANNING ; 
 int /*<<< orphan*/  IPW_LOCK (struct ipw_softc*) ; 
 int /*<<< orphan*/  IPW_LOCK_ASSERT (struct ipw_softc*) ; 
 int /*<<< orphan*/  IPW_UNLOCK (struct ipw_softc*) ; 
 int /*<<< orphan*/  TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*),struct ipw_softc*) ; 
 int /*<<< orphan*/  counter_u64_add (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  ieee80211_scan_done (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_swi ; 

__attribute__((used)) static void
ipw_watchdog(void *arg)
{
	struct ipw_softc *sc = arg;
	struct ieee80211com *ic = &sc->sc_ic;

	IPW_LOCK_ASSERT(sc);

	if (sc->sc_tx_timer > 0) {
		if (--sc->sc_tx_timer == 0) {
			device_printf(sc->sc_dev, "device timeout\n");
			counter_u64_add(ic->ic_oerrors, 1);
			taskqueue_enqueue(taskqueue_swi, &sc->sc_init_task);
		}
	}
	if (sc->sc_scan_timer > 0) {
		if (--sc->sc_scan_timer == 0) {
			DPRINTFN(3, ("Scan timeout\n"));
			/* End the scan */
			if (sc->flags & IPW_FLAG_SCANNING) {
				IPW_UNLOCK(sc);
				ieee80211_scan_done(TAILQ_FIRST(&ic->ic_vaps));
				IPW_LOCK(sc);
				sc->flags &= ~IPW_FLAG_SCANNING;
			}
		}
	}
	if (sc->flags & IPW_FLAG_RUNNING)
		callout_reset(&sc->sc_wdtimer, hz, ipw_watchdog, sc);
}