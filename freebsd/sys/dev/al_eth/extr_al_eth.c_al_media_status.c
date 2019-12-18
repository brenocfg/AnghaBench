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
struct mii_data {int mii_media_active; int /*<<< orphan*/  mii_media_status; } ;
struct ifnet {struct al_eth_adapter* if_softc; } ;
struct ifmediareq {int ifm_active; int /*<<< orphan*/  ifm_status; } ;
struct al_eth_adapter {struct mii_data* mii; } ;

/* Variables and functions */
 int IFM_ETHER ; 
 int IFM_NONE ; 
 int /*<<< orphan*/  mii_pollstat (struct mii_data*) ; 

__attribute__((used)) static void
al_media_status(struct ifnet *ifp, struct ifmediareq *ifmr)
{
	struct al_eth_adapter *sc = ifp->if_softc;
	struct mii_data *mii;

	if (sc->mii == NULL) {
		ifmr->ifm_active = IFM_ETHER | IFM_NONE;
		ifmr->ifm_status = 0;

		return;
	}

	mii = sc->mii;
	mii_pollstat(mii);

	ifmr->ifm_active = mii->mii_media_active;
	ifmr->ifm_status = mii->mii_media_status;
}