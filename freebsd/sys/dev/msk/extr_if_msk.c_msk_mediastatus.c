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
struct msk_if_softc {int /*<<< orphan*/  msk_miibus; } ;
struct mii_data {int /*<<< orphan*/  mii_media_status; int /*<<< orphan*/  mii_media_active; } ;
struct ifnet {int if_flags; struct msk_if_softc* if_softc; } ;
struct ifmediareq {int /*<<< orphan*/  ifm_status; int /*<<< orphan*/  ifm_active; } ;

/* Variables and functions */
 int IFF_UP ; 
 int /*<<< orphan*/  MSK_IF_LOCK (struct msk_if_softc*) ; 
 int /*<<< orphan*/  MSK_IF_UNLOCK (struct msk_if_softc*) ; 
 struct mii_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mii_pollstat (struct mii_data*) ; 

__attribute__((used)) static void
msk_mediastatus(struct ifnet *ifp, struct ifmediareq *ifmr)
{
	struct msk_if_softc *sc_if;
	struct mii_data	*mii;

	sc_if = ifp->if_softc;
	MSK_IF_LOCK(sc_if);
	if ((ifp->if_flags & IFF_UP) == 0) {
		MSK_IF_UNLOCK(sc_if);
		return;
	}
	mii = device_get_softc(sc_if->msk_miibus);

	mii_pollstat(mii);
	ifmr->ifm_active = mii->mii_media_active;
	ifmr->ifm_status = mii->mii_media_status;
	MSK_IF_UNLOCK(sc_if);
}