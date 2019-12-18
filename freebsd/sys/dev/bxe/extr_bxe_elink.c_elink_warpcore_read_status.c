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
typedef  int uint16_t ;
struct elink_vars {int link_status; int duplex; int /*<<< orphan*/  flow_ctrl; int /*<<< orphan*/  rx_tx_asic_rst; } ;
struct elink_phy {int flags; scalar_t__ req_line_speed; int supported; scalar_t__ media_type; } ;
struct elink_params {scalar_t__ loopback_mode; struct bxe_softc* sc; } ;
struct bxe_softc {int dummy; } ;
typedef  int /*<<< orphan*/  elink_status_t ;

/* Variables and functions */
 int DUPLEX_FULL ; 
 int /*<<< orphan*/  ELINK_DEBUG_P1 (struct bxe_softc*,char*,int) ; 
 int /*<<< orphan*/  ELINK_DEBUG_P2 (struct bxe_softc*,char*,int,int) ; 
 int /*<<< orphan*/  ELINK_DEBUG_P3 (struct bxe_softc*,char*,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ELINK_ETH_PHY_KR ; 
 int ELINK_FLAGS_WC_DUAL_MODE ; 
 scalar_t__ ELINK_SINGLE_MEDIA_DIRECT (struct elink_params*) ; 
 scalar_t__ ELINK_SPEED_10000 ; 
 scalar_t__ ELINK_SPEED_AUTO_NEG ; 
 int /*<<< orphan*/  ELINK_STATUS_OK ; 
 int ELINK_SUPPORTED_20000baseKR2_Full ; 
 int ELINK_SUPPORTED_20000baseMLD2_Full ; 
 int LINK_STATUS_AUTO_NEGOTIATE_COMPLETE ; 
 int LINK_STATUS_LINK_PARTNER_1000TFD_CAPABLE ; 
 int LINK_STATUS_LINK_PARTNER_10GXFD_CAPABLE ; 
 int LINK_STATUS_LINK_PARTNER_2500XFD_CAPABLE ; 
 int LINK_STATUS_PARALLEL_DETECTION_USED ; 
 int /*<<< orphan*/  MAX_KR_LINK_RETRY ; 
 int /*<<< orphan*/  MDIO_AN_DEVAD ; 
 int MDIO_AN_REG_LP_AUTO_NEG2 ; 
 int MDIO_AN_REG_STATUS ; 
 int MDIO_CL73_IEEEB1_AN_ADV2_ADVR_1000M_KX ; 
 int MDIO_CL73_IEEEB1_AN_ADV2_ADVR_10G_KR ; 
 int MDIO_CL73_IEEEB1_AN_ADV2_ADVR_10G_KX4 ; 
 int MDIO_OVER_1G_UP1_10G ; 
 int MDIO_OVER_1G_UP1_10GH ; 
 int MDIO_OVER_1G_UP1_2_5G ; 
 int /*<<< orphan*/  MDIO_WC_DEVAD ; 
 int MDIO_WC_REG_DIGITAL3_LP_UP1 ; 
 int MDIO_WC_REG_DIGITAL5_LINK_STATUS ; 
 int MDIO_WC_REG_GP2_STATUS_GP_2_1 ; 
 int MDIO_WC_REG_GP2_STATUS_GP_2_2 ; 
 int MDIO_WC_REG_GP2_STATUS_GP_2_3 ; 
 int MDIO_WC_REG_GP2_STATUS_GP_2_4 ; 
 int MDIO_WC_REG_PAR_DET_10G_STATUS ; 
 int /*<<< orphan*/  elink_cl45_read (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  elink_ext_phy_resolve_fc (struct elink_phy*,struct elink_params*,struct elink_vars*) ; 
 int /*<<< orphan*/  elink_get_link_speed_duplex (struct elink_phy*,struct elink_params*,struct elink_vars*,int,int,int) ; 
 int elink_get_warpcore_lane (struct elink_phy*,struct elink_params*) ; 

__attribute__((used)) static elink_status_t elink_warpcore_read_status(struct elink_phy *phy,
				     struct elink_params *params,
				     struct elink_vars *vars)
{
	struct bxe_softc *sc = params->sc;
	uint8_t lane;
	uint16_t gp_status1, gp_speed, link_up, duplex = DUPLEX_FULL;
	elink_status_t rc = ELINK_STATUS_OK;
	lane = elink_get_warpcore_lane(phy, params);
	/* Read gp_status */
	if ((params->loopback_mode) &&
	    (phy->flags & ELINK_FLAGS_WC_DUAL_MODE)) {
		elink_cl45_read(sc, phy, MDIO_WC_DEVAD,
				MDIO_WC_REG_DIGITAL5_LINK_STATUS, &link_up);
		elink_cl45_read(sc, phy, MDIO_WC_DEVAD,
				MDIO_WC_REG_DIGITAL5_LINK_STATUS, &link_up);
		link_up &= 0x1;
		ELINK_DEBUG_P1(sc, "params->loopback_mode link_up read = %x\n",
				link_up);
	} else if ((phy->req_line_speed > ELINK_SPEED_10000) &&
		(phy->supported & ELINK_SUPPORTED_20000baseMLD2_Full)) {
		uint16_t temp_link_up;
		elink_cl45_read(sc, phy, MDIO_WC_DEVAD,
				1, &temp_link_up);
		elink_cl45_read(sc, phy, MDIO_WC_DEVAD,
				1, &link_up);
		ELINK_DEBUG_P2(sc, "PCS RX link status = 0x%x-->0x%x\n",
			       temp_link_up, link_up);
		link_up &= (1<<2);
		if (link_up)
			elink_ext_phy_resolve_fc(phy, params, vars);
	} else {
		elink_cl45_read(sc, phy, MDIO_WC_DEVAD,
				MDIO_WC_REG_GP2_STATUS_GP_2_1,
				&gp_status1);
		ELINK_DEBUG_P1(sc, "0x81d1 = 0x%x\n", gp_status1);
		/* Check for either KR, 1G, or AN up. */
		link_up = ((gp_status1 >> 8) |
			   (gp_status1 >> 12) |
			   (gp_status1)) &
			(1 << lane);
		if (phy->supported & ELINK_SUPPORTED_20000baseKR2_Full) {
			uint16_t an_link;
			elink_cl45_read(sc, phy, MDIO_AN_DEVAD,
					MDIO_AN_REG_STATUS, &an_link);
			elink_cl45_read(sc, phy, MDIO_AN_DEVAD,
					MDIO_AN_REG_STATUS, &an_link);
			link_up |= (an_link & (1<<2));
			ELINK_DEBUG_P2(sc,"an_link = %x, link_up = %x\n", an_link,
						link_up);
		}
		if (link_up && ELINK_SINGLE_MEDIA_DIRECT(params)) {
			uint16_t pd, gp_status4;
			if (phy->req_line_speed == ELINK_SPEED_AUTO_NEG) {
				/* Check Autoneg complete */
				elink_cl45_read(sc, phy, MDIO_WC_DEVAD,
						MDIO_WC_REG_GP2_STATUS_GP_2_4,
						&gp_status4);
				if (gp_status4 & ((1<<12)<<lane))
					vars->link_status |=
					LINK_STATUS_AUTO_NEGOTIATE_COMPLETE;

				/* Check parallel detect used */
				elink_cl45_read(sc, phy, MDIO_WC_DEVAD,
						MDIO_WC_REG_PAR_DET_10G_STATUS,
						&pd);
				if (pd & (1<<15))
					vars->link_status |=
					LINK_STATUS_PARALLEL_DETECTION_USED;
				ELINK_DEBUG_P2(sc, "pd = %x, link_status = %x\n",
						pd, vars->link_status);
			}
			elink_ext_phy_resolve_fc(phy, params, vars);
			vars->duplex = duplex;
			ELINK_DEBUG_P3(sc, " ELINK_SINGLE_MEDIA_DIRECT duplex %x  flow_ctrl 0x%x link_status 0x%x\n",
					vars->duplex, vars->flow_ctrl, vars->link_status);
		}
	}
	ELINK_DEBUG_P3(sc, "duplex %x  flow_ctrl 0x%x link_status 0x%x\n",
			vars->duplex, vars->flow_ctrl, vars->link_status);
	if ((vars->link_status & LINK_STATUS_AUTO_NEGOTIATE_COMPLETE) &&
	    ELINK_SINGLE_MEDIA_DIRECT(params)) {
		uint16_t val;

		elink_cl45_read(sc, phy, MDIO_AN_DEVAD,
				MDIO_AN_REG_LP_AUTO_NEG2, &val);

		if (val & MDIO_CL73_IEEEB1_AN_ADV2_ADVR_1000M_KX)
			vars->link_status |=
				LINK_STATUS_LINK_PARTNER_1000TFD_CAPABLE;
		if (val & (MDIO_CL73_IEEEB1_AN_ADV2_ADVR_10G_KX4 |
			   MDIO_CL73_IEEEB1_AN_ADV2_ADVR_10G_KR))
			vars->link_status |=
				LINK_STATUS_LINK_PARTNER_10GXFD_CAPABLE;
		ELINK_DEBUG_P2(sc, "val = %x, link_status = %x\n",
				val, vars->link_status);
		elink_cl45_read(sc, phy, MDIO_WC_DEVAD,
				MDIO_WC_REG_DIGITAL3_LP_UP1, &val);

		if (val & MDIO_OVER_1G_UP1_2_5G)
			vars->link_status |=
				LINK_STATUS_LINK_PARTNER_2500XFD_CAPABLE;
		if (val & (MDIO_OVER_1G_UP1_10G | MDIO_OVER_1G_UP1_10GH))
			vars->link_status |=
				LINK_STATUS_LINK_PARTNER_10GXFD_CAPABLE;
		ELINK_DEBUG_P2(sc, "val = %x, link_status = %x\n",
				val, vars->link_status);

	}


	if (lane < 2) {
		elink_cl45_read(sc, phy, MDIO_WC_DEVAD,
				MDIO_WC_REG_GP2_STATUS_GP_2_2, &gp_speed);
	} else {
		elink_cl45_read(sc, phy, MDIO_WC_DEVAD,
				MDIO_WC_REG_GP2_STATUS_GP_2_3, &gp_speed);
	}
	ELINK_DEBUG_P2(sc, "lane %d gp_speed 0x%x\n", lane, gp_speed);

	if ((lane & 1) == 0)
		gp_speed <<= 8;
	gp_speed &= 0x3f00;
	link_up = !!link_up;

	/* Reset the TX FIFO to fix SGMII issue */
	rc = elink_get_link_speed_duplex(phy, params, vars, link_up, gp_speed,
					 duplex);

	/* In case of KR link down, start up the recovering procedure */
	if ((!link_up) && (phy->media_type == ELINK_ETH_PHY_KR) &&
	    (!(phy->flags & ELINK_FLAGS_WC_DUAL_MODE)))
		vars->rx_tx_asic_rst = MAX_KR_LINK_RETRY;

	ELINK_DEBUG_P3(sc, "duplex %x  flow_ctrl 0x%x link_status 0x%x\n",
		   vars->duplex, vars->flow_ctrl, vars->link_status);
	return rc;
}