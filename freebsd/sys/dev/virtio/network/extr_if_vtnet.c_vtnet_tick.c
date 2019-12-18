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
struct vtnet_softc {int vtnet_act_vq_pairs; int /*<<< orphan*/  vtnet_tick_ch; int /*<<< orphan*/ * vtnet_txqs; struct ifnet* vtnet_ifp; } ;
struct ifnet {int /*<<< orphan*/  if_drv_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  VTNET_CORE_LOCK_ASSERT (struct vtnet_softc*) ; 
 int /*<<< orphan*/  callout_schedule (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  vtnet_init_locked (struct vtnet_softc*) ; 
 int vtnet_watchdog (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
vtnet_tick(void *xsc)
{
	struct vtnet_softc *sc;
	struct ifnet *ifp;
	int i, timedout;

	sc = xsc;
	ifp = sc->vtnet_ifp;
	timedout = 0;

	VTNET_CORE_LOCK_ASSERT(sc);

	for (i = 0; i < sc->vtnet_act_vq_pairs; i++)
		timedout |= vtnet_watchdog(&sc->vtnet_txqs[i]);

	if (timedout != 0) {
		ifp->if_drv_flags &= ~IFF_DRV_RUNNING;
		vtnet_init_locked(sc);
	} else
		callout_schedule(&sc->vtnet_tick_ch, hz);
}