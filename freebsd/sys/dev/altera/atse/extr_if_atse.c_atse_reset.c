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
typedef  int uint16_t ;
struct atse_softc {int /*<<< orphan*/  atse_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATSE_ETH_ADDR_ALL ; 
 int /*<<< orphan*/  BASE_CFG_COMMAND_CONFIG ; 
 int BASE_CFG_COMMAND_CONFIG_CNTL_FRM_ENA ; 
 int BASE_CFG_COMMAND_CONFIG_CRC_FWD ; 
 int BASE_CFG_COMMAND_CONFIG_ENA_10 ; 
 int BASE_CFG_COMMAND_CONFIG_ETH_SPEED ; 
 int BASE_CFG_COMMAND_CONFIG_LOOP_ENA ; 
 int BASE_CFG_COMMAND_CONFIG_PAD_EN ; 
 int BASE_CFG_COMMAND_CONFIG_RX_ENA ; 
 int BASE_CFG_COMMAND_CONFIG_RX_ERR_DISC ; 
 int BASE_CFG_COMMAND_CONFIG_SW_RESET ; 
 int BASE_CFG_COMMAND_CONFIG_TX_ADDR_INS ; 
 int BASE_CFG_COMMAND_CONFIG_TX_ENA ; 
 int /*<<< orphan*/  BASE_CFG_FRM_LENGTH ; 
 int /*<<< orphan*/  BASE_CFG_PAUSE_QUANT ; 
 int /*<<< orphan*/  BASE_CFG_RX_ALMOST_EMPTY ; 
 int /*<<< orphan*/  BASE_CFG_RX_ALMOST_FULL ; 
 int /*<<< orphan*/  BASE_CFG_RX_SECTION_EMPTY ; 
 int /*<<< orphan*/  BASE_CFG_RX_SECTION_FULL ; 
 int /*<<< orphan*/  BASE_CFG_TX_ALMOST_EMPTY ; 
 int /*<<< orphan*/  BASE_CFG_TX_ALMOST_FULL ; 
 int /*<<< orphan*/  BASE_CFG_TX_IPG_LENGTH ; 
 int /*<<< orphan*/  BASE_CFG_TX_SECTION_EMPTY ; 
 int /*<<< orphan*/  BASE_CFG_TX_SECTION_FULL ; 
 int CSR_READ_4 (struct atse_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct atse_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int ENXIO ; 
 int FIFO_DEPTH_RX ; 
 int FIFO_DEPTH_TX ; 
 int /*<<< orphan*/  PCS_CONTROL ; 
 int PCS_CONTROL_AUTO_NEGOTIATION_ENABLE ; 
 int PCS_CONTROL_ISOLATE ; 
 int PCS_CONTROL_LOOPBACK ; 
 int PCS_CONTROL_POWERDOWN ; 
 int PCS_CONTROL_RESET ; 
 int /*<<< orphan*/  PCS_EXT_IF_MODE ; 
 int PCS_EXT_IF_MODE_SGMII_ENA ; 
 int PCS_EXT_IF_MODE_USE_SGMII_AN ; 
 int /*<<< orphan*/  PCS_EXT_LINK_TIMER_0 ; 
 int /*<<< orphan*/  PCS_EXT_LINK_TIMER_1 ; 
 int PCS_READ_2 (struct atse_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCS_WRITE_2 (struct atse_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RX_CMD_STAT ; 
 int RX_CMD_STAT_RX_SHIFT16 ; 
 int /*<<< orphan*/  TX_CMD_STAT ; 
 int TX_CMD_STAT_OMIT_CRC ; 
 int TX_CMD_STAT_TX_SHIFT16 ; 
 int /*<<< orphan*/  atse_get_eth_address (struct atse_softc*) ; 
 int /*<<< orphan*/  atse_set_eth_address (struct atse_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
atse_reset(struct atse_softc *sc)
{
	uint32_t val4, mask;
	uint16_t val;
	int i;

	/* 1. External PHY Initialization using MDIO. */
	/*
	 * We select the right MDIO space in atse_attach() and let MII do
	 * anything else.
	 */

	/* 2. PCS Configuration Register Initialization. */
	/* a. Set auto negotiation link timer to 1.6ms for SGMII. */
	PCS_WRITE_2(sc, PCS_EXT_LINK_TIMER_0, 0x0D40);
	PCS_WRITE_2(sc, PCS_EXT_LINK_TIMER_1, 0x0003);

	/* b. Configure SGMII. */
	val = PCS_EXT_IF_MODE_SGMII_ENA|PCS_EXT_IF_MODE_USE_SGMII_AN;
	PCS_WRITE_2(sc, PCS_EXT_IF_MODE, val);

	/* c. Enable auto negotiation. */
	/* Ignore Bits 6,8,13; should be set,set,unset. */
	val = PCS_READ_2(sc, PCS_CONTROL);
	val &= ~(PCS_CONTROL_ISOLATE|PCS_CONTROL_POWERDOWN);
	val &= ~PCS_CONTROL_LOOPBACK;		/* Make this a -link1 option? */
	val |= PCS_CONTROL_AUTO_NEGOTIATION_ENABLE;
	PCS_WRITE_2(sc, PCS_CONTROL, val);

	/* d. PCS reset. */
	val = PCS_READ_2(sc, PCS_CONTROL);
	val |= PCS_CONTROL_RESET;
	PCS_WRITE_2(sc, PCS_CONTROL, val);

	/* Wait for reset bit to clear; i=100 is excessive. */
	for (i = 0; i < 100; i++) {
		val = PCS_READ_2(sc, PCS_CONTROL);
		if ((val & PCS_CONTROL_RESET) == 0) {
			break;
		}
		DELAY(10);
	}

	if ((val & PCS_CONTROL_RESET) != 0) {
		device_printf(sc->atse_dev, "PCS reset timed out.\n");
		return (ENXIO);
	}

	/* 3. MAC Configuration Register Initialization. */
	/* a. Disable MAC transmit and receive datapath. */
	mask = BASE_CFG_COMMAND_CONFIG_TX_ENA|BASE_CFG_COMMAND_CONFIG_RX_ENA;
	val4 = CSR_READ_4(sc, BASE_CFG_COMMAND_CONFIG);
	val4 &= ~mask;
	/* Samples in the manual do have the SW_RESET bit set here, why? */
	CSR_WRITE_4(sc, BASE_CFG_COMMAND_CONFIG, val4);
	/* Wait for bits to be cleared; i=100 is excessive. */
	for (i = 0; i < 100; i++) {
		val4 = CSR_READ_4(sc, BASE_CFG_COMMAND_CONFIG);
		if ((val4 & mask) == 0) {
			break;
		}
		DELAY(10);
	}
	if ((val4 & mask) != 0) {
		device_printf(sc->atse_dev, "Disabling MAC TX/RX timed out.\n");
		return (ENXIO);
	}
	/* b. MAC FIFO configuration. */
	CSR_WRITE_4(sc, BASE_CFG_TX_SECTION_EMPTY, FIFO_DEPTH_TX - 16);
	CSR_WRITE_4(sc, BASE_CFG_TX_ALMOST_FULL, 3);
	CSR_WRITE_4(sc, BASE_CFG_TX_ALMOST_EMPTY, 8);
	CSR_WRITE_4(sc, BASE_CFG_RX_SECTION_EMPTY, FIFO_DEPTH_RX - 16);
	CSR_WRITE_4(sc, BASE_CFG_RX_ALMOST_FULL, 8);
	CSR_WRITE_4(sc, BASE_CFG_RX_ALMOST_EMPTY, 8);
#if 0
	CSR_WRITE_4(sc, BASE_CFG_TX_SECTION_FULL, 16);
	CSR_WRITE_4(sc, BASE_CFG_RX_SECTION_FULL, 16);
#else
	/* For store-and-forward mode, set this threshold to 0. */
	CSR_WRITE_4(sc, BASE_CFG_TX_SECTION_FULL, 0);
	CSR_WRITE_4(sc, BASE_CFG_RX_SECTION_FULL, 0);
#endif
	/* c. MAC address configuration. */
	/* Also intialize supplementary addresses to our primary one. */
	/* XXX-BZ FreeBSD really needs to grow and API for using these. */
	atse_get_eth_address(sc);
	atse_set_eth_address(sc, ATSE_ETH_ADDR_ALL);

	/* d. MAC function configuration. */
	CSR_WRITE_4(sc, BASE_CFG_FRM_LENGTH, 1518);	/* Default. */
	CSR_WRITE_4(sc, BASE_CFG_TX_IPG_LENGTH, 12);
	CSR_WRITE_4(sc, BASE_CFG_PAUSE_QUANT, 0xFFFF);

	val4 = CSR_READ_4(sc, BASE_CFG_COMMAND_CONFIG);
	/*
	 * If 1000BASE-X/SGMII PCS is initialized, set the ETH_SPEED (bit 3)
	 * and ENA_10 (bit 25) in command_config register to 0.  If half duplex
	 * is reported in the PHY/PCS status register, set the HD_ENA (bit 10)
	 * to 1 in command_config register.
	 * BZ: We shoot for 1000 instead.
	 */
#if 0
	val4 |= BASE_CFG_COMMAND_CONFIG_ETH_SPEED;
#else
	val4 &= ~BASE_CFG_COMMAND_CONFIG_ETH_SPEED;
#endif
	val4 &= ~BASE_CFG_COMMAND_CONFIG_ENA_10;
#if 0
	/*
	 * We do not want to set this, otherwise, we could not even send
	 * random raw ethernet frames for various other research.  By default
	 * FreeBSD will use the right ether source address.
	 */
	val4 |= BASE_CFG_COMMAND_CONFIG_TX_ADDR_INS;
#endif
	val4 |= BASE_CFG_COMMAND_CONFIG_PAD_EN;
	val4 &= ~BASE_CFG_COMMAND_CONFIG_CRC_FWD;
#if 0
	val4 |= BASE_CFG_COMMAND_CONFIG_CNTL_FRM_ENA;
#endif
#if 1
	val4 |= BASE_CFG_COMMAND_CONFIG_RX_ERR_DISC;
#endif
	val &= ~BASE_CFG_COMMAND_CONFIG_LOOP_ENA;		/* link0? */
	CSR_WRITE_4(sc, BASE_CFG_COMMAND_CONFIG, val4);

	/*
	 * Make sure we do not enable 32bit alignment;  FreeBSD cannot
	 * cope with the additional padding (though we should!?).
	 * Also make sure we get the CRC appended.
	 */
	val4 = CSR_READ_4(sc, TX_CMD_STAT);
	val4 &= ~(TX_CMD_STAT_OMIT_CRC|TX_CMD_STAT_TX_SHIFT16);
	CSR_WRITE_4(sc, TX_CMD_STAT, val4);

	val4 = CSR_READ_4(sc, RX_CMD_STAT);
	val4 &= ~RX_CMD_STAT_RX_SHIFT16;
	val4 |= RX_CMD_STAT_RX_SHIFT16;
	CSR_WRITE_4(sc, RX_CMD_STAT, val4);

	/* e. Reset MAC. */
	val4 = CSR_READ_4(sc, BASE_CFG_COMMAND_CONFIG);
	val4 |= BASE_CFG_COMMAND_CONFIG_SW_RESET;
	CSR_WRITE_4(sc, BASE_CFG_COMMAND_CONFIG, val4);
	/* Wait for bits to be cleared; i=100 is excessive. */
	for (i = 0; i < 100; i++) {
		val4 = CSR_READ_4(sc, BASE_CFG_COMMAND_CONFIG);
		if ((val4 & BASE_CFG_COMMAND_CONFIG_SW_RESET) == 0) {
			break;
		}
		DELAY(10);
	}
	if ((val4 & BASE_CFG_COMMAND_CONFIG_SW_RESET) != 0) {
		device_printf(sc->atse_dev, "MAC reset timed out.\n");
		return (ENXIO);
	}

	/* f. Enable MAC transmit and receive datapath. */
	mask = BASE_CFG_COMMAND_CONFIG_TX_ENA|BASE_CFG_COMMAND_CONFIG_RX_ENA;
	val4 = CSR_READ_4(sc, BASE_CFG_COMMAND_CONFIG);
	val4 |= mask;
	CSR_WRITE_4(sc, BASE_CFG_COMMAND_CONFIG, val4);
	/* Wait for bits to be cleared; i=100 is excessive. */
	for (i = 0; i < 100; i++) {
		val4 = CSR_READ_4(sc, BASE_CFG_COMMAND_CONFIG);
		if ((val4 & mask) == mask) {
			break;
		}
		DELAY(10);
	}
	if ((val4 & mask) != mask) {
		device_printf(sc->atse_dev, "Enabling MAC TX/RX timed out.\n");
		return (ENXIO);
	}

	return (0);
}