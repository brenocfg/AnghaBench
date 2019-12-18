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
struct tsec_softc {scalar_t__ tsec_watchdog; struct ifnet* tsec_ifp; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFCOUNTER_OERRORS ; 
 int /*<<< orphan*/  TSEC_GLOBAL_LOCK_ASSERT (struct tsec_softc*) ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  if_printf (struct ifnet*,char*) ; 
 int /*<<< orphan*/  tsec_init_locked (struct tsec_softc*) ; 
 int /*<<< orphan*/  tsec_stop (struct tsec_softc*) ; 

__attribute__((used)) static void
tsec_watchdog(struct tsec_softc *sc)
{
	struct ifnet *ifp;

	TSEC_GLOBAL_LOCK_ASSERT(sc);

	if (sc->tsec_watchdog == 0 || --sc->tsec_watchdog > 0)
		return;

	ifp = sc->tsec_ifp;
	if_inc_counter(ifp, IFCOUNTER_OERRORS, 1);
	if_printf(ifp, "watchdog timeout\n");

	tsec_stop(sc);
	tsec_init_locked(sc);
}