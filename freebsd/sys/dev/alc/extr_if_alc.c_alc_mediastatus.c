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
struct mii_data {int /*<<< orphan*/  mii_media_active; int /*<<< orphan*/  mii_media_status; } ;
struct ifnet {int if_flags; struct alc_softc* if_softc; } ;
struct ifmediareq {int /*<<< orphan*/  ifm_active; int /*<<< orphan*/  ifm_status; } ;
struct alc_softc {int /*<<< orphan*/  alc_miibus; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALC_LOCK (struct alc_softc*) ; 
 int /*<<< orphan*/  ALC_UNLOCK (struct alc_softc*) ; 
 int IFF_UP ; 
 struct mii_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mii_pollstat (struct mii_data*) ; 

__attribute__((used)) static void
alc_mediastatus(struct ifnet *ifp, struct ifmediareq *ifmr)
{
	struct alc_softc *sc;
	struct mii_data *mii;

	sc = ifp->if_softc;
	ALC_LOCK(sc);
	if ((ifp->if_flags & IFF_UP) == 0) {
		ALC_UNLOCK(sc);
		return;
	}
	mii = device_get_softc(sc->alc_miibus);

	mii_pollstat(mii);
	ifmr->ifm_status = mii->mii_media_status;
	ifmr->ifm_active = mii->mii_media_active;
	ALC_UNLOCK(sc);
}