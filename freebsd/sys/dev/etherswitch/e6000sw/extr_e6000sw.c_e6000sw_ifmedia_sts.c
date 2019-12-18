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
struct ifnet {int /*<<< orphan*/  if_dunit; int /*<<< orphan*/ * if_softc; } ;
struct ifmediareq {int /*<<< orphan*/  ifm_status; int /*<<< orphan*/  ifm_active; } ;
typedef  int /*<<< orphan*/  e6000sw_softc_t ;

/* Variables and functions */
 struct mii_data* e6000sw_miiforphy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mii_pollstat (struct mii_data*) ; 

__attribute__((used)) static void
e6000sw_ifmedia_sts(struct ifnet *ifp, struct ifmediareq *ifmr)
{
	e6000sw_softc_t *sc;
	struct mii_data *mii;

	sc = ifp->if_softc;
	mii = e6000sw_miiforphy(sc, ifp->if_dunit);

	if (mii == NULL)
		return;

	mii_pollstat(mii);
	ifmr->ifm_active = mii->mii_media_active;
	ifmr->ifm_status = mii->mii_media_status;
}