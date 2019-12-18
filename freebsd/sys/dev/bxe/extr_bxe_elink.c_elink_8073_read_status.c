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
struct elink_vars {scalar_t__ line_speed; int link_status; int /*<<< orphan*/  duplex; } ;
struct elink_phy {scalar_t__ req_line_speed; } ;
struct elink_params {int port; int lane_config; struct bxe_softc* sc; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUPLEX_FULL ; 
 int /*<<< orphan*/  ELINK_DEBUG_P0 (struct bxe_softc*,char*) ; 
 int /*<<< orphan*/  ELINK_DEBUG_P1 (struct bxe_softc*,char*,int) ; 
 int /*<<< orphan*/  ELINK_DEBUG_P2 (struct bxe_softc*,char*,int,int) ; 
 int /*<<< orphan*/  ELINK_DEBUG_P3 (struct bxe_softc*,char*,int,int,int) ; 
 scalar_t__ ELINK_SPEED_1000 ; 
 scalar_t__ ELINK_SPEED_10000 ; 
 scalar_t__ ELINK_SPEED_2500 ; 
 int LINK_STATUS_AUTO_NEGOTIATE_COMPLETE ; 
 int LINK_STATUS_LINK_PARTNER_1000TFD_CAPABLE ; 
 int LINK_STATUS_LINK_PARTNER_10GXFD_CAPABLE ; 
 int /*<<< orphan*/  MDIO_AN_DEVAD ; 
 int /*<<< orphan*/  MDIO_AN_REG_LINK_STATUS ; 
 int /*<<< orphan*/  MDIO_AN_REG_LP_AUTO_NEG2 ; 
 int /*<<< orphan*/  MDIO_PCS_DEVAD ; 
 int /*<<< orphan*/  MDIO_PCS_REG_STATUS ; 
 int /*<<< orphan*/  MDIO_PMA_DEVAD ; 
 int /*<<< orphan*/  MDIO_PMA_LASI_RXSTAT ; 
 int /*<<< orphan*/  MDIO_PMA_LASI_STAT ; 
 int /*<<< orphan*/  MDIO_PMA_REG_8073_SPEED_LINK_STATUS ; 
 int /*<<< orphan*/  MDIO_PMA_REG_CDR_BANDWIDTH ; 
 int /*<<< orphan*/  MDIO_PMA_REG_M8051_MSGOUT_REG ; 
 int /*<<< orphan*/  MDIO_PMA_REG_PLL_BANDWIDTH ; 
 int /*<<< orphan*/  MDIO_PMA_REG_STATUS ; 
 int /*<<< orphan*/  MDIO_XS_DEVAD ; 
 int /*<<< orphan*/  MDIO_XS_REG_8073_RX_CTRL_PCIE ; 
 int PORT_HW_CFG_SWAP_PHY_POLARITY_ENABLED ; 
 scalar_t__ elink_8073_is_snr_needed (struct bxe_softc*,struct elink_phy*) ; 
 int /*<<< orphan*/  elink_8073_resolve_fc (struct elink_phy*,struct elink_params*,struct elink_vars*) ; 
 scalar_t__ elink_8073_xaui_wa (struct bxe_softc*,struct elink_phy*) ; 
 int /*<<< orphan*/  elink_cl45_read (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  elink_cl45_write (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  elink_ext_phy_10G_an_resolve (struct bxe_softc*,struct elink_phy*,struct elink_vars*) ; 

__attribute__((used)) static uint8_t elink_8073_read_status(struct elink_phy *phy,
				 struct elink_params *params,
				 struct elink_vars *vars)
{
	struct bxe_softc *sc = params->sc;
	uint8_t link_up = 0;
	uint16_t val1, val2;
	uint16_t link_status = 0;
	uint16_t an1000_status = 0;

	elink_cl45_read(sc, phy,
			MDIO_PMA_DEVAD, MDIO_PMA_LASI_STAT, &val1);

	ELINK_DEBUG_P1(sc, "8703 LASI status 0x%x\n", val1);

	/* Clear the interrupt LASI status register */
	elink_cl45_read(sc, phy,
			MDIO_PCS_DEVAD, MDIO_PCS_REG_STATUS, &val2);
	elink_cl45_read(sc, phy,
			MDIO_PCS_DEVAD, MDIO_PCS_REG_STATUS, &val1);
	ELINK_DEBUG_P2(sc, "807x PCS status 0x%x->0x%x\n", val2, val1);
	/* Clear MSG-OUT */
	elink_cl45_read(sc, phy,
			MDIO_PMA_DEVAD, MDIO_PMA_REG_M8051_MSGOUT_REG, &val1);

	/* Check the LASI */
	elink_cl45_read(sc, phy,
			MDIO_PMA_DEVAD, MDIO_PMA_LASI_RXSTAT, &val2);

	ELINK_DEBUG_P1(sc, "KR 0x9003 0x%x\n", val2);

	/* Check the link status */
	elink_cl45_read(sc, phy,
			MDIO_PCS_DEVAD, MDIO_PCS_REG_STATUS, &val2);
	ELINK_DEBUG_P1(sc, "KR PCS status 0x%x\n", val2);

	elink_cl45_read(sc, phy,
			MDIO_PMA_DEVAD, MDIO_PMA_REG_STATUS, &val2);
	elink_cl45_read(sc, phy,
			MDIO_PMA_DEVAD, MDIO_PMA_REG_STATUS, &val1);
	link_up = ((val1 & 4) == 4);
	ELINK_DEBUG_P1(sc, "PMA_REG_STATUS=0x%x\n", val1);

	if (link_up &&
	     ((phy->req_line_speed != ELINK_SPEED_10000))) {
		if (elink_8073_xaui_wa(sc, phy) != 0)
			return 0;
	}
	elink_cl45_read(sc, phy,
			MDIO_AN_DEVAD, MDIO_AN_REG_LINK_STATUS, &an1000_status);
	elink_cl45_read(sc, phy,
			MDIO_AN_DEVAD, MDIO_AN_REG_LINK_STATUS, &an1000_status);

	/* Check the link status on 1.1.2 */
	elink_cl45_read(sc, phy,
			MDIO_PMA_DEVAD, MDIO_PMA_REG_STATUS, &val2);
	elink_cl45_read(sc, phy,
			MDIO_PMA_DEVAD, MDIO_PMA_REG_STATUS, &val1);
	ELINK_DEBUG_P3(sc, "KR PMA status 0x%x->0x%x,"
		   "an_link_status=0x%x\n", val2, val1, an1000_status);

	link_up = (((val1 & 4) == 4) || (an1000_status & (1<<1)));
	if (link_up && elink_8073_is_snr_needed(sc, phy)) {
		/* The SNR will improve about 2dbby changing the BW and FEE main
		 * tap. The 1st write to change FFE main tap is set before
		 * restart AN. Change PLL Bandwidth in EDC register
		 */
		elink_cl45_write(sc, phy,
				 MDIO_PMA_DEVAD, MDIO_PMA_REG_PLL_BANDWIDTH,
				 0x26BC);

		/* Change CDR Bandwidth in EDC register */
		elink_cl45_write(sc, phy,
				 MDIO_PMA_DEVAD, MDIO_PMA_REG_CDR_BANDWIDTH,
				 0x0333);
	}
	elink_cl45_read(sc, phy,
			MDIO_PMA_DEVAD, MDIO_PMA_REG_8073_SPEED_LINK_STATUS,
			&link_status);

	/* Bits 0..2 --> speed detected, bits 13..15--> link is down */
	if ((link_status & (1<<2)) && (!(link_status & (1<<15)))) {
		link_up = 1;
		vars->line_speed = ELINK_SPEED_10000;
		ELINK_DEBUG_P1(sc, "port %x: External link up in 10G\n",
			   params->port);
	} else if ((link_status & (1<<1)) && (!(link_status & (1<<14)))) {
		link_up = 1;
		vars->line_speed = ELINK_SPEED_2500;
		ELINK_DEBUG_P1(sc, "port %x: External link up in 2.5G\n",
			   params->port);
	} else if ((link_status & (1<<0)) && (!(link_status & (1<<13)))) {
		link_up = 1;
		vars->line_speed = ELINK_SPEED_1000;
		ELINK_DEBUG_P1(sc, "port %x: External link up in 1G\n",
			   params->port);
	} else {
		link_up = 0;
		ELINK_DEBUG_P1(sc, "port %x: External link is down\n",
			   params->port);
	}

	if (link_up) {
		/* Swap polarity if required */
		if (params->lane_config &
		    PORT_HW_CFG_SWAP_PHY_POLARITY_ENABLED) {
			/* Configure the 8073 to swap P and N of the KR lines */
			elink_cl45_read(sc, phy,
					MDIO_XS_DEVAD,
					MDIO_XS_REG_8073_RX_CTRL_PCIE, &val1);
			/* Set bit 3 to invert Rx in 1G mode and clear this bit
			 * when it`s in 10G mode.
			 */
			if (vars->line_speed == ELINK_SPEED_1000) {
				ELINK_DEBUG_P0(sc, "Swapping 1G polarity for"
					      "the 8073\n");
				val1 |= (1<<3);
			} else
				val1 &= ~(1<<3);

			elink_cl45_write(sc, phy,
					 MDIO_XS_DEVAD,
					 MDIO_XS_REG_8073_RX_CTRL_PCIE,
					 val1);
		}
		elink_ext_phy_10G_an_resolve(sc, phy, vars);
		elink_8073_resolve_fc(phy, params, vars);
		vars->duplex = DUPLEX_FULL;
	}

	if (vars->link_status & LINK_STATUS_AUTO_NEGOTIATE_COMPLETE) {
		elink_cl45_read(sc, phy, MDIO_AN_DEVAD,
				MDIO_AN_REG_LP_AUTO_NEG2, &val1);

		if (val1 & (1<<5))
			vars->link_status |=
				LINK_STATUS_LINK_PARTNER_1000TFD_CAPABLE;
		if (val1 & (1<<7))
			vars->link_status |=
				LINK_STATUS_LINK_PARTNER_10GXFD_CAPABLE;
	}

	return link_up;
}