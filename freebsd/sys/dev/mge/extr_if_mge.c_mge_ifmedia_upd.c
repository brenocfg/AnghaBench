#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mge_softc {TYPE_2__* mii; int /*<<< orphan*/  mge_media_status; scalar_t__ phy_attached; } ;
struct ifnet {int if_flags; struct mge_softc* if_softc; } ;
struct TYPE_3__ {int /*<<< orphan*/  ifm_media; } ;
struct TYPE_4__ {TYPE_1__ mii_media; } ;

/* Variables and functions */
 int IFF_UP ; 
 int /*<<< orphan*/  MGE_GLOBAL_LOCK (struct mge_softc*) ; 
 int /*<<< orphan*/  MGE_GLOBAL_UNLOCK (struct mge_softc*) ; 
 int /*<<< orphan*/  mge_init_locked (struct mge_softc*) ; 
 int /*<<< orphan*/  mii_mediachg (TYPE_2__*) ; 

__attribute__((used)) static int
mge_ifmedia_upd(struct ifnet *ifp)
{
	struct mge_softc *sc = ifp->if_softc;

	/*
	 * Do not do anything for switch here, as updating media between
	 * MGE MAC and switch MAC is hardcoded in PCB. Changing it here would
	 * break the link.
	 */
	if (sc->phy_attached) {
		MGE_GLOBAL_LOCK(sc);
		if (ifp->if_flags & IFF_UP) {
			sc->mge_media_status = sc->mii->mii_media.ifm_media;
			mii_mediachg(sc->mii);

			/* MGE MAC needs to be reinitialized. */
			mge_init_locked(sc);

		}
		MGE_GLOBAL_UNLOCK(sc);
	}

	return (0);
}