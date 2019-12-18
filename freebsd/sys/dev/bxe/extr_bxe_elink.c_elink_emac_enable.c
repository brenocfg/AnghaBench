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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct elink_vars {int phy_flags; int flow_ctrl; int /*<<< orphan*/  mac_type; } ;
struct elink_params {int port; int lane_config; int feature_config_flags; struct bxe_softc* sc; } ;
struct bxe_softc {int dummy; } ;
typedef  int /*<<< orphan*/  elink_status_t ;

/* Variables and functions */
 scalar_t__ CHIP_REV_IS_EMUL (struct bxe_softc*) ; 
 scalar_t__ CHIP_REV_IS_FPGA (struct bxe_softc*) ; 
 scalar_t__ CHIP_REV_IS_SLOW (struct bxe_softc*) ; 
 int /*<<< orphan*/  ELINK_DEBUG_P0 (struct bxe_softc*,char*) ; 
 int ELINK_ETH_MAX_JUMBO_PACKET_SIZE ; 
 int ELINK_ETH_OVREHEAD ; 
 int ELINK_FEATURE_CONFIG_PFC_ENABLED ; 
 int ELINK_FLOW_CTRL_RX ; 
 int ELINK_FLOW_CTRL_TX ; 
 int /*<<< orphan*/  ELINK_MAC_TYPE_EMAC ; 
 int /*<<< orphan*/  ELINK_STATUS_OK ; 
 int EMAC_MODE_PORT_GMII ; 
 int EMAC_REG_EMAC_MODE ; 
 int EMAC_REG_EMAC_RX_MODE ; 
 int EMAC_REG_EMAC_RX_MTU_SIZE ; 
 int EMAC_REG_EMAC_TX_MODE ; 
 int EMAC_REG_RX_PFC_MODE ; 
 int EMAC_REG_RX_PFC_MODE_PRIORITIES ; 
 int EMAC_REG_RX_PFC_MODE_RX_EN ; 
 int EMAC_REG_RX_PFC_MODE_TX_EN ; 
 int EMAC_REG_RX_PFC_PARAM ; 
 int EMAC_REG_RX_PFC_PARAM_OPCODE_BITSHIFT ; 
 int EMAC_REG_RX_PFC_PARAM_PRIORITY_EN_BITSHIFT ; 
 int EMAC_RX_MODE_FLOW_EN ; 
 int EMAC_RX_MODE_KEEP_MAC_CONTROL ; 
 int EMAC_RX_MODE_KEEP_VLAN_TAG ; 
 int EMAC_RX_MODE_PROMISCUOUS ; 
 int EMAC_RX_MODE_RESET ; 
 int EMAC_RX_MTU_SIZE_JUMBO_ENA ; 
 int EMAC_TX_MODE_EXT_PAUSE_EN ; 
 int EMAC_TX_MODE_FLOW_EN ; 
 int EMAC_TX_MODE_RESET ; 
 int GRCBASE_EMAC0 ; 
 int GRCBASE_EMAC1 ; 
 scalar_t__ GRCBASE_MISC ; 
 scalar_t__ MISC_REGISTERS_RESET_REG_2_CLEAR ; 
 int MISC_REGISTERS_RESET_REG_2_RST_BMAC0 ; 
 scalar_t__ MISC_REGISTERS_RESET_REG_2_SET ; 
 scalar_t__ NIG_REG_BMAC0_IN_EN ; 
 scalar_t__ NIG_REG_BMAC0_OUT_EN ; 
 scalar_t__ NIG_REG_BMAC0_PAUSE_OUT_EN ; 
 scalar_t__ NIG_REG_BMAC0_REGS_OUT_EN ; 
 scalar_t__ NIG_REG_EGRESS_EMAC0_OUT_EN ; 
 scalar_t__ NIG_REG_EGRESS_EMAC0_PORT ; 
 scalar_t__ NIG_REG_EMAC0_IN_EN ; 
 scalar_t__ NIG_REG_EMAC0_PAUSE_OUT_EN ; 
 scalar_t__ NIG_REG_NIG_EMAC0_EN ; 
 scalar_t__ NIG_REG_NIG_INGRESS_EMAC0_NO_CRC ; 
 scalar_t__ NIG_REG_XGXS_LANE_SEL_P0 ; 
 scalar_t__ NIG_REG_XGXS_SERDES0_MODE_SEL ; 
 int PHY_XGXS_FLAG ; 
 int PORT_HW_CFG_LANE_SWAP_CFG_MASTER_MASK ; 
 int PORT_HW_CFG_LANE_SWAP_CFG_MASTER_SHIFT ; 
 int REG_RD (struct bxe_softc*,int) ; 
 int /*<<< orphan*/  REG_WR (struct bxe_softc*,scalar_t__,int) ; 
 int /*<<< orphan*/  elink_bits_dis (struct bxe_softc*,int,int) ; 
 int /*<<< orphan*/  elink_bits_en (struct bxe_softc*,int,int) ; 
 int /*<<< orphan*/  elink_cb_reg_write (struct bxe_softc*,int,int) ; 

__attribute__((used)) static elink_status_t elink_emac_enable(struct elink_params *params,
			     struct elink_vars *vars, uint8_t lb)
{
	struct bxe_softc *sc = params->sc;
	uint8_t port = params->port;
	uint32_t emac_base = port ? GRCBASE_EMAC1 : GRCBASE_EMAC0;
	uint32_t val;

	ELINK_DEBUG_P0(sc, "enabling EMAC\n");

	/* Disable BMAC */
	REG_WR(sc, GRCBASE_MISC + MISC_REGISTERS_RESET_REG_2_CLEAR,
	       (MISC_REGISTERS_RESET_REG_2_RST_BMAC0 << port));

	/* enable emac and not bmac */
	REG_WR(sc, NIG_REG_EGRESS_EMAC0_PORT + port*4, 1);

#ifdef ELINK_INCLUDE_EMUL
	/* for paladium */
	if (CHIP_REV_IS_EMUL(sc)) {
		/* Use lane 1 (of lanes 0-3) */
		REG_WR(sc, NIG_REG_XGXS_LANE_SEL_P0 + port*4, 1);
		REG_WR(sc, NIG_REG_XGXS_SERDES0_MODE_SEL + port*4, 1);
	}
	/* for fpga */
	else
#endif
#ifdef ELINK_INCLUDE_FPGA
	if (CHIP_REV_IS_FPGA(sc)) {
		/* Use lane 1 (of lanes 0-3) */
		ELINK_DEBUG_P0(sc, "elink_emac_enable: Setting FPGA\n");

		REG_WR(sc, NIG_REG_XGXS_LANE_SEL_P0 + port*4, 1);
		REG_WR(sc, NIG_REG_XGXS_SERDES0_MODE_SEL + port*4, 0);
	} else
#endif
	/* ASIC */
	if (vars->phy_flags & PHY_XGXS_FLAG) {
		uint32_t ser_lane = ((params->lane_config &
				 PORT_HW_CFG_LANE_SWAP_CFG_MASTER_MASK) >>
				PORT_HW_CFG_LANE_SWAP_CFG_MASTER_SHIFT);

		ELINK_DEBUG_P0(sc, "XGXS\n");
		/* select the master lanes (out of 0-3) */
		REG_WR(sc, NIG_REG_XGXS_LANE_SEL_P0 + port*4, ser_lane);
		/* select XGXS */
		REG_WR(sc, NIG_REG_XGXS_SERDES0_MODE_SEL + port*4, 1);

	} else { /* SerDes */
		ELINK_DEBUG_P0(sc, "SerDes\n");
		/* select SerDes */
		REG_WR(sc, NIG_REG_XGXS_SERDES0_MODE_SEL + port*4, 0);
	}

	elink_bits_en(sc, emac_base + EMAC_REG_EMAC_RX_MODE,
		      EMAC_RX_MODE_RESET);
	elink_bits_en(sc, emac_base + EMAC_REG_EMAC_TX_MODE,
		      EMAC_TX_MODE_RESET);

#if defined(ELINK_INCLUDE_EMUL) || defined(ELINK_INCLUDE_FPGA)
	if (CHIP_REV_IS_SLOW(sc)) {
		/* config GMII mode */
		val = REG_RD(sc, emac_base + EMAC_REG_EMAC_MODE);
		elink_cb_reg_write(sc, emac_base + EMAC_REG_EMAC_MODE, (val | EMAC_MODE_PORT_GMII));
	} else { /* ASIC */
#endif
		/* pause enable/disable */
		elink_bits_dis(sc, emac_base + EMAC_REG_EMAC_RX_MODE,
			       EMAC_RX_MODE_FLOW_EN);

		elink_bits_dis(sc,  emac_base + EMAC_REG_EMAC_TX_MODE,
			       (EMAC_TX_MODE_EXT_PAUSE_EN |
				EMAC_TX_MODE_FLOW_EN));
		if (!(params->feature_config_flags &
		      ELINK_FEATURE_CONFIG_PFC_ENABLED)) {
			if (vars->flow_ctrl & ELINK_FLOW_CTRL_RX)
				elink_bits_en(sc, emac_base +
					      EMAC_REG_EMAC_RX_MODE,
					      EMAC_RX_MODE_FLOW_EN);

			if (vars->flow_ctrl & ELINK_FLOW_CTRL_TX)
				elink_bits_en(sc, emac_base +
					      EMAC_REG_EMAC_TX_MODE,
					      (EMAC_TX_MODE_EXT_PAUSE_EN |
					       EMAC_TX_MODE_FLOW_EN));
		} else
			elink_bits_en(sc, emac_base + EMAC_REG_EMAC_TX_MODE,
				      EMAC_TX_MODE_FLOW_EN);
#if defined(ELINK_INCLUDE_EMUL) || defined(ELINK_INCLUDE_FPGA)
	}
#endif

	/* KEEP_VLAN_TAG, promiscuous */
	val = REG_RD(sc, emac_base + EMAC_REG_EMAC_RX_MODE);
	val |= EMAC_RX_MODE_KEEP_VLAN_TAG | EMAC_RX_MODE_PROMISCUOUS;

	/* Setting this bit causes MAC control frames (except for pause
	 * frames) to be passed on for processing. This setting has no
	 * affect on the operation of the pause frames. This bit effects
	 * all packets regardless of RX Parser packet sorting logic.
	 * Turn the PFC off to make sure we are in Xon state before
	 * enabling it.
	 */
	elink_cb_reg_write(sc, emac_base + EMAC_REG_RX_PFC_MODE, 0);
	if (params->feature_config_flags & ELINK_FEATURE_CONFIG_PFC_ENABLED) {
		ELINK_DEBUG_P0(sc, "PFC is enabled\n");
		/* Enable PFC again */
		elink_cb_reg_write(sc, emac_base + EMAC_REG_RX_PFC_MODE,
			EMAC_REG_RX_PFC_MODE_RX_EN |
			EMAC_REG_RX_PFC_MODE_TX_EN |
			EMAC_REG_RX_PFC_MODE_PRIORITIES);

		elink_cb_reg_write(sc, emac_base + EMAC_REG_RX_PFC_PARAM,
			((0x0101 <<
			  EMAC_REG_RX_PFC_PARAM_OPCODE_BITSHIFT) |
			 (0x00ff <<
			  EMAC_REG_RX_PFC_PARAM_PRIORITY_EN_BITSHIFT)));
		val |= EMAC_RX_MODE_KEEP_MAC_CONTROL;
	}
	elink_cb_reg_write(sc, emac_base + EMAC_REG_EMAC_RX_MODE, val);

	/* Set Loopback */
	val = REG_RD(sc, emac_base + EMAC_REG_EMAC_MODE);
	if (lb)
		val |= 0x810;
	else
		val &= ~0x810;
	elink_cb_reg_write(sc, emac_base + EMAC_REG_EMAC_MODE, val);

	/* Enable emac */
	REG_WR(sc, NIG_REG_NIG_EMAC0_EN + port*4, 1);

	/* Enable emac for jumbo packets */
	elink_cb_reg_write(sc, emac_base + EMAC_REG_EMAC_RX_MTU_SIZE,
		(EMAC_RX_MTU_SIZE_JUMBO_ENA |
		 (ELINK_ETH_MAX_JUMBO_PACKET_SIZE + ELINK_ETH_OVREHEAD)));

	/* Strip CRC */
	REG_WR(sc, NIG_REG_NIG_INGRESS_EMAC0_NO_CRC + port*4, 0x1);

	/* Disable the NIG in/out to the bmac */
	REG_WR(sc, NIG_REG_BMAC0_IN_EN + port*4, 0x0);
	REG_WR(sc, NIG_REG_BMAC0_PAUSE_OUT_EN + port*4, 0x0);
	REG_WR(sc, NIG_REG_BMAC0_OUT_EN + port*4, 0x0);

	/* Enable the NIG in/out to the emac */
	REG_WR(sc, NIG_REG_EMAC0_IN_EN + port*4, 0x1);
	val = 0;
	if ((params->feature_config_flags &
	      ELINK_FEATURE_CONFIG_PFC_ENABLED) ||
	    (vars->flow_ctrl & ELINK_FLOW_CTRL_TX))
		val = 1;

	REG_WR(sc, NIG_REG_EMAC0_PAUSE_OUT_EN + port*4, val);
	REG_WR(sc, NIG_REG_EGRESS_EMAC0_OUT_EN + port*4, 0x1);

#ifdef ELINK_INCLUDE_EMUL
	if (CHIP_REV_IS_EMUL(sc)) {
		/* Take the BigMac out of reset */
		REG_WR(sc, GRCBASE_MISC + MISC_REGISTERS_RESET_REG_2_SET,
		       (MISC_REGISTERS_RESET_REG_2_RST_BMAC0 << port));

		/* Enable access for bmac registers */
		REG_WR(sc, NIG_REG_BMAC0_REGS_OUT_EN + port*4, 0x1);
	} else
#endif
	REG_WR(sc, NIG_REG_BMAC0_REGS_OUT_EN + port*4, 0x0);

	vars->mac_type = ELINK_MAC_TYPE_EMAC;
	return ELINK_STATUS_OK;
}