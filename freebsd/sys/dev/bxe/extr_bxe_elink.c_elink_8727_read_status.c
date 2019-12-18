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
struct elink_vars {scalar_t__ line_speed; int fault_detected; int duplex; } ;
struct elink_phy {int flags; scalar_t__ req_line_speed; } ;
struct elink_params {int port; struct bxe_softc* sc; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHIP_IS_E1x (struct bxe_softc*) ; 
 int DUPLEX_FULL ; 
 int /*<<< orphan*/  ELINK_DEBUG_P0 (struct bxe_softc*,char*) ; 
 int /*<<< orphan*/  ELINK_DEBUG_P1 (struct bxe_softc*,char*,int) ; 
 scalar_t__ ELINK_DUAL_MEDIA (struct elink_params*) ; 
 int ELINK_FLAGS_NOC ; 
 int ELINK_FLAGS_SFP_NOT_APPROVED ; 
 int /*<<< orphan*/  ELINK_LOG_ID_OVER_CURRENT ; 
 scalar_t__ ELINK_SPEED_1000 ; 
 scalar_t__ ELINK_SPEED_10000 ; 
 int /*<<< orphan*/  MDIO_PMA_DEVAD ; 
 int /*<<< orphan*/  MDIO_PMA_LASI_CTRL ; 
 int /*<<< orphan*/  MDIO_PMA_LASI_RXCTRL ; 
 int /*<<< orphan*/  MDIO_PMA_LASI_RXSTAT ; 
 int /*<<< orphan*/  MDIO_PMA_LASI_STAT ; 
 int /*<<< orphan*/  MDIO_PMA_LASI_TXCTRL ; 
 int /*<<< orphan*/  MDIO_PMA_LASI_TXSTAT ; 
 int /*<<< orphan*/  MDIO_PMA_REG_8073_SPEED_LINK_STATUS ; 
 int /*<<< orphan*/  MDIO_PMA_REG_8727_GPIO_CTRL ; 
 int /*<<< orphan*/  MDIO_PMA_REG_8727_PCS_GP ; 
 int /*<<< orphan*/  MDIO_PMA_REG_M8051_MSGOUT_REG ; 
 int /*<<< orphan*/  MDIO_PMA_REG_PHY_IDENTIFIER ; 
 int SC_PATH (struct bxe_softc*) ; 
 int /*<<< orphan*/  elink_8727_handle_mod_abs (struct elink_phy*,struct elink_params*) ; 
 int /*<<< orphan*/  elink_8727_power_module (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elink_cb_event_log (struct bxe_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  elink_cl45_read (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  elink_cl45_write (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  elink_ext_phy_resolve_fc (struct elink_phy*,struct elink_params*,struct elink_vars*) ; 
 int /*<<< orphan*/  elink_sfp_mask_fault (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elink_sfp_set_transmitter (struct elink_params*,struct elink_phy*,int) ; 

__attribute__((used)) static uint8_t elink_8727_read_status(struct elink_phy *phy,
				 struct elink_params *params,
				 struct elink_vars *vars)

{
	struct bxe_softc *sc = params->sc;
	uint8_t link_up = 0;
	uint16_t link_status = 0;
	uint16_t rx_alarm_status, lasi_ctrl, val1;

	/* If PHY is not initialized, do not check link status */
	elink_cl45_read(sc, phy,
			MDIO_PMA_DEVAD, MDIO_PMA_LASI_CTRL,
			&lasi_ctrl);
	if (!lasi_ctrl)
		return 0;

	/* Check the LASI on Rx */
	elink_cl45_read(sc, phy,
			MDIO_PMA_DEVAD, MDIO_PMA_LASI_RXSTAT,
			&rx_alarm_status);
	vars->line_speed = 0;
	ELINK_DEBUG_P1(sc, "8727 RX_ALARM_STATUS  0x%x\n", rx_alarm_status);

	elink_sfp_mask_fault(sc, phy, MDIO_PMA_LASI_TXSTAT,
			     MDIO_PMA_LASI_TXCTRL);

	elink_cl45_read(sc, phy,
			MDIO_PMA_DEVAD, MDIO_PMA_LASI_STAT, &val1);

	ELINK_DEBUG_P1(sc, "8727 LASI status 0x%x\n", val1);

	/* Clear MSG-OUT */
	elink_cl45_read(sc, phy,
			MDIO_PMA_DEVAD, MDIO_PMA_REG_M8051_MSGOUT_REG, &val1);

	/* If a module is present and there is need to check
	 * for over current
	 */
	if (!(phy->flags & ELINK_FLAGS_NOC) && !(rx_alarm_status & (1<<5))) {
		/* Check over-current using 8727 GPIO0 input*/
		elink_cl45_read(sc, phy,
				MDIO_PMA_DEVAD, MDIO_PMA_REG_8727_GPIO_CTRL,
				&val1);

		if ((val1 & (1<<8)) == 0) {
			uint8_t oc_port = params->port;
			if (!CHIP_IS_E1x(sc))
				oc_port = SC_PATH(sc) + (params->port << 1);
			ELINK_DEBUG_P1(sc,
			   "8727 Power fault has been detected on port %d\n",
			   oc_port);
			elink_cb_event_log(sc, ELINK_LOG_ID_OVER_CURRENT, oc_port); //"Error: Power fault on Port %d has "
					  //  "been detected and the power to "
					  //  "that SFP+ module has been removed "
					  //  "to prevent failure of the card. "
					  //  "Please remove the SFP+ module and "
					  //  "restart the system to clear this "
					  //  "error.\n",
			/* Disable all RX_ALARMs except for mod_abs */
			elink_cl45_write(sc, phy,
					 MDIO_PMA_DEVAD,
					 MDIO_PMA_LASI_RXCTRL, (1<<5));

			elink_cl45_read(sc, phy,
					MDIO_PMA_DEVAD,
					MDIO_PMA_REG_PHY_IDENTIFIER, &val1);
			/* Wait for module_absent_event */
			val1 |= (1<<8);
			elink_cl45_write(sc, phy,
					 MDIO_PMA_DEVAD,
					 MDIO_PMA_REG_PHY_IDENTIFIER, val1);
			/* Clear RX alarm */
			elink_cl45_read(sc, phy,
				MDIO_PMA_DEVAD,
				MDIO_PMA_LASI_RXSTAT, &rx_alarm_status);
			elink_8727_power_module(params->sc, phy, 0);
			return 0;
		}
	} /* Over current check */

	/* When module absent bit is set, check module */
	if (rx_alarm_status & (1<<5)) {
		elink_8727_handle_mod_abs(phy, params);
		/* Enable all mod_abs and link detection bits */
		elink_cl45_write(sc, phy,
				 MDIO_PMA_DEVAD, MDIO_PMA_LASI_RXCTRL,
				 ((1<<5) | (1<<2)));
	}

	if (!(phy->flags & ELINK_FLAGS_SFP_NOT_APPROVED)) {
		ELINK_DEBUG_P0(sc, "Enabling 8727 TX laser\n");
		elink_sfp_set_transmitter(params, phy, 1);
	} else {
		ELINK_DEBUG_P0(sc, "Tx is disabled\n");
		return 0;
	}

	elink_cl45_read(sc, phy,
			MDIO_PMA_DEVAD,
			MDIO_PMA_REG_8073_SPEED_LINK_STATUS, &link_status);

	/* Bits 0..2 --> speed detected,
	 * Bits 13..15--> link is down
	 */
	if ((link_status & (1<<2)) && (!(link_status & (1<<15)))) {
		link_up = 1;
		vars->line_speed = ELINK_SPEED_10000;
		ELINK_DEBUG_P1(sc, "port %x: External link up in 10G\n",
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

	/* Capture 10G link fault. */
	if (vars->line_speed == ELINK_SPEED_10000) {
		elink_cl45_read(sc, phy, MDIO_PMA_DEVAD,
			    MDIO_PMA_LASI_TXSTAT, &val1);

		elink_cl45_read(sc, phy, MDIO_PMA_DEVAD,
			    MDIO_PMA_LASI_TXSTAT, &val1);

		if (val1 & (1<<0)) {
			vars->fault_detected = 1;
		}
	}

	if (link_up) {
		elink_ext_phy_resolve_fc(phy, params, vars);
		vars->duplex = DUPLEX_FULL;
		ELINK_DEBUG_P1(sc, "duplex = 0x%x\n", vars->duplex);
	}

	if ((ELINK_DUAL_MEDIA(params)) &&
	    (phy->req_line_speed == ELINK_SPEED_1000)) {
		elink_cl45_read(sc, phy,
				MDIO_PMA_DEVAD,
				MDIO_PMA_REG_8727_PCS_GP, &val1);
		/* In case of dual-media board and 1G, power up the XAUI side,
		 * otherwise power it down. For 10G it is done automatically
		 */
		if (link_up)
			val1 &= ~(3<<10);
		else
			val1 |= (3<<10);
		elink_cl45_write(sc, phy,
				 MDIO_PMA_DEVAD,
				 MDIO_PMA_REG_8727_PCS_GP, val1);
	}
	return link_up;
}