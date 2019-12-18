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
typedef  int uint32_t ;
struct xae_softc {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BMCR_AUTOEN ; 
 int BMCR_FDX ; 
 int BMCR_RESET ; 
 int BMCR_SPEED1 ; 
 int BMCR_STARTNEG ; 
 int BMSR_ACOMP ; 
 int CFG2_INTERRUPT_POLARITY ; 
 int CFG2_SPEED_OPT_10M_EN ; 
 int CFG2_SPEED_OPT_ATTEMPT_CNT_4 ; 
 int CFG2_SPEED_OPT_ATTEMPT_CNT_M ; 
 int CFG2_SPEED_OPT_ENHANCED_EN ; 
 int /*<<< orphan*/  CFG4_SGMII_TMR ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  DP83867_CFG2 ; 
 int /*<<< orphan*/  DP83867_CFG4 ; 
 int /*<<< orphan*/  DP83867_PHYCR ; 
 int /*<<< orphan*/  DP83867_SGMIICTL1 ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int /*<<< orphan*/  MII_BMSR ; 
 int PHY1_RD (struct xae_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHY1_WR (struct xae_softc*,int /*<<< orphan*/ ,int) ; 
 int PHYCR_SGMII_EN ; 
 int PHY_RD (struct xae_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHY_WR (struct xae_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SGMIICTL1_SGMII_6W ; 
 int /*<<< orphan*/  WRITE_TI_EREG (struct xae_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
xae_phy_fixup(struct xae_softc *sc)
{
	uint32_t reg;
	device_t dev;

	dev = sc->dev;

	do {
		WRITE_TI_EREG(sc, DP83867_SGMIICTL1, SGMIICTL1_SGMII_6W);
		PHY_WR(sc, DP83867_PHYCR, PHYCR_SGMII_EN);

		reg = PHY_RD(sc, DP83867_CFG2);
		reg &= ~CFG2_SPEED_OPT_ATTEMPT_CNT_M;
		reg |= (CFG2_SPEED_OPT_ATTEMPT_CNT_4);
		reg |= CFG2_INTERRUPT_POLARITY;
		reg |= CFG2_SPEED_OPT_ENHANCED_EN;
		reg |= CFG2_SPEED_OPT_10M_EN;
		PHY_WR(sc, DP83867_CFG2, reg);

		WRITE_TI_EREG(sc, DP83867_CFG4, CFG4_SGMII_TMR);
		PHY_WR(sc, MII_BMCR,
		    BMCR_AUTOEN | BMCR_FDX | BMCR_SPEED1 | BMCR_RESET);
	} while (PHY1_RD(sc, MII_BMCR) == 0x0ffff);

	do {
		PHY1_WR(sc, MII_BMCR,
		    BMCR_AUTOEN | BMCR_FDX | BMCR_SPEED1 | BMCR_STARTNEG);
		DELAY(40000);
	} while ((PHY1_RD(sc, MII_BMSR) & BMSR_ACOMP) == 0);
}