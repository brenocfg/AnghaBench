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
struct ste_softc {scalar_t__ ste_timer; struct ifnet* ste_ifp; } ;
struct ifnet {int /*<<< orphan*/  if_snd; int /*<<< orphan*/  if_drv_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFCOUNTER_OERRORS ; 
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  IFQ_DRV_IS_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STE_LOCK_ASSERT (struct ste_softc*) ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  if_printf (struct ifnet*,char*) ; 
 int /*<<< orphan*/  ste_init_locked (struct ste_softc*) ; 
 int /*<<< orphan*/  ste_rxeof (struct ste_softc*,int) ; 
 int /*<<< orphan*/  ste_start_locked (struct ifnet*) ; 
 int /*<<< orphan*/  ste_txeoc (struct ste_softc*) ; 
 int /*<<< orphan*/  ste_txeof (struct ste_softc*) ; 

__attribute__((used)) static void
ste_watchdog(struct ste_softc *sc)
{
	struct ifnet *ifp;

	ifp = sc->ste_ifp;
	STE_LOCK_ASSERT(sc);

	if (sc->ste_timer == 0 || --sc->ste_timer)
		return;

	if_inc_counter(ifp, IFCOUNTER_OERRORS, 1);
	if_printf(ifp, "watchdog timeout\n");

	ste_txeof(sc);
	ste_txeoc(sc);
	ste_rxeof(sc, -1);
	ifp->if_drv_flags &= ~IFF_DRV_RUNNING;
	ste_init_locked(sc);

	if (!IFQ_DRV_IS_EMPTY(&ifp->if_snd))
		ste_start_locked(ifp);
}