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
struct my_softc {scalar_t__ my_timer; struct ifnet* my_ifp; int /*<<< orphan*/  my_watchdog; } ;
struct ifnet {int /*<<< orphan*/  if_snd; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFCOUNTER_OERRORS ; 
 int /*<<< orphan*/  IFQ_DRV_IS_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MY_LOCK_ASSERT (struct my_softc*) ; 
 int /*<<< orphan*/  PHY_BMSR ; 
 int PHY_BMSR_LINKSTAT ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*),struct my_softc*) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  if_printf (struct ifnet*,char*) ; 
 int /*<<< orphan*/  my_init_locked (struct my_softc*) ; 
 int my_phy_readreg (struct my_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  my_reset (struct my_softc*) ; 
 int /*<<< orphan*/  my_start_locked (struct ifnet*) ; 
 int /*<<< orphan*/  my_stop (struct my_softc*) ; 

__attribute__((used)) static void
my_watchdog(void *arg)
{
	struct my_softc *sc;
	struct ifnet *ifp;

	sc = arg;
	MY_LOCK_ASSERT(sc);
	callout_reset(&sc->my_watchdog, hz, my_watchdog, sc);
	if (sc->my_timer == 0 || --sc->my_timer > 0)
		return;

	ifp = sc->my_ifp;
	if_inc_counter(ifp, IFCOUNTER_OERRORS, 1);
	if_printf(ifp, "watchdog timeout\n");
	if (!(my_phy_readreg(sc, PHY_BMSR) & PHY_BMSR_LINKSTAT))
		if_printf(ifp, "no carrier - transceiver cable problem?\n");
	my_stop(sc);
	my_reset(sc);
	my_init_locked(sc);
	if (!IFQ_DRV_IS_EMPTY(&ifp->if_snd))
		my_start_locked(ifp);
}