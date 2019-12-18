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
struct ifnet {struct axge_softc* if_softc; } ;
struct ifmediareq {int /*<<< orphan*/  ifm_status; int /*<<< orphan*/  ifm_active; } ;
struct axge_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AXGE_LOCK (struct axge_softc*) ; 
 int /*<<< orphan*/  AXGE_UNLOCK (struct axge_softc*) ; 
 struct mii_data* GET_MII (struct axge_softc*) ; 
 int /*<<< orphan*/  mii_pollstat (struct mii_data*) ; 

__attribute__((used)) static void
axge_ifmedia_sts(struct ifnet *ifp, struct ifmediareq *ifmr)
{
	struct axge_softc *sc;
	struct mii_data *mii;

	sc = ifp->if_softc;
	mii = GET_MII(sc);
	AXGE_LOCK(sc);
	mii_pollstat(mii);
	ifmr->ifm_active = mii->mii_media_active;
	ifmr->ifm_status = mii->mii_media_status;
	AXGE_UNLOCK(sc);
}