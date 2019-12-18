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
struct gem_softc {struct ifnet* sc_ifp; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_LOCK (struct gem_softc*) ; 
 int /*<<< orphan*/  GEM_UNLOCK (struct gem_softc*) ; 
 int /*<<< orphan*/  gem_stop (struct ifnet*,int /*<<< orphan*/ ) ; 

void
gem_suspend(struct gem_softc *sc)
{
	struct ifnet *ifp = sc->sc_ifp;

	GEM_LOCK(sc);
	gem_stop(ifp, 0);
	GEM_UNLOCK(sc);
}