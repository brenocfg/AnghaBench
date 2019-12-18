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
struct tsec_softc {int tsec_link; int /*<<< orphan*/  tsec_callout; int /*<<< orphan*/  tsec_mii; struct ifnet* tsec_ifp; } ;
struct ifnet {int /*<<< orphan*/  if_snd; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFQ_DRV_IS_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TSEC_GLOBAL_LOCK (struct tsec_softc*) ; 
 int /*<<< orphan*/  TSEC_GLOBAL_UNLOCK (struct tsec_softc*) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*),struct tsec_softc*) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  mii_tick (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsec_start_locked (struct ifnet*) ; 
 int /*<<< orphan*/  tsec_watchdog (struct tsec_softc*) ; 

__attribute__((used)) static void
tsec_tick(void *arg)
{
	struct tsec_softc *sc = arg;
	struct ifnet *ifp;
	int link;

	TSEC_GLOBAL_LOCK(sc);

	tsec_watchdog(sc);

	ifp = sc->tsec_ifp;
	link = sc->tsec_link;

	mii_tick(sc->tsec_mii);

	if (link == 0 && sc->tsec_link == 1 &&
	    (!IFQ_DRV_IS_EMPTY(&ifp->if_snd)))
		tsec_start_locked(ifp);

	/* Schedule another timeout one second from now. */
	callout_reset(&sc->tsec_callout, hz, tsec_tick, sc);

	TSEC_GLOBAL_UNLOCK(sc);
}