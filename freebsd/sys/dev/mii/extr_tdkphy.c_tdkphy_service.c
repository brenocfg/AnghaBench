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
struct mii_softc {TYPE_1__* mii_pdata; } ;
struct mii_data {int dummy; } ;
struct TYPE_2__ {int mii_media_active; } ;

/* Variables and functions */
 int BMCR_FDX ; 
 int /*<<< orphan*/  EJUSTRETURN ; 
 int IFM_FDX ; 
 int /*<<< orphan*/  MII_BMCR ; 
#define  MII_MEDIACHG 130 
#define  MII_POLLSTAT 129 
#define  MII_TICK 128 
 int PHY_READ (struct mii_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHY_STATUS (struct mii_softc*) ; 
 int /*<<< orphan*/  PHY_WRITE (struct mii_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mii_phy_setmedia (struct mii_softc*) ; 
 int /*<<< orphan*/  mii_phy_tick (struct mii_softc*) ; 
 int /*<<< orphan*/  mii_phy_update (struct mii_softc*,int) ; 

__attribute__((used)) static int
tdkphy_service(struct mii_softc *sc, struct mii_data *mii, int cmd)
{

	switch (cmd) {
	case MII_POLLSTAT:
		break;

	case MII_MEDIACHG:
		mii_phy_setmedia(sc);
		break;

	case MII_TICK:
		if (mii_phy_tick(sc) == EJUSTRETURN)
			return (0);
		break;
	}

	/* Update the media status. */
	PHY_STATUS(sc);
	if (sc->mii_pdata->mii_media_active & IFM_FDX)
		PHY_WRITE(sc, MII_BMCR, PHY_READ(sc, MII_BMCR) | BMCR_FDX);
	else
		PHY_WRITE(sc, MII_BMCR, PHY_READ(sc, MII_BMCR) & ~BMCR_FDX);

	/* Callback if something changed. */
	mii_phy_update(sc, cmd);
	return (0);
}