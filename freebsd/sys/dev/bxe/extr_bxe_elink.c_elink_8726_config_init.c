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
struct elink_vars {int dummy; } ;
struct elink_phy {scalar_t__ req_line_speed; int speed_cap_mask; int* tx_preemphasis; } ;
struct elink_params {int feature_config_flags; struct bxe_softc* sc; } ;
struct bxe_softc {int dummy; } ;
typedef  int /*<<< orphan*/  elink_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  ELINK_DEBUG_P0 (struct bxe_softc*,char*) ; 
 int /*<<< orphan*/  ELINK_DEBUG_P2 (struct bxe_softc*,char*,int,int) ; 
 int ELINK_FEATURE_CONFIG_OVERRIDE_PREEMPHASIS_ENABLED ; 
 scalar_t__ ELINK_SPEED_1000 ; 
 scalar_t__ ELINK_SPEED_AUTO_NEG ; 
 int /*<<< orphan*/  ELINK_STATUS_OK ; 
 int /*<<< orphan*/  MDIO_AN_DEVAD ; 
 int /*<<< orphan*/  MDIO_AN_REG_ADV ; 
 int /*<<< orphan*/  MDIO_AN_REG_CL37_AN ; 
 int /*<<< orphan*/  MDIO_AN_REG_CL37_CL73 ; 
 int /*<<< orphan*/  MDIO_AN_REG_CL37_FC_LD ; 
 int /*<<< orphan*/  MDIO_AN_REG_CTRL ; 
 int /*<<< orphan*/  MDIO_PMA_DEVAD ; 
 int /*<<< orphan*/  MDIO_PMA_LASI_CTRL ; 
 int /*<<< orphan*/  MDIO_PMA_LASI_RXCTRL ; 
 int /*<<< orphan*/  MDIO_PMA_REG_10G_CTRL2 ; 
 int /*<<< orphan*/  MDIO_PMA_REG_8726_TX_CTRL1 ; 
 int /*<<< orphan*/  MDIO_PMA_REG_8726_TX_CTRL2 ; 
 int /*<<< orphan*/  MDIO_PMA_REG_CTRL ; 
 int PORT_HW_CFG_SPEED_CAPABILITY_D0_10G ; 
 int PORT_HW_CFG_SPEED_CAPABILITY_D0_1G ; 
 int /*<<< orphan*/  elink_8726_external_rom_boot (struct elink_phy*,struct elink_params*) ; 
 int /*<<< orphan*/  elink_cl45_write (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  elink_ext_phy_set_pause (struct elink_params*,struct elink_phy*,struct elink_vars*) ; 
 int /*<<< orphan*/  elink_sfp_module_detection (struct elink_phy*,struct elink_params*) ; 
 int /*<<< orphan*/  elink_wait_reset_complete (struct bxe_softc*,struct elink_phy*,struct elink_params*) ; 

__attribute__((used)) static elink_status_t elink_8726_config_init(struct elink_phy *phy,
				  struct elink_params *params,
				  struct elink_vars *vars)
{
	struct bxe_softc *sc = params->sc;
	ELINK_DEBUG_P0(sc, "Initializing BCM8726\n");

	elink_cl45_write(sc, phy, MDIO_PMA_DEVAD, MDIO_PMA_REG_CTRL, 1<<15);
	elink_wait_reset_complete(sc, phy, params);

	elink_8726_external_rom_boot(phy, params);

	/* Need to call module detected on initialization since the module
	 * detection triggered by actual module insertion might occur before
	 * driver is loaded, and when driver is loaded, it reset all
	 * registers, including the transmitter
	 */
	elink_sfp_module_detection(phy, params);

	if (phy->req_line_speed == ELINK_SPEED_1000) {
		ELINK_DEBUG_P0(sc, "Setting 1G force\n");
		elink_cl45_write(sc, phy,
				 MDIO_PMA_DEVAD, MDIO_PMA_REG_CTRL, 0x40);
		elink_cl45_write(sc, phy,
				 MDIO_PMA_DEVAD, MDIO_PMA_REG_10G_CTRL2, 0xD);
		elink_cl45_write(sc, phy,
				 MDIO_PMA_DEVAD, MDIO_PMA_LASI_CTRL, 0x5);
		elink_cl45_write(sc, phy,
				 MDIO_PMA_DEVAD, MDIO_PMA_LASI_RXCTRL,
				 0x400);
	} else if ((phy->req_line_speed == ELINK_SPEED_AUTO_NEG) &&
		   (phy->speed_cap_mask &
		      PORT_HW_CFG_SPEED_CAPABILITY_D0_1G) &&
		   ((phy->speed_cap_mask &
		      PORT_HW_CFG_SPEED_CAPABILITY_D0_10G) !=
		    PORT_HW_CFG_SPEED_CAPABILITY_D0_10G)) {
		ELINK_DEBUG_P0(sc, "Setting 1G clause37\n");
		/* Set Flow control */
		elink_ext_phy_set_pause(params, phy, vars);
		elink_cl45_write(sc, phy,
				 MDIO_AN_DEVAD, MDIO_AN_REG_ADV, 0x20);
		elink_cl45_write(sc, phy,
				 MDIO_AN_DEVAD, MDIO_AN_REG_CL37_CL73, 0x040c);
		elink_cl45_write(sc, phy,
				 MDIO_AN_DEVAD, MDIO_AN_REG_CL37_FC_LD, 0x0020);
		elink_cl45_write(sc, phy,
				 MDIO_AN_DEVAD, MDIO_AN_REG_CL37_AN, 0x1000);
		elink_cl45_write(sc, phy,
				MDIO_AN_DEVAD, MDIO_AN_REG_CTRL, 0x1200);
		/* Enable RX-ALARM control to receive interrupt for 1G speed
		 * change
		 */
		elink_cl45_write(sc, phy,
				 MDIO_PMA_DEVAD, MDIO_PMA_LASI_CTRL, 0x4);
		elink_cl45_write(sc, phy,
				 MDIO_PMA_DEVAD, MDIO_PMA_LASI_RXCTRL,
				 0x400);

	} else { /* Default 10G. Set only LASI control */
		elink_cl45_write(sc, phy,
				 MDIO_PMA_DEVAD, MDIO_PMA_LASI_CTRL, 1);
	}

	/* Set TX PreEmphasis if needed */
	if ((params->feature_config_flags &
	     ELINK_FEATURE_CONFIG_OVERRIDE_PREEMPHASIS_ENABLED)) {
		ELINK_DEBUG_P2(sc,
		   "Setting TX_CTRL1 0x%x, TX_CTRL2 0x%x\n",
			 phy->tx_preemphasis[0],
			 phy->tx_preemphasis[1]);
		elink_cl45_write(sc, phy,
				 MDIO_PMA_DEVAD,
				 MDIO_PMA_REG_8726_TX_CTRL1,
				 phy->tx_preemphasis[0]);

		elink_cl45_write(sc, phy,
				 MDIO_PMA_DEVAD,
				 MDIO_PMA_REG_8726_TX_CTRL2,
				 phy->tx_preemphasis[1]);
	}

	return ELINK_STATUS_OK;

}