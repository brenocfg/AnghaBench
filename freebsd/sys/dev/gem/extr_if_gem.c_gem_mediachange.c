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
struct ifnet {struct gem_softc* if_softc; } ;
struct gem_softc {int /*<<< orphan*/  sc_mii; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_LOCK (struct gem_softc*) ; 
 int /*<<< orphan*/  GEM_UNLOCK (struct gem_softc*) ; 
 int mii_mediachg (int /*<<< orphan*/ ) ; 

int
gem_mediachange(struct ifnet *ifp)
{
	struct gem_softc *sc = ifp->if_softc;
	int error;

	/* XXX add support for serial media. */

	GEM_LOCK(sc);
	error = mii_mediachg(sc->sc_mii);
	GEM_UNLOCK(sc);
	return (error);
}