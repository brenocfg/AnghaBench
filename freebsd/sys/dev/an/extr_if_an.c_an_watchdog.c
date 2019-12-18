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
struct ifnet {int dummy; } ;
struct an_softc {scalar_t__ mpi350; struct ifnet* an_ifp; scalar_t__ an_gone; } ;

/* Variables and functions */
 int /*<<< orphan*/  AN_LOCK_ASSERT (struct an_softc*) ; 
 int /*<<< orphan*/  IFCOUNTER_OERRORS ; 
 int /*<<< orphan*/  an_init_locked (struct an_softc*) ; 
 int /*<<< orphan*/  an_init_mpi350_desc (struct an_softc*) ; 
 int /*<<< orphan*/  an_reset (struct an_softc*) ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  if_printf (struct ifnet*,char*) ; 

__attribute__((used)) static void
an_watchdog(struct an_softc *sc)
{
	struct ifnet *ifp;

	AN_LOCK_ASSERT(sc);

	if (sc->an_gone)
		return;

	ifp = sc->an_ifp;
	if_printf(ifp, "device timeout\n");

	an_reset(sc);
	if (sc->mpi350)
		an_init_mpi350_desc(sc);
	an_init_locked(sc);

	if_inc_counter(ifp, IFCOUNTER_OERRORS, 1);
}