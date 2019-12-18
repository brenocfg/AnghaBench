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
struct ifnet {int if_drv_flags; } ;
struct dwc_softc {scalar_t__ tx_watchdog_count; int link_is_up; int /*<<< orphan*/  dwc_callout; int /*<<< orphan*/  mii_softc; struct ifnet* ifp; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_ASSERT_LOCKED (struct dwc_softc*) ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*),struct dwc_softc*) ; 
 int /*<<< orphan*/  dwc_harvest_stats (struct dwc_softc*) ; 
 int /*<<< orphan*/  dwc_txfinish_locked (struct dwc_softc*) ; 
 int /*<<< orphan*/  dwc_txstart_locked (struct dwc_softc*) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  mii_tick (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dwc_tick(void *arg)
{
	struct dwc_softc *sc;
	struct ifnet *ifp;
	int link_was_up;

	sc = arg;

	DWC_ASSERT_LOCKED(sc);

	ifp = sc->ifp;

	if (!(ifp->if_drv_flags & IFF_DRV_RUNNING))
	    return;

	/*
	 * Typical tx watchdog.  If this fires it indicates that we enqueued
	 * packets for output and never got a txdone interrupt for them.  Maybe
	 * it's a missed interrupt somehow, just pretend we got one.
	 */
	if (sc->tx_watchdog_count > 0) {
		if (--sc->tx_watchdog_count == 0) {
			dwc_txfinish_locked(sc);
		}
	}

	/* Gather stats from hardware counters. */
	dwc_harvest_stats(sc);

	/* Check the media status. */
	link_was_up = sc->link_is_up;
	mii_tick(sc->mii_softc);
	if (sc->link_is_up && !link_was_up)
		dwc_txstart_locked(sc);

	/* Schedule another check one second from now. */
	callout_reset(&sc->dwc_callout, hz, dwc_tick, sc);
}