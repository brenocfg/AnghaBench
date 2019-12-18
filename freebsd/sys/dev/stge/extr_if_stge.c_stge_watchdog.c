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
struct stge_softc {scalar_t__ sc_watchdog_timer; struct ifnet* sc_ifp; } ;
struct ifnet {int /*<<< orphan*/  if_snd; int /*<<< orphan*/  if_drv_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFCOUNTER_OERRORS ; 
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  IFQ_DRV_IS_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STGE_LOCK_ASSERT (struct stge_softc*) ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  if_printf (struct ifnet*,char*) ; 
 int /*<<< orphan*/  stge_init_locked (struct stge_softc*) ; 
 int /*<<< orphan*/  stge_start_locked (struct ifnet*) ; 

__attribute__((used)) static void
stge_watchdog(struct stge_softc *sc)
{
	struct ifnet *ifp;

	STGE_LOCK_ASSERT(sc);

	if (sc->sc_watchdog_timer == 0 || --sc->sc_watchdog_timer)
		return;

	ifp = sc->sc_ifp;
	if_printf(sc->sc_ifp, "device timeout\n");
	if_inc_counter(ifp, IFCOUNTER_OERRORS, 1);
	ifp->if_drv_flags &= ~IFF_DRV_RUNNING;
	stge_init_locked(sc);
	if (!IFQ_DRV_IS_EMPTY(&ifp->if_snd))
		stge_start_locked(ifp);
}