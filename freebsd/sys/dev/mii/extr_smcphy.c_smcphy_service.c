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
struct mii_softc {int /*<<< orphan*/  mii_ticks; } ;
struct TYPE_2__ {struct ifmedia_entry* ifm_cur; } ;
struct mii_data {TYPE_1__ mii_media; } ;
struct ifmedia_entry {int /*<<< orphan*/  ifm_media; } ;

/* Variables and functions */
 int BMCR_ISO ; 
 int BMSR_LINK ; 
#define  IFM_AUTO 131 
 int const IFM_SUBTYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MII_ANEGTICKS ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int /*<<< orphan*/  MII_BMSR ; 
#define  MII_MEDIACHG 130 
#define  MII_POLLSTAT 129 
#define  MII_TICK 128 
 int PHY_READ (struct mii_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHY_RESET (struct mii_softc*) ; 
 int /*<<< orphan*/  PHY_STATUS (struct mii_softc*) ; 
 int /*<<< orphan*/  PHY_WRITE (struct mii_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mii_phy_setmedia (struct mii_softc*) ; 
 int /*<<< orphan*/  mii_phy_update (struct mii_softc*,int) ; 
 int /*<<< orphan*/  smcphy_auto (struct mii_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
smcphy_service(struct mii_softc *sc, struct mii_data *mii, int cmd)
{
        struct	ifmedia_entry *ife;
        int	reg;

	ife = mii->mii_media.ifm_cur;

        switch (cmd) {
        case MII_POLLSTAT:
                break;

        case MII_MEDIACHG:
		switch (IFM_SUBTYPE(ife->ifm_media)) {
		case IFM_AUTO:
			smcphy_auto(sc, ife->ifm_media);
			break;

		default:
                	mii_phy_setmedia(sc);
			break;
		}

                break;

        case MII_TICK:
		if (IFM_SUBTYPE(ife->ifm_media) != IFM_AUTO) {
			break;
		}

		/* I have no idea why BMCR_ISO gets set. */
		reg = PHY_READ(sc, MII_BMCR);
		if (reg & BMCR_ISO) {
			PHY_WRITE(sc, MII_BMCR, reg & ~BMCR_ISO);
		}

		reg = PHY_READ(sc, MII_BMSR) | PHY_READ(sc, MII_BMSR);
		if (reg & BMSR_LINK) {
			sc->mii_ticks = 0;
			break;
		}

		if (++sc->mii_ticks <= MII_ANEGTICKS) {
			break;
		}

		sc->mii_ticks = 0;
		PHY_RESET(sc);
		smcphy_auto(sc, ife->ifm_media);
                break;
        }

        /* Update the media status. */
        PHY_STATUS(sc);

        /* Callback if something changed. */
        mii_phy_update(sc, cmd);
        return (0);
}