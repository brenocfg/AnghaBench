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
struct ifnet {int if_flags; } ;
struct cas_softc {int /*<<< orphan*/  sc_flags; struct ifnet* sc_ifp; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAS_INITED ; 
 int /*<<< orphan*/  CAS_LOCK (struct cas_softc*) ; 
 int /*<<< orphan*/  CAS_UNLOCK (struct cas_softc*) ; 
 int IFF_UP ; 
 int /*<<< orphan*/  cas_init_locked (struct cas_softc*) ; 

__attribute__((used)) static void
cas_resume(struct cas_softc *sc)
{
	struct ifnet *ifp = sc->sc_ifp;

	CAS_LOCK(sc);
	/*
	 * On resume all registers have to be initialized again like
	 * after power-on.
	 */
	sc->sc_flags &= ~CAS_INITED;
	if (ifp->if_flags & IFF_UP)
		cas_init_locked(sc);
	CAS_UNLOCK(sc);
}