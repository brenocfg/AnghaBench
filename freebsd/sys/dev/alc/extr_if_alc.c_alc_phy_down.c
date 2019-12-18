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
typedef  int uint32_t ;
struct alc_softc {int /*<<< orphan*/  alc_phyaddr; int /*<<< orphan*/  alc_dev; TYPE_1__* alc_ident; } ;
struct TYPE_2__ {int deviceid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALC_GPHY_CFG ; 
 int BMCR_ISO ; 
 int BMCR_PDOWN ; 
 int CSR_READ_4 (struct alc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_2 (struct alc_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct alc_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
#define  DEVICEID_ATHEROS_AR8151 138 
#define  DEVICEID_ATHEROS_AR8151_V2 137 
#define  DEVICEID_ATHEROS_AR8152_B 136 
#define  DEVICEID_ATHEROS_AR8152_B2 135 
#define  DEVICEID_ATHEROS_AR8161 134 
#define  DEVICEID_ATHEROS_AR8162 133 
#define  DEVICEID_ATHEROS_AR8171 132 
#define  DEVICEID_ATHEROS_AR8172 131 
#define  DEVICEID_ATHEROS_E2200 130 
#define  DEVICEID_ATHEROS_E2400 129 
#define  DEVICEID_ATHEROS_E2500 128 
 int GPHY_CFG_100AB_ENB ; 
 int GPHY_CFG_EXT_RESET ; 
 int GPHY_CFG_HIB_EN ; 
 int GPHY_CFG_HIB_PULSE ; 
 int GPHY_CFG_LED_MODE ; 
 int GPHY_CFG_PHY_IDDQ ; 
 int GPHY_CFG_PHY_PLL_ON ; 
 int GPHY_CFG_PWDOWN_HW ; 
 int GPHY_CFG_SEL_ANA_RESET ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int /*<<< orphan*/  alc_miibus_writereg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
alc_phy_down(struct alc_softc *sc)
{
	uint32_t gphy;

	switch (sc->alc_ident->deviceid) {
	case DEVICEID_ATHEROS_AR8161:
	case DEVICEID_ATHEROS_E2200:
	case DEVICEID_ATHEROS_E2400:
	case DEVICEID_ATHEROS_E2500:
	case DEVICEID_ATHEROS_AR8162:
	case DEVICEID_ATHEROS_AR8171:
	case DEVICEID_ATHEROS_AR8172:
		gphy = CSR_READ_4(sc, ALC_GPHY_CFG);
		gphy &= ~(GPHY_CFG_EXT_RESET | GPHY_CFG_LED_MODE |
		    GPHY_CFG_100AB_ENB | GPHY_CFG_PHY_PLL_ON);
		gphy |= GPHY_CFG_HIB_EN | GPHY_CFG_HIB_PULSE |
		    GPHY_CFG_SEL_ANA_RESET;
		gphy |= GPHY_CFG_PHY_IDDQ | GPHY_CFG_PWDOWN_HW;
		CSR_WRITE_4(sc, ALC_GPHY_CFG, gphy);
		break;
	case DEVICEID_ATHEROS_AR8151:
	case DEVICEID_ATHEROS_AR8151_V2:
	case DEVICEID_ATHEROS_AR8152_B:
	case DEVICEID_ATHEROS_AR8152_B2:
		/*
		 * GPHY power down caused more problems on AR8151 v2.0.
		 * When driver is reloaded after GPHY power down,
		 * accesses to PHY/MAC registers hung the system. Only
		 * cold boot recovered from it.  I'm not sure whether
		 * AR8151 v1.0 also requires this one though.  I don't
		 * have AR8151 v1.0 controller in hand.
		 * The only option left is to isolate the PHY and
		 * initiates power down the PHY which in turn saves
		 * more power when driver is unloaded.
		 */
		alc_miibus_writereg(sc->alc_dev, sc->alc_phyaddr,
		    MII_BMCR, BMCR_ISO | BMCR_PDOWN);
		break;
	default:
		/* Force PHY down. */
		CSR_WRITE_2(sc, ALC_GPHY_CFG, GPHY_CFG_EXT_RESET |
		    GPHY_CFG_SEL_ANA_RESET | GPHY_CFG_PHY_IDDQ |
		    GPHY_CFG_PWDOWN_HW);
		DELAY(1000);
		break;
	}
}