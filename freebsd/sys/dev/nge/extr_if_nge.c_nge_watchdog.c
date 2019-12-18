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
struct nge_softc {scalar_t__ nge_watchdog_timer; struct ifnet* nge_ifp; } ;
struct ifnet {int /*<<< orphan*/  if_snd; int /*<<< orphan*/  if_drv_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFCOUNTER_OERRORS ; 
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  IFQ_DRV_IS_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NGE_LOCK_ASSERT (struct nge_softc*) ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  if_printf (struct ifnet*,char*) ; 
 int /*<<< orphan*/  nge_init_locked (struct nge_softc*) ; 
 int /*<<< orphan*/  nge_start_locked (struct ifnet*) ; 

__attribute__((used)) static void
nge_watchdog(struct nge_softc *sc)
{
	struct ifnet *ifp;

	NGE_LOCK_ASSERT(sc);

	if (sc->nge_watchdog_timer == 0 || --sc->nge_watchdog_timer)
		return;

	ifp = sc->nge_ifp;
	if_inc_counter(ifp, IFCOUNTER_OERRORS, 1);
	if_printf(ifp, "watchdog timeout\n");

	ifp->if_drv_flags &= ~IFF_DRV_RUNNING;
	nge_init_locked(sc);

	if (!IFQ_DRV_IS_EMPTY(&ifp->if_snd))
		nge_start_locked(ifp);
}