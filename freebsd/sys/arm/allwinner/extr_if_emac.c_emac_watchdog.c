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
struct emac_softc {scalar_t__ emac_watchdog_timer; scalar_t__ emac_link; struct ifnet* emac_ifp; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMAC_ASSERT_LOCKED (struct emac_softc*) ; 
 int /*<<< orphan*/  IFCOUNTER_OERRORS ; 
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  IFQ_DRV_IS_EMPTY (int /*<<< orphan*/ *) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  emac_init_locked (struct emac_softc*) ; 
 int /*<<< orphan*/  emac_start_locked (struct ifnet*) ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  if_printf (struct ifnet*,char*) ; 

__attribute__((used)) static void
emac_watchdog(struct emac_softc *sc)
{
	struct ifnet *ifp;

	EMAC_ASSERT_LOCKED(sc);

	if (sc->emac_watchdog_timer == 0 || --sc->emac_watchdog_timer)
		return;

	ifp = sc->emac_ifp;

	if (sc->emac_link == 0) {
		if (bootverbose)
			if_printf(sc->emac_ifp, "watchdog timeout "
			    "(missed link)\n");
	} else
		if_printf(sc->emac_ifp, "watchdog timeout -- resetting\n");
	
	if_inc_counter(ifp, IFCOUNTER_OERRORS, 1);
	ifp->if_drv_flags &= ~IFF_DRV_RUNNING;
	emac_init_locked(sc);
	if (!IFQ_DRV_IS_EMPTY(&ifp->if_snd))
		emac_start_locked(ifp);
}