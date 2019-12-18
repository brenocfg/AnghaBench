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
struct udav_softc {int dummy; } ;
struct mii_data {int /*<<< orphan*/  mii_media_status; int /*<<< orphan*/  mii_media_active; } ;
struct ifnet {struct udav_softc* if_softc; } ;
struct ifmediareq {int /*<<< orphan*/  ifm_status; int /*<<< orphan*/  ifm_active; } ;

/* Variables and functions */
 struct mii_data* GET_MII (struct udav_softc*) ; 
 int /*<<< orphan*/  UDAV_LOCK (struct udav_softc*) ; 
 int /*<<< orphan*/  UDAV_UNLOCK (struct udav_softc*) ; 
 int /*<<< orphan*/  mii_pollstat (struct mii_data*) ; 

__attribute__((used)) static void
udav_ifmedia_status(struct ifnet *ifp, struct ifmediareq *ifmr)
{
	struct udav_softc *sc = ifp->if_softc;
	struct mii_data *mii = GET_MII(sc);

	UDAV_LOCK(sc);
	mii_pollstat(mii);
	ifmr->ifm_active = mii->mii_media_active;
	ifmr->ifm_status = mii->mii_media_status;
	UDAV_UNLOCK(sc);
}