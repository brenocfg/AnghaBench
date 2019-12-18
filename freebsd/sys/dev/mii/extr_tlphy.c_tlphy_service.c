#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  mii_ticks; } ;
struct tlphy_softc {TYPE_2__ sc_mii; scalar_t__ sc_need_acomp; } ;
struct mii_softc {int dummy; } ;
struct TYPE_7__ {struct ifmedia_entry* ifm_cur; } ;
struct mii_data {TYPE_1__ mii_media; } ;
struct ifmedia_entry {int /*<<< orphan*/  ifm_media; } ;

/* Variables and functions */
 int BMSR_LINK ; 
 int /*<<< orphan*/  CTRL_AUISEL ; 
 int /*<<< orphan*/  DELAY (int) ; 
#define  IFM_10_2 133 
#define  IFM_10_5 132 
#define  IFM_AUTO 131 
 int const IFM_SUBTYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MII_ANEGTICKS ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int /*<<< orphan*/  MII_BMSR ; 
#define  MII_MEDIACHG 130 
#define  MII_POLLSTAT 129 
#define  MII_TICK 128 
 int /*<<< orphan*/  MII_TLPHY_CTRL ; 
 int PHY_READ (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHY_RESET (TYPE_2__*) ; 
 int /*<<< orphan*/  PHY_STATUS (struct mii_softc*) ; 
 int /*<<< orphan*/  PHY_WRITE (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mii_phy_setmedia (TYPE_2__*) ; 
 int /*<<< orphan*/  mii_phy_update (TYPE_2__*,int) ; 
 int /*<<< orphan*/  tlphy_acomp (struct tlphy_softc*) ; 
 int /*<<< orphan*/  tlphy_auto (struct tlphy_softc*) ; 

__attribute__((used)) static int
tlphy_service(struct mii_softc *self, struct mii_data *mii, int cmd)
{
	struct tlphy_softc *sc = (struct tlphy_softc *)self;
	struct ifmedia_entry *ife = mii->mii_media.ifm_cur;
	int reg;

	if (sc->sc_need_acomp)
		tlphy_acomp(sc);

	switch (cmd) {
	case MII_POLLSTAT:
		break;

	case MII_MEDIACHG:
		switch (IFM_SUBTYPE(ife->ifm_media)) {
		case IFM_AUTO:
			/*
			 * The ThunderLAN PHY doesn't self-configure after
			 * an autonegotiation cycle, so there's no such
			 * thing as "already in auto mode".
			 */
			(void)tlphy_auto(sc);
			break;
		case IFM_10_2:
		case IFM_10_5:
			PHY_WRITE(&sc->sc_mii, MII_BMCR, 0);
			PHY_WRITE(&sc->sc_mii, MII_TLPHY_CTRL, CTRL_AUISEL);
			DELAY(100000);
			break;
		default:
			PHY_WRITE(&sc->sc_mii, MII_TLPHY_CTRL, 0);
			DELAY(100000);
			mii_phy_setmedia(&sc->sc_mii);
		}
		break;

	case MII_TICK:
		/*
		 * Only used for autonegotiation.
		 */
		if (IFM_SUBTYPE(ife->ifm_media) != IFM_AUTO)
			break;

		/*
		 * Check to see if we have link.  If we do, we don't
		 * need to restart the autonegotiation process.  Read
		 * the BMSR twice in case it's latched.
		 *
		 * XXX WHAT ABOUT CHECKING LINK ON THE BNC/AUI?!
		 */
		reg = PHY_READ(&sc->sc_mii, MII_BMSR) |
		    PHY_READ(&sc->sc_mii, MII_BMSR);
		if (reg & BMSR_LINK)
			break;

		/*
		 * Only retry autonegotiation every 5 seconds.
		 */
		if (++sc->sc_mii.mii_ticks <= MII_ANEGTICKS)
			break;

		sc->sc_mii.mii_ticks = 0;
		PHY_RESET(&sc->sc_mii);
		(void)tlphy_auto(sc);
		return (0);
	}

	/* Update the media status. */
	PHY_STATUS(self);

	/* Callback if something changed. */
	mii_phy_update(&sc->sc_mii, cmd);
	return (0);
}