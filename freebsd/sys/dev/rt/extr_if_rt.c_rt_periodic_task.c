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
struct rt_softc {int periodic_round; int /*<<< orphan*/  periodic_ch; struct ifnet* ifp; } ;
struct ifnet {int if_drv_flags; } ;

/* Variables and functions */
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  RT_DEBUG_PERIODIC ; 
 int /*<<< orphan*/  RT_DPRINTF (struct rt_softc*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  RT_SOFTC_LOCK (struct rt_softc*) ; 
 int /*<<< orphan*/  RT_SOFTC_UNLOCK (struct rt_softc*) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct rt_softc*) ; 
 int hz ; 
 int /*<<< orphan*/  rt_periodic ; 
 int /*<<< orphan*/  rt_update_raw_counters (struct rt_softc*) ; 
 int /*<<< orphan*/  rt_update_stats (struct rt_softc*) ; 
 int /*<<< orphan*/  rt_watchdog (struct rt_softc*) ; 

__attribute__((used)) static void
rt_periodic_task(void *context, int pending)
{
	struct rt_softc *sc;
	struct ifnet *ifp;

	sc = context;
	ifp = sc->ifp;

	RT_DPRINTF(sc, RT_DEBUG_PERIODIC, "periodic task: round=%lu\n",
	    sc->periodic_round);

	if (!(ifp->if_drv_flags & IFF_DRV_RUNNING))
		return;

	RT_SOFTC_LOCK(sc);
	sc->periodic_round++;
	rt_update_stats(sc);

	if ((sc->periodic_round % 10) == 0) {
		rt_update_raw_counters(sc);
		rt_watchdog(sc);
	}

	RT_SOFTC_UNLOCK(sc);
	callout_reset(&sc->periodic_ch, hz / 10, rt_periodic, sc);
}