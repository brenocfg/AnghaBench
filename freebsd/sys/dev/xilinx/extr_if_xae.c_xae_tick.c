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
struct xae_softc {int link_is_up; int /*<<< orphan*/  xae_callout; struct ifnet* ifp; int /*<<< orphan*/  mii_softc; } ;
struct ifnet {int if_drv_flags; } ;

/* Variables and functions */
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  XAE_ASSERT_LOCKED (struct xae_softc*) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*),struct xae_softc*) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  mii_tick (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xae_harvest_stats (struct xae_softc*) ; 
 int /*<<< orphan*/  xae_transmit_locked (struct ifnet*) ; 

__attribute__((used)) static void
xae_tick(void *arg)
{
	struct xae_softc *sc;
	struct ifnet *ifp;
	int link_was_up;

	sc = arg;

	XAE_ASSERT_LOCKED(sc);

	ifp = sc->ifp;

	if (!(ifp->if_drv_flags & IFF_DRV_RUNNING))
		return;

	/* Gather stats from hardware counters. */
	xae_harvest_stats(sc);

	/* Check the media status. */
	link_was_up = sc->link_is_up;
	mii_tick(sc->mii_softc);
	if (sc->link_is_up && !link_was_up)
		xae_transmit_locked(sc->ifp);

	/* Schedule another check one second from now. */
	callout_reset(&sc->xae_callout, hz, xae_tick, sc);
}