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
struct mii_data {int mii_media_active; int mii_media_status; } ;
struct mge_softc {struct mii_data* mii; int /*<<< orphan*/  phy_attached; } ;
struct ifnet {struct mge_softc* if_softc; } ;
struct ifmediareq {int ifm_active; int ifm_status; } ;

/* Variables and functions */
 int IFM_1000_T ; 
 int IFM_ACTIVE ; 
 int IFM_AVALID ; 
 int IFM_ETHER ; 
 int IFM_FDX ; 
 int /*<<< orphan*/  MGE_GLOBAL_LOCK (struct mge_softc*) ; 
 int /*<<< orphan*/  MGE_GLOBAL_UNLOCK (struct mge_softc*) ; 
 int /*<<< orphan*/  mii_pollstat (struct mii_data*) ; 

__attribute__((used)) static void
mge_ifmedia_sts(struct ifnet *ifp, struct ifmediareq *ifmr)
{
	struct mge_softc *sc;
	struct mii_data *mii;

	sc = ifp->if_softc;
	MGE_GLOBAL_LOCK(sc);

	if (!sc->phy_attached) {
		ifmr->ifm_active = IFM_1000_T | IFM_FDX | IFM_ETHER;
		ifmr->ifm_status = IFM_AVALID | IFM_ACTIVE;
		goto out_unlock;
	}

	mii = sc->mii;
	mii_pollstat(mii);

	ifmr->ifm_active = mii->mii_media_active;
	ifmr->ifm_status = mii->mii_media_status;

out_unlock:
	MGE_GLOBAL_UNLOCK(sc);
}