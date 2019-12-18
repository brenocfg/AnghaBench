#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mii_data {int /*<<< orphan*/  mii_media_status; int /*<<< orphan*/  mii_media_active; } ;
struct ifnet {TYPE_1__* if_softc; } ;
struct ifmediareq {int /*<<< orphan*/  ifm_status; int /*<<< orphan*/  ifm_active; } ;
struct TYPE_2__ {int /*<<< orphan*/  miibus; } ;
typedef  TYPE_1__ cvm_oct_private_t ;

/* Variables and functions */
 struct mii_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mii_pollstat (struct mii_data*) ; 

__attribute__((used)) static void
octe_mii_medstat(struct ifnet *ifp, struct ifmediareq *ifm)
{
	cvm_oct_private_t *priv;
	struct mii_data *mii;

	priv = ifp->if_softc;
	mii = device_get_softc(priv->miibus);

	mii_pollstat(mii);
	ifm->ifm_active = mii->mii_media_active;
	ifm->ifm_status = mii->mii_media_status;
}