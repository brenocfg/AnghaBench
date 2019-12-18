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
struct cas_softc {struct ifnet* sc_ifp; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAS_LOCK (struct cas_softc*) ; 
 int /*<<< orphan*/  CAS_UNLOCK (struct cas_softc*) ; 
 int /*<<< orphan*/  cas_stop (struct ifnet*) ; 

__attribute__((used)) static void
cas_suspend(struct cas_softc *sc)
{
	struct ifnet *ifp = sc->sc_ifp;

	CAS_LOCK(sc);
	cas_stop(ifp);
	CAS_UNLOCK(sc);
}