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
struct msk_if_softc {scalar_t__ msk_watchdog_timer; int msk_flags; struct ifnet* msk_ifp; } ;
struct ifnet {int /*<<< orphan*/  if_snd; int /*<<< orphan*/  if_drv_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFCOUNTER_OERRORS ; 
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  IFQ_DRV_IS_EMPTY (int /*<<< orphan*/ *) ; 
 int MSK_FLAG_LINK ; 
 int /*<<< orphan*/  MSK_IF_LOCK_ASSERT (struct msk_if_softc*) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  if_printf (struct ifnet*,char*) ; 
 int /*<<< orphan*/  msk_init_locked (struct msk_if_softc*) ; 
 int /*<<< orphan*/  msk_start_locked (struct ifnet*) ; 

__attribute__((used)) static void
msk_watchdog(struct msk_if_softc *sc_if)
{
	struct ifnet *ifp;

	MSK_IF_LOCK_ASSERT(sc_if);

	if (sc_if->msk_watchdog_timer == 0 || --sc_if->msk_watchdog_timer)
		return;
	ifp = sc_if->msk_ifp;
	if ((sc_if->msk_flags & MSK_FLAG_LINK) == 0) {
		if (bootverbose)
			if_printf(sc_if->msk_ifp, "watchdog timeout "
			   "(missed link)\n");
		if_inc_counter(ifp, IFCOUNTER_OERRORS, 1);
		ifp->if_drv_flags &= ~IFF_DRV_RUNNING;
		msk_init_locked(sc_if);
		return;
	}

	if_printf(ifp, "watchdog timeout\n");
	if_inc_counter(ifp, IFCOUNTER_OERRORS, 1);
	ifp->if_drv_flags &= ~IFF_DRV_RUNNING;
	msk_init_locked(sc_if);
	if (!IFQ_DRV_IS_EMPTY(&ifp->if_snd))
		msk_start_locked(ifp);
}