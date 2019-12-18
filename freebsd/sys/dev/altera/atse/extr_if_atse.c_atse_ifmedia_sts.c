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
struct ifnet {struct atse_softc* if_softc; } ;
struct ifmediareq {int /*<<< orphan*/  ifm_status; int /*<<< orphan*/  ifm_active; } ;
struct atse_softc {int /*<<< orphan*/  atse_miibus; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATSE_LOCK (struct atse_softc*) ; 
 int /*<<< orphan*/  ATSE_UNLOCK (struct atse_softc*) ; 
 struct mii_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mii_pollstat (struct mii_data*) ; 

__attribute__((used)) static void
atse_ifmedia_sts(struct ifnet *ifp, struct ifmediareq *ifmr)
{
	struct atse_softc *sc;
	struct mii_data *mii;

	sc = ifp->if_softc;

	ATSE_LOCK(sc);
	mii = device_get_softc(sc->atse_miibus);
	mii_pollstat(mii);
	ifmr->ifm_active = mii->mii_media_active;
	ifmr->ifm_status = mii->mii_media_status;
	ATSE_UNLOCK(sc);
}