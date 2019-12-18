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
struct hme_softc {struct ifnet* sc_ifp; } ;

/* Variables and functions */
 int /*<<< orphan*/  HME_LOCK (struct hme_softc*) ; 
 int /*<<< orphan*/  HME_UNLOCK (struct hme_softc*) ; 
 int IFF_UP ; 
 int /*<<< orphan*/  hme_init_locked (struct hme_softc*) ; 

void
hme_resume(struct hme_softc *sc)
{
	struct ifnet *ifp = sc->sc_ifp;

	HME_LOCK(sc);
	if ((ifp->if_flags & IFF_UP) != 0)
		hme_init_locked(sc);
	HME_UNLOCK(sc);
}