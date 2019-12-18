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
struct lance_softc {int /*<<< orphan*/  (* sc_wrcsr ) (struct lance_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;scalar_t__ sc_wdog_timer; int /*<<< orphan*/  sc_wdog_ch; struct ifnet* sc_ifp; } ;
struct ifnet {int if_drv_flags; } ;

/* Variables and functions */
 int IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  LE_C0_STOP ; 
 int /*<<< orphan*/  LE_CSR0 ; 
 int /*<<< orphan*/  LE_LOCK_ASSERT (struct lance_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct lance_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
lance_stop(struct lance_softc *sc)
{
	struct ifnet *ifp = sc->sc_ifp;

	LE_LOCK_ASSERT(sc, MA_OWNED);

	/*
	 * Mark the interface down and cancel the watchdog timer.
	 */
	ifp->if_drv_flags &= ~(IFF_DRV_RUNNING | IFF_DRV_OACTIVE);
	callout_stop(&sc->sc_wdog_ch);
	sc->sc_wdog_timer = 0;

	(*sc->sc_wrcsr)(sc, LE_CSR0, LE_C0_STOP);
}