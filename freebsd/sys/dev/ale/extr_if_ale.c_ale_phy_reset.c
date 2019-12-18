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
struct ale_softc {int /*<<< orphan*/  ale_phyaddr; int /*<<< orphan*/  ale_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALE_GPHY_CTRL ; 
 int /*<<< orphan*/  ATPHY_DBG_ADDR ; 
 int /*<<< orphan*/  ATPHY_DBG_DATA ; 
 int /*<<< orphan*/  CSR_WRITE_2 (struct ale_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int GPHY_CTRL_EXT_RESET ; 
 int GPHY_CTRL_HIB_EN ; 
 int GPHY_CTRL_HIB_PULSE ; 
 int GPHY_CTRL_PHY_PLL_ON ; 
 int GPHY_CTRL_SEL_ANA_RESET ; 
 int /*<<< orphan*/  ale_miibus_writereg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ale_phy_reset(struct ale_softc *sc)
{

	/* Reset magic from Linux. */
	CSR_WRITE_2(sc, ALE_GPHY_CTRL,
	    GPHY_CTRL_HIB_EN | GPHY_CTRL_HIB_PULSE | GPHY_CTRL_SEL_ANA_RESET |
	    GPHY_CTRL_PHY_PLL_ON);
	DELAY(1000);
	CSR_WRITE_2(sc, ALE_GPHY_CTRL,
	    GPHY_CTRL_EXT_RESET | GPHY_CTRL_HIB_EN | GPHY_CTRL_HIB_PULSE |
	    GPHY_CTRL_SEL_ANA_RESET | GPHY_CTRL_PHY_PLL_ON);
	DELAY(1000);

#define	ATPHY_DBG_ADDR		0x1D
#define	ATPHY_DBG_DATA		0x1E

	/* Enable hibernation mode. */
	ale_miibus_writereg(sc->ale_dev, sc->ale_phyaddr,
	    ATPHY_DBG_ADDR, 0x0B);
	ale_miibus_writereg(sc->ale_dev, sc->ale_phyaddr,
	    ATPHY_DBG_DATA, 0xBC00);
	/* Set Class A/B for all modes. */
	ale_miibus_writereg(sc->ale_dev, sc->ale_phyaddr,
	    ATPHY_DBG_ADDR, 0x00);
	ale_miibus_writereg(sc->ale_dev, sc->ale_phyaddr,
	    ATPHY_DBG_DATA, 0x02EF);
	/* Enable 10BT power saving. */
	ale_miibus_writereg(sc->ale_dev, sc->ale_phyaddr,
	    ATPHY_DBG_ADDR, 0x12);
	ale_miibus_writereg(sc->ale_dev, sc->ale_phyaddr,
	    ATPHY_DBG_DATA, 0x4C04);
	/* Adjust 1000T power. */
	ale_miibus_writereg(sc->ale_dev, sc->ale_phyaddr,
	    ATPHY_DBG_ADDR, 0x04);
	ale_miibus_writereg(sc->ale_dev, sc->ale_phyaddr,
	    ATPHY_DBG_ADDR, 0x8BBB);
	/* 10BT center tap voltage. */
	ale_miibus_writereg(sc->ale_dev, sc->ale_phyaddr,
	    ATPHY_DBG_ADDR, 0x05);
	ale_miibus_writereg(sc->ale_dev, sc->ale_phyaddr,
	    ATPHY_DBG_ADDR, 0x2C46);

#undef	ATPHY_DBG_ADDR
#undef	ATPHY_DBG_DATA
	DELAY(1000);
}