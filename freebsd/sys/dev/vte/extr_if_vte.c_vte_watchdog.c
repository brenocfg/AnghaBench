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
struct vte_softc {scalar_t__ vte_watchdog_timer; struct ifnet* vte_ifp; } ;
struct ifnet {int /*<<< orphan*/  if_snd; int /*<<< orphan*/  if_drv_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFCOUNTER_OERRORS ; 
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  IFQ_DRV_IS_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VTE_LOCK_ASSERT (struct vte_softc*) ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  if_printf (struct ifnet*,char*) ; 
 int /*<<< orphan*/  vte_init_locked (struct vte_softc*) ; 
 int /*<<< orphan*/  vte_start_locked (struct vte_softc*) ; 

__attribute__((used)) static void
vte_watchdog(struct vte_softc *sc)
{
	struct ifnet *ifp;

	VTE_LOCK_ASSERT(sc);

	if (sc->vte_watchdog_timer == 0 || --sc->vte_watchdog_timer)
		return;

	ifp = sc->vte_ifp;
	if_printf(sc->vte_ifp, "watchdog timeout -- resetting\n");
	if_inc_counter(ifp, IFCOUNTER_OERRORS, 1);
	ifp->if_drv_flags &= ~IFF_DRV_RUNNING;
	vte_init_locked(sc);
	if (!IFQ_DRV_IS_EMPTY(&ifp->if_snd))
		vte_start_locked(sc);
}