#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mge_softc {int phy_attached; scalar_t__ mge_media_status; int /*<<< orphan*/  wd_callout; int /*<<< orphan*/  ifp; TYPE_2__* mii; } ;
struct TYPE_3__ {scalar_t__ ifm_media; } ;
struct TYPE_4__ {TYPE_1__ mii_media; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MGE_GLOBAL_LOCK (struct mge_softc*) ; 
 int /*<<< orphan*/  MGE_GLOBAL_UNLOCK (struct mge_softc*) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*),struct mge_softc*) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  mge_ifmedia_upd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mge_watchdog (struct mge_softc*) ; 
 int /*<<< orphan*/  mii_tick (TYPE_2__*) ; 

__attribute__((used)) static void
mge_tick(void *msc)
{
	struct mge_softc *sc = msc;

	KASSERT(sc->phy_attached == 1, ("mge_tick while PHY not attached"));

	MGE_GLOBAL_LOCK(sc);

	/* Check for TX timeout */
	mge_watchdog(sc);

	mii_tick(sc->mii);

	/* Check for media type change */
	if(sc->mge_media_status != sc->mii->mii_media.ifm_media)
		mge_ifmedia_upd(sc->ifp);

	MGE_GLOBAL_UNLOCK(sc);

	/* Schedule another timeout one second from now */
	callout_reset(&sc->wd_callout, hz, mge_tick, sc);

	return;
}