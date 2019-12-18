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
struct ifnet {struct cpswp_softc* if_softc; } ;
struct ifmediareq {int /*<<< orphan*/  ifm_status; int /*<<< orphan*/  ifm_active; } ;
struct cpswp_softc {struct mii_data* mii; int /*<<< orphan*/  swsc; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPSW_DEBUGF (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  CPSW_PORT_LOCK (struct cpswp_softc*) ; 
 int /*<<< orphan*/  CPSW_PORT_UNLOCK (struct cpswp_softc*) ; 
 int /*<<< orphan*/  mii_pollstat (struct mii_data*) ; 

__attribute__((used)) static void
cpswp_ifmedia_sts(struct ifnet *ifp, struct ifmediareq *ifmr)
{
	struct cpswp_softc *sc;
	struct mii_data *mii;

	sc = ifp->if_softc;
	CPSW_DEBUGF(sc->swsc, (""));
	CPSW_PORT_LOCK(sc);

	mii = sc->mii;
	mii_pollstat(mii);

	ifmr->ifm_active = mii->mii_media_active;
	ifmr->ifm_status = mii->mii_media_status;
	CPSW_PORT_UNLOCK(sc);
}