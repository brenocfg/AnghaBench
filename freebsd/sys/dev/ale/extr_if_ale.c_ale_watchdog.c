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
struct ifnet {int /*<<< orphan*/  if_snd; int /*<<< orphan*/  if_drv_flags; } ;
struct ale_softc {scalar_t__ ale_watchdog_timer; int ale_flags; struct ifnet* ale_ifp; } ;

/* Variables and functions */
 int ALE_FLAG_LINK ; 
 int /*<<< orphan*/  ALE_LOCK_ASSERT (struct ale_softc*) ; 
 int /*<<< orphan*/  IFCOUNTER_OERRORS ; 
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  IFQ_DRV_IS_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ale_init_locked (struct ale_softc*) ; 
 int /*<<< orphan*/  ale_start_locked (struct ifnet*) ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  if_printf (struct ifnet*,char*) ; 

__attribute__((used)) static void
ale_watchdog(struct ale_softc *sc)
{
	struct ifnet *ifp;

	ALE_LOCK_ASSERT(sc);

	if (sc->ale_watchdog_timer == 0 || --sc->ale_watchdog_timer)
		return;

	ifp = sc->ale_ifp;
	if ((sc->ale_flags & ALE_FLAG_LINK) == 0) {
		if_printf(sc->ale_ifp, "watchdog timeout (lost link)\n");
		if_inc_counter(ifp, IFCOUNTER_OERRORS, 1);
		ifp->if_drv_flags &= ~IFF_DRV_RUNNING;
		ale_init_locked(sc);
		return;
	}
	if_printf(sc->ale_ifp, "watchdog timeout -- resetting\n");
	if_inc_counter(ifp, IFCOUNTER_OERRORS, 1);
	ifp->if_drv_flags &= ~IFF_DRV_RUNNING;
	ale_init_locked(sc);
	if (!IFQ_DRV_IS_EMPTY(&ifp->if_snd))
		ale_start_locked(ifp);
}