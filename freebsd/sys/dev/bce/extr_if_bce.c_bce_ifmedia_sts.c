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
struct ifnet {int if_flags; struct bce_softc* if_softc; } ;
struct ifmediareq {int /*<<< orphan*/  ifm_status; int /*<<< orphan*/  ifm_active; } ;
struct bce_softc {int bce_phy_flags; int /*<<< orphan*/  bce_miibus; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCE_LOCK (struct bce_softc*) ; 
 int BCE_PHY_REMOTE_CAP_FLAG ; 
 int /*<<< orphan*/  BCE_UNLOCK (struct bce_softc*) ; 
 int /*<<< orphan*/  BCE_VERBOSE_PHY ; 
 int /*<<< orphan*/  DBENTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBEXIT (int /*<<< orphan*/ ) ; 
 int IFF_UP ; 
 int /*<<< orphan*/  bce_ifmedia_sts_rphy (struct bce_softc*,struct ifmediareq*) ; 
 struct mii_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mii_pollstat (struct mii_data*) ; 

__attribute__((used)) static void
bce_ifmedia_sts(struct ifnet *ifp, struct ifmediareq *ifmr)
{
	struct bce_softc *sc = ifp->if_softc;
	struct mii_data *mii;

	DBENTER(BCE_VERBOSE_PHY);

	BCE_LOCK(sc);

	if ((ifp->if_flags & IFF_UP) == 0) {
		BCE_UNLOCK(sc);
		return;
	}

	if ((sc->bce_phy_flags & BCE_PHY_REMOTE_CAP_FLAG) != 0)
		bce_ifmedia_sts_rphy(sc, ifmr);
	else {
		mii = device_get_softc(sc->bce_miibus);
		mii_pollstat(mii);
		ifmr->ifm_active = mii->mii_media_active;
		ifmr->ifm_status = mii->mii_media_status;
	}

	BCE_UNLOCK(sc);

	DBEXIT(BCE_VERBOSE_PHY);
}