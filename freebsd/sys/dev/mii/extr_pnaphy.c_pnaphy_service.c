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
struct mii_softc {int dummy; } ;
struct TYPE_2__ {struct ifmedia_entry* ifm_cur; } ;
struct mii_data {int mii_media_active; TYPE_1__ mii_media; } ;
struct ifmedia_entry {int ifm_media; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  EJUSTRETURN ; 
 scalar_t__ IFM_10_T ; 
 int const IFM_ETHER ; 
#define  IFM_HPNA_1 131 
 scalar_t__ IFM_SUBTYPE (int) ; 
#define  MII_MEDIACHG 130 
#define  MII_POLLSTAT 129 
#define  MII_TICK 128 
 int /*<<< orphan*/  PHY_STATUS (struct mii_softc*) ; 
 int /*<<< orphan*/  mii_phy_setmedia (struct mii_softc*) ; 
 int /*<<< orphan*/  mii_phy_tick (struct mii_softc*) ; 
 int /*<<< orphan*/  mii_phy_update (struct mii_softc*,int) ; 

__attribute__((used)) static int
pnaphy_service(struct mii_softc *sc, struct mii_data *mii, int cmd)
{
	struct ifmedia_entry *ife = mii->mii_media.ifm_cur;

	switch (cmd) {
	case MII_POLLSTAT:
		break;

	case MII_MEDIACHG:
		switch (IFM_SUBTYPE(ife->ifm_media)) {
		case IFM_HPNA_1:
			mii_phy_setmedia(sc);
			break;
		default:
			return (EINVAL);
		}
		break;

	case MII_TICK:
		if (mii_phy_tick(sc) == EJUSTRETURN)
			return (0);
		break;
	}

	/* Update the media status. */
	PHY_STATUS(sc);
	if (IFM_SUBTYPE(mii->mii_media_active) == IFM_10_T)
		mii->mii_media_active = IFM_ETHER | IFM_HPNA_1;

	/* Callback if something changed. */
	mii_phy_update(sc, cmd);
	return (0);
}