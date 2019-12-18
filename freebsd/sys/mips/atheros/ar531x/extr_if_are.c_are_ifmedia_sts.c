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
struct mii_data {int mii_media_status; int /*<<< orphan*/  mii_media_active; } ;
struct ifnet {struct are_softc* if_softc; } ;
struct ifmediareq {int ifm_status; int /*<<< orphan*/  ifm_active; } ;
struct are_softc {int /*<<< orphan*/  are_miibus; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARE_LOCK (struct are_softc*) ; 
 int /*<<< orphan*/  ARE_UNLOCK (struct are_softc*) ; 
 int IFM_ACTIVE ; 
 int IFM_AVALID ; 
 struct mii_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mii_pollstat (struct mii_data*) ; 

__attribute__((used)) static void
are_ifmedia_sts(struct ifnet *ifp, struct ifmediareq *ifmr)
{
#ifdef ARE_MII
	struct are_softc		*sc = ifp->if_softc;
	struct mii_data		*mii;

	mii = device_get_softc(sc->are_miibus);
	ARE_LOCK(sc);
	mii_pollstat(mii);
	ifmr->ifm_active = mii->mii_media_active;
	ifmr->ifm_status = mii->mii_media_status;
	ARE_UNLOCK(sc);
#else
	ifmr->ifm_status = IFM_AVALID | IFM_ACTIVE;
#endif
}