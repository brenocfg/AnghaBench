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
typedef  int uint16_t ;
struct mii_softc {int mii_flags; } ;
struct ifmedia_entry {int ifm_media; } ;

/* Variables and functions */
 int ANAR_CSMA ; 
 int ANAR_PAUSE_TOWARDS ; 
 int BMCR_AUTOEN ; 
 int BMCR_ISO ; 
 int BMCR_PDOWN ; 
 int BMCR_STARTNEG ; 
 int EINVAL ; 
 int EJUSTRETURN ; 
 int GTCR_ADV_1000TFDX ; 
 int GTCR_ADV_1000THDX ; 
 int GTCR_ADV_MS ; 
 int GTCR_MAN_MS ; 
#define  IFM_1000_T 132 
#define  IFM_100_TX 131 
#define  IFM_10_T 130 
#define  IFM_AUTO 129 
 int IFM_ETH_MASTER ; 
 int IFM_FDX ; 
 int IFM_FLOW ; 
#define  IFM_NONE 128 
 int const IFM_SUBTYPE (int) ; 
 int MIIF_FORCEPAUSE ; 
 int MIIF_HAVE_GTCR ; 
 int /*<<< orphan*/  MII_100T2CR ; 
 int /*<<< orphan*/  MII_ANAR ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int PHY_READ (struct mii_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHY_WRITE (struct mii_softc*,int /*<<< orphan*/ ,int) ; 
 int jmphy_anar (struct ifmedia_entry*) ; 

__attribute__((used)) static int
jmphy_setmedia(struct mii_softc *sc, struct ifmedia_entry *ife)
{
	uint16_t anar, bmcr, gig;

	gig = 0;
	bmcr = PHY_READ(sc, MII_BMCR);
	switch (IFM_SUBTYPE(ife->ifm_media)) {
	case IFM_AUTO:
		gig |= GTCR_ADV_1000TFDX | GTCR_ADV_1000THDX;
		break;
	case IFM_1000_T:
		gig |= GTCR_ADV_1000TFDX | GTCR_ADV_1000THDX;
		break;
	case IFM_100_TX:
	case IFM_10_T:
		break;
	case IFM_NONE:
		PHY_WRITE(sc, MII_BMCR, bmcr | BMCR_ISO | BMCR_PDOWN);
		return (EJUSTRETURN);
	default:
		return (EINVAL);
	}

	anar = jmphy_anar(ife);
	if ((IFM_SUBTYPE(ife->ifm_media) == IFM_AUTO ||
	    (ife->ifm_media & IFM_FDX) != 0) &&
	    ((ife->ifm_media & IFM_FLOW) != 0 ||
	    (sc->mii_flags & MIIF_FORCEPAUSE) != 0))
		anar |= ANAR_PAUSE_TOWARDS;

	if ((sc->mii_flags & MIIF_HAVE_GTCR) != 0) {
		if (IFM_SUBTYPE(ife->ifm_media) == IFM_1000_T) {
			gig |= GTCR_MAN_MS;
			if ((ife->ifm_media & IFM_ETH_MASTER) != 0)
				gig |= GTCR_ADV_MS;
		}
		PHY_WRITE(sc, MII_100T2CR, gig);
	}
	PHY_WRITE(sc, MII_ANAR, anar | ANAR_CSMA);
	PHY_WRITE(sc, MII_BMCR, bmcr | BMCR_AUTOEN | BMCR_STARTNEG);

	return (EJUSTRETURN);
}