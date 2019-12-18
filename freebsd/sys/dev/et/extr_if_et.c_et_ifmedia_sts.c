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
struct mii_data {int /*<<< orphan*/  mii_media_status; int /*<<< orphan*/  mii_media_active; } ;
struct ifnet {int if_flags; struct et_softc* if_softc; } ;
struct ifmediareq {int /*<<< orphan*/  ifm_status; int /*<<< orphan*/  ifm_active; } ;
struct et_softc {int /*<<< orphan*/  sc_miibus; } ;

/* Variables and functions */
 int /*<<< orphan*/  ET_LOCK (struct et_softc*) ; 
 int /*<<< orphan*/  ET_UNLOCK (struct et_softc*) ; 
 int IFF_UP ; 
 struct mii_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mii_pollstat (struct mii_data*) ; 

__attribute__((used)) static void
et_ifmedia_sts(struct ifnet *ifp, struct ifmediareq *ifmr)
{
	struct et_softc *sc;
	struct mii_data *mii;

	sc = ifp->if_softc;
	ET_LOCK(sc);
	if ((ifp->if_flags & IFF_UP) == 0) {
		ET_UNLOCK(sc);
		return;
	}

	mii = device_get_softc(sc->sc_miibus);
	mii_pollstat(mii);
	ifmr->ifm_active = mii->mii_media_active;
	ifmr->ifm_status = mii->mii_media_status;
	ET_UNLOCK(sc);
}