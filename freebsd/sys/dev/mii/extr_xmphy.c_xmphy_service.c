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
struct mii_softc {int /*<<< orphan*/  mii_ticks; int /*<<< orphan*/  mii_anegticks; } ;
struct TYPE_2__ {struct ifmedia_entry* ifm_cur; } ;
struct mii_data {TYPE_1__ mii_media; } ;
struct ifmedia_entry {int ifm_media; } ;

/* Variables and functions */
 int BMSR_LINK ; 
 int EINVAL ; 
#define  IFM_1000_SX 132 
#define  IFM_AUTO 131 
 int IFM_FDX ; 
 int const IFM_SUBTYPE (int) ; 
 int /*<<< orphan*/  MII_BMSR ; 
#define  MII_MEDIACHG 130 
#define  MII_POLLSTAT 129 
#define  MII_TICK 128 
 int PHY_READ (struct mii_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHY_RESET (struct mii_softc*) ; 
 int /*<<< orphan*/  PHY_WRITE (struct mii_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XMPHY_ANAR_FDX ; 
 int /*<<< orphan*/  XMPHY_ANAR_HDX ; 
 int XMPHY_BMCR_AUTOEN ; 
 int /*<<< orphan*/  XMPHY_BMCR_FDX ; 
 int /*<<< orphan*/  XMPHY_MII_ANAR ; 
 int /*<<< orphan*/  XMPHY_MII_BMCR ; 
 int /*<<< orphan*/  mii_phy_update (struct mii_softc*,int) ; 
 int /*<<< orphan*/  xmphy_mii_phy_auto (struct mii_softc*) ; 
 int /*<<< orphan*/  xmphy_status (struct mii_softc*) ; 

__attribute__((used)) static int
xmphy_service(struct mii_softc *sc, struct mii_data *mii, int cmd)
{
	struct ifmedia_entry *ife = mii->mii_media.ifm_cur;
	int reg;

	switch (cmd) {
	case MII_POLLSTAT:
		break;

	case MII_MEDIACHG:
		switch (IFM_SUBTYPE(ife->ifm_media)) {
		case IFM_AUTO:
#ifdef foo
			/*
			 * If we're already in auto mode, just return.
			 */
			if (PHY_READ(sc, XMPHY_MII_BMCR) & XMPHY_BMCR_AUTOEN)
				return (0);
#endif
			(void)xmphy_mii_phy_auto(sc);
			break;
		case IFM_1000_SX:
			PHY_RESET(sc);
			if ((ife->ifm_media & IFM_FDX) != 0) {
				PHY_WRITE(sc, XMPHY_MII_ANAR, XMPHY_ANAR_FDX);
				PHY_WRITE(sc, XMPHY_MII_BMCR, XMPHY_BMCR_FDX);
			} else {
				PHY_WRITE(sc, XMPHY_MII_ANAR, XMPHY_ANAR_HDX);
				PHY_WRITE(sc, XMPHY_MII_BMCR, 0);
			}
			break;
		default:
			return (EINVAL);
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
		 */
		reg = PHY_READ(sc, MII_BMSR) | PHY_READ(sc, MII_BMSR);
		if (reg & BMSR_LINK)
			break;

		/* Only retry autonegotiation every mii_anegticks seconds. */
		if (sc->mii_ticks <= sc->mii_anegticks)
			break;

		sc->mii_ticks = 0;

		PHY_RESET(sc);
		xmphy_mii_phy_auto(sc);
		return (0);
	}

	/* Update the media status. */
	xmphy_status(sc);

	/* Callback if something changed. */
	mii_phy_update(sc, cmd);
	return (0);
}