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
struct lance_softc {scalar_t__ sc_wdog_timer; int /*<<< orphan*/  sc_wdog_ch; struct ifnet* sc_ifp; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFCOUNTER_OERRORS ; 
 int /*<<< orphan*/  LE_LOCK_ASSERT (struct lance_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*),struct lance_softc*) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  if_printf (struct ifnet*,char*) ; 
 int /*<<< orphan*/  lance_init_locked (struct lance_softc*) ; 

__attribute__((used)) static void
lance_watchdog(void *xsc)
{
	struct lance_softc *sc = (struct lance_softc *)xsc;
	struct ifnet *ifp = sc->sc_ifp;

	LE_LOCK_ASSERT(sc, MA_OWNED);

	if (sc->sc_wdog_timer == 0 || --sc->sc_wdog_timer != 0) {
		callout_reset(&sc->sc_wdog_ch, hz, lance_watchdog, sc);
		return;
	}

	if_printf(ifp, "device timeout\n");
	if_inc_counter(ifp, IFCOUNTER_OERRORS, 1);
	lance_init_locked(sc);
}