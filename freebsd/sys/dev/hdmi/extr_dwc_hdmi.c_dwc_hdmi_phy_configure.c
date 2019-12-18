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
typedef  int uint8_t ;
struct TYPE_2__ {int dot_clock; } ;
struct dwc_hdmi_softc {int /*<<< orphan*/  sc_dev; TYPE_1__ sc_mode; } ;

/* Variables and functions */
 int CKCALCTRL_OVERRIDE ; 
 int CKSYMTXCTRL_OVERRIDE ; 
 int CKSYMTXCTRL_TX_CK_SYMON ; 
 int CKSYMTXCTRL_TX_SYMON ; 
 int CKSYMTXCTRL_TX_TRAON ; 
 int CKSYMTXCTRL_TX_TRBON ; 
 int CPCE_CTRL_185 ; 
 int CPCE_CTRL_370 ; 
 int CPCE_CTRL_45_25 ; 
 int CPCE_CTRL_92_50 ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int GMPCTRL_185 ; 
 int GMPCTRL_370 ; 
 int GMPCTRL_45_25 ; 
 int GMPCTRL_92_50 ; 
 int /*<<< orphan*/  HDMI_MC_FLOWCTRL ; 
 int /*<<< orphan*/  HDMI_MC_FLOWCTRL_FEED_THROUGH_OFF_CSC_BYPASS ; 
 int /*<<< orphan*/  HDMI_MC_HEACPHY_RST ; 
 int /*<<< orphan*/  HDMI_MC_HEACPHY_RST_ASSERT ; 
 int /*<<< orphan*/  HDMI_MC_PHYRSTZ ; 
 int /*<<< orphan*/  HDMI_MC_PHYRSTZ_ASSERT ; 
 int /*<<< orphan*/  HDMI_MC_PHYRSTZ_DEASSERT ; 
 int /*<<< orphan*/  HDMI_PHY_I2CM_SLAVE_ADDR ; 
 int /*<<< orphan*/  HDMI_PHY_I2CM_SLAVE_ADDR_PHY_GEN2 ; 
 int /*<<< orphan*/  HDMI_PHY_I2C_CKCALCTRL ; 
 int /*<<< orphan*/  HDMI_PHY_I2C_CKSYMTXCTRL ; 
 int /*<<< orphan*/  HDMI_PHY_I2C_CPCE_CTRL ; 
 int /*<<< orphan*/  HDMI_PHY_I2C_CURRCTRL ; 
 int /*<<< orphan*/  HDMI_PHY_I2C_GMPCTRL ; 
 int /*<<< orphan*/  HDMI_PHY_I2C_MSM_CTRL ; 
 int /*<<< orphan*/  HDMI_PHY_I2C_PLLPHBYCTRL ; 
 int /*<<< orphan*/  HDMI_PHY_I2C_TXTERM ; 
 int /*<<< orphan*/  HDMI_PHY_I2C_VLEVCTRL ; 
 int /*<<< orphan*/  HDMI_PHY_STAT0 ; 
 int HDMI_PHY_TX_PHY_LOCK ; 
 int MSM_CTRL_FB_CLK ; 
 int RD1 (struct dwc_hdmi_softc*,int /*<<< orphan*/ ) ; 
 int TXTERM_133 ; 
 int VLEVCTRL_CK_LVL (int) ; 
 int VLEVCTRL_TX_LVL (int) ; 
 int /*<<< orphan*/  WR1 (struct dwc_hdmi_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dwc_hdmi_phy_enable_power (struct dwc_hdmi_softc*,int) ; 
 int /*<<< orphan*/  dwc_hdmi_phy_enable_tmds (struct dwc_hdmi_softc*,int) ; 
 int /*<<< orphan*/  dwc_hdmi_phy_gen2_pddq (struct dwc_hdmi_softc*,int) ; 
 int /*<<< orphan*/  dwc_hdmi_phy_gen2_txpwron (struct dwc_hdmi_softc*,int) ; 
 int /*<<< orphan*/  dwc_hdmi_phy_i2c_write (struct dwc_hdmi_softc*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc_hdmi_phy_test_clear (struct dwc_hdmi_softc*,int) ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static int
dwc_hdmi_phy_configure(struct dwc_hdmi_softc *sc)
{
	uint8_t val;
	uint8_t msec;

	WR1(sc, HDMI_MC_FLOWCTRL, HDMI_MC_FLOWCTRL_FEED_THROUGH_OFF_CSC_BYPASS);

	/* gen2 tx power off */
	dwc_hdmi_phy_gen2_txpwron(sc, 0);

	/* gen2 pddq */
	dwc_hdmi_phy_gen2_pddq(sc, 1);

	/* PHY reset */
	WR1(sc, HDMI_MC_PHYRSTZ, HDMI_MC_PHYRSTZ_DEASSERT);
	WR1(sc, HDMI_MC_PHYRSTZ, HDMI_MC_PHYRSTZ_ASSERT);

	WR1(sc, HDMI_MC_HEACPHY_RST, HDMI_MC_HEACPHY_RST_ASSERT);

	dwc_hdmi_phy_test_clear(sc, 1);
	WR1(sc, HDMI_PHY_I2CM_SLAVE_ADDR, HDMI_PHY_I2CM_SLAVE_ADDR_PHY_GEN2);
	dwc_hdmi_phy_test_clear(sc, 0);

	/*
	 * Following initialization are for 8bit per color case
	 */

	/*
	 * PLL/MPLL config, see section 24.7.22 in TRM
	 *  config, see section 24.7.22
	 */
	if (sc->sc_mode.dot_clock*1000 <= 45250000) {
		dwc_hdmi_phy_i2c_write(sc, CPCE_CTRL_45_25, HDMI_PHY_I2C_CPCE_CTRL);
		dwc_hdmi_phy_i2c_write(sc, GMPCTRL_45_25, HDMI_PHY_I2C_GMPCTRL);
	} else if (sc->sc_mode.dot_clock*1000 <= 92500000) {
		dwc_hdmi_phy_i2c_write(sc, CPCE_CTRL_92_50, HDMI_PHY_I2C_CPCE_CTRL);
		dwc_hdmi_phy_i2c_write(sc, GMPCTRL_92_50, HDMI_PHY_I2C_GMPCTRL);
	} else if (sc->sc_mode.dot_clock*1000 <= 185000000) {
		dwc_hdmi_phy_i2c_write(sc, CPCE_CTRL_185, HDMI_PHY_I2C_CPCE_CTRL);
		dwc_hdmi_phy_i2c_write(sc, GMPCTRL_185, HDMI_PHY_I2C_GMPCTRL);
	} else {
		dwc_hdmi_phy_i2c_write(sc, CPCE_CTRL_370, HDMI_PHY_I2C_CPCE_CTRL);
		dwc_hdmi_phy_i2c_write(sc, GMPCTRL_370, HDMI_PHY_I2C_GMPCTRL);
	}

	/*
	 * Values described in TRM section 34.9.2 PLL/MPLL Generic
	 *    Configuration Settings. Table 34-23.
	 */
	if (sc->sc_mode.dot_clock*1000 <= 54000000) {
		dwc_hdmi_phy_i2c_write(sc, 0x091c, HDMI_PHY_I2C_CURRCTRL);
	} else if (sc->sc_mode.dot_clock*1000 <= 58400000) {
		dwc_hdmi_phy_i2c_write(sc, 0x091c, HDMI_PHY_I2C_CURRCTRL);
	} else if (sc->sc_mode.dot_clock*1000 <= 72000000) {
		dwc_hdmi_phy_i2c_write(sc, 0x06dc, HDMI_PHY_I2C_CURRCTRL);
	} else if (sc->sc_mode.dot_clock*1000 <= 74250000) {
		dwc_hdmi_phy_i2c_write(sc, 0x06dc, HDMI_PHY_I2C_CURRCTRL);
	} else if (sc->sc_mode.dot_clock*1000 <= 118800000) {
		dwc_hdmi_phy_i2c_write(sc, 0x091c, HDMI_PHY_I2C_CURRCTRL);
	} else if (sc->sc_mode.dot_clock*1000 <= 216000000) {
		dwc_hdmi_phy_i2c_write(sc, 0x06dc, HDMI_PHY_I2C_CURRCTRL);
	} else {
		panic("Unsupported mode\n");
	}

	dwc_hdmi_phy_i2c_write(sc, 0x0000, HDMI_PHY_I2C_PLLPHBYCTRL);
	dwc_hdmi_phy_i2c_write(sc, MSM_CTRL_FB_CLK, HDMI_PHY_I2C_MSM_CTRL);
	/* RESISTANCE TERM 133 Ohm */
	dwc_hdmi_phy_i2c_write(sc, TXTERM_133, HDMI_PHY_I2C_TXTERM);

	/* REMOVE CLK TERM */
	dwc_hdmi_phy_i2c_write(sc, CKCALCTRL_OVERRIDE, HDMI_PHY_I2C_CKCALCTRL);

	if (sc->sc_mode.dot_clock*1000 > 148500000) {
		dwc_hdmi_phy_i2c_write(sc,CKSYMTXCTRL_OVERRIDE | CKSYMTXCTRL_TX_SYMON |
		    CKSYMTXCTRL_TX_TRBON | CKSYMTXCTRL_TX_CK_SYMON, HDMI_PHY_I2C_CKSYMTXCTRL); 
		dwc_hdmi_phy_i2c_write(sc, VLEVCTRL_TX_LVL(9) | VLEVCTRL_CK_LVL(9),
		    HDMI_PHY_I2C_VLEVCTRL);
	} else {
		dwc_hdmi_phy_i2c_write(sc,CKSYMTXCTRL_OVERRIDE | CKSYMTXCTRL_TX_SYMON |
		    CKSYMTXCTRL_TX_TRAON | CKSYMTXCTRL_TX_CK_SYMON, HDMI_PHY_I2C_CKSYMTXCTRL); 
		dwc_hdmi_phy_i2c_write(sc, VLEVCTRL_TX_LVL(13) | VLEVCTRL_CK_LVL(13),
		    HDMI_PHY_I2C_VLEVCTRL);
	}

	dwc_hdmi_phy_enable_power(sc, 1);

	/* toggle TMDS enable */
	dwc_hdmi_phy_enable_tmds(sc, 0);
	dwc_hdmi_phy_enable_tmds(sc, 1);

	/* gen2 tx power on */
	dwc_hdmi_phy_gen2_txpwron(sc, 1);
	dwc_hdmi_phy_gen2_pddq(sc, 0);

	/*Wait for PHY PLL lock */
	msec = 4;
	val = RD1(sc, HDMI_PHY_STAT0) & HDMI_PHY_TX_PHY_LOCK;
	while (val == 0) {
		DELAY(1000);
		if (msec-- == 0) {
			device_printf(sc->sc_dev, "PHY PLL not locked\n");
			return (-1);
		}
		val = RD1(sc, HDMI_PHY_STAT0) & HDMI_PHY_TX_PHY_LOCK;
	}

	return true;
}