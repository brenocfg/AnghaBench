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
struct jme_softc {int /*<<< orphan*/  jme_miibus; } ;
struct ifnet {int if_flags; struct jme_softc* if_softc; } ;
struct ifmediareq {int /*<<< orphan*/  ifm_active; int /*<<< orphan*/  ifm_status; } ;

/* Variables and functions */
 int IFF_UP ; 
 int /*<<< orphan*/  JME_LOCK (struct jme_softc*) ; 
 int /*<<< orphan*/  JME_UNLOCK (struct jme_softc*) ; 
 struct mii_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mii_pollstat (struct mii_data*) ; 

__attribute__((used)) static void
jme_mediastatus(struct ifnet *ifp, struct ifmediareq *ifmr)
{
	struct jme_softc *sc;
	struct mii_data *mii;

	sc = ifp->if_softc;
	JME_LOCK(sc);
	if ((ifp->if_flags & IFF_UP) == 0) {
		JME_UNLOCK(sc);
		return;
	}
	mii = device_get_softc(sc->jme_miibus);

	mii_pollstat(mii);
	ifmr->ifm_status = mii->mii_media_status;
	ifmr->ifm_active = mii->mii_media_active;
	JME_UNLOCK(sc);
}