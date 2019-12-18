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
struct bfe_softc {scalar_t__ bfe_watchdog_timer; int /*<<< orphan*/  bfe_dev; struct ifnet* bfe_ifp; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFE_LOCK_ASSERT (struct bfe_softc*) ; 
 int /*<<< orphan*/  IFCOUNTER_OERRORS ; 
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  IFQ_DRV_IS_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfe_init_locked (struct bfe_softc*) ; 
 int /*<<< orphan*/  bfe_start_locked (struct ifnet*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bfe_watchdog(struct bfe_softc *sc)
{
	struct ifnet *ifp;

	BFE_LOCK_ASSERT(sc);

	if (sc->bfe_watchdog_timer == 0 || --sc->bfe_watchdog_timer)
		return;

	ifp = sc->bfe_ifp;

	device_printf(sc->bfe_dev, "watchdog timeout -- resetting\n");

	if_inc_counter(ifp, IFCOUNTER_OERRORS, 1);
	ifp->if_drv_flags &= ~IFF_DRV_RUNNING;
	bfe_init_locked(sc);

	if (!IFQ_DRV_IS_EMPTY(&ifp->if_snd))
		bfe_start_locked(ifp);
}