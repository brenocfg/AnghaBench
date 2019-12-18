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
struct ifnet {struct cas_softc* if_softc; } ;
struct cas_softc {int /*<<< orphan*/  sc_mii; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAS_LOCK (struct cas_softc*) ; 
 int /*<<< orphan*/  CAS_UNLOCK (struct cas_softc*) ; 
 int mii_mediachg (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cas_mediachange(struct ifnet *ifp)
{
	struct cas_softc *sc = ifp->if_softc;
	int error;

	/* XXX add support for serial media. */

	CAS_LOCK(sc);
	error = mii_mediachg(sc->sc_mii);
	CAS_UNLOCK(sc);
	return (error);
}