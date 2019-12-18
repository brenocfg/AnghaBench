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
typedef  int uint16_t ;
struct elink_vars {int dummy; } ;
struct elink_phy {scalar_t__ req_line_speed; int speed_cap_mask; scalar_t__ req_duplex; int supported; } ;
struct elink_params {struct bxe_softc* sc; } ;
struct bxe_softc {int dummy; } ;
typedef  int /*<<< orphan*/  elink_status_t ;

/* Variables and functions */
 scalar_t__ DUPLEX_FULL ; 
 int /*<<< orphan*/  ELINK_DEBUG_P0 (struct bxe_softc*,char*) ; 
 int /*<<< orphan*/  ELINK_PHY_INIT ; 
 scalar_t__ ELINK_SPEED_10 ; 
 scalar_t__ ELINK_SPEED_100 ; 
 scalar_t__ ELINK_SPEED_1000 ; 
 scalar_t__ ELINK_SPEED_10000 ; 
 scalar_t__ ELINK_SPEED_AUTO_NEG ; 
 int /*<<< orphan*/  ELINK_STATUS_OK ; 
 int ELINK_SUPPORTED_100baseT_Full ; 
 int ELINK_SUPPORTED_100baseT_Half ; 
 int ELINK_SUPPORTED_10baseT_Full ; 
 int ELINK_SUPPORTED_10baseT_Half ; 
 int /*<<< orphan*/  MDIO_AN_DEVAD ; 
 int /*<<< orphan*/  MDIO_AN_REG_8481_1000T_CTRL ; 
 int /*<<< orphan*/  MDIO_AN_REG_8481_10GBASE_T_AN_CTRL ; 
 int /*<<< orphan*/  MDIO_AN_REG_8481_AUX_CTRL ; 
 int /*<<< orphan*/  MDIO_AN_REG_8481_LEGACY_AN_ADV ; 
 int /*<<< orphan*/  MDIO_AN_REG_8481_LEGACY_MII_CTRL ; 
 int /*<<< orphan*/  MDIO_AN_REG_CTRL ; 
 int /*<<< orphan*/  MDIO_PMA_DEVAD ; 
 int /*<<< orphan*/  MDIO_PMA_REG_CTRL ; 
 int PORT_HW_CFG_SPEED_CAPABILITY_D0_100M_FULL ; 
 int PORT_HW_CFG_SPEED_CAPABILITY_D0_100M_HALF ; 
 int PORT_HW_CFG_SPEED_CAPABILITY_D0_10G ; 
 int PORT_HW_CFG_SPEED_CAPABILITY_D0_10M_FULL ; 
 int PORT_HW_CFG_SPEED_CAPABILITY_D0_10M_HALF ; 
 int PORT_HW_CFG_SPEED_CAPABILITY_D0_1G ; 
 int /*<<< orphan*/  elink_848xx_specific_func (struct elink_phy*,struct elink_params*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elink_cl45_read (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  elink_cl45_read_or_write (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  elink_cl45_write (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  elink_ext_phy_set_pause (struct elink_params*,struct elink_phy*,struct elink_vars*) ; 
 int /*<<< orphan*/  elink_is_8483x_8485x (struct elink_phy*) ; 

__attribute__((used)) static elink_status_t elink_848xx_cmn_config_init(struct elink_phy *phy,
				       struct elink_params *params,
				       struct elink_vars *vars)
{
	struct bxe_softc *sc = params->sc;
	uint16_t autoneg_val, an_1000_val, an_10_100_val;

	elink_848xx_specific_func(phy, params, ELINK_PHY_INIT);
	elink_cl45_write(sc, phy,
			 MDIO_PMA_DEVAD, MDIO_PMA_REG_CTRL, 0x0000);

	/* set 1000 speed advertisement */
	elink_cl45_read(sc, phy,
			MDIO_AN_DEVAD, MDIO_AN_REG_8481_1000T_CTRL,
			&an_1000_val);

	elink_ext_phy_set_pause(params, phy, vars);
	elink_cl45_read(sc, phy,
			MDIO_AN_DEVAD,
			MDIO_AN_REG_8481_LEGACY_AN_ADV,
			&an_10_100_val);
	elink_cl45_read(sc, phy,
			MDIO_AN_DEVAD, MDIO_AN_REG_8481_LEGACY_MII_CTRL,
			&autoneg_val);
	/* Disable forced speed */
	autoneg_val &= ~((1<<6) | (1<<8) | (1<<9) | (1<<12) | (1<<13));
	an_10_100_val &= ~((1<<5) | (1<<6) | (1<<7) | (1<<8));

	if (((phy->req_line_speed == ELINK_SPEED_AUTO_NEG) &&
	     (phy->speed_cap_mask &
	     PORT_HW_CFG_SPEED_CAPABILITY_D0_1G)) ||
	    (phy->req_line_speed == ELINK_SPEED_1000)) {
		an_1000_val |= (1<<8);
		autoneg_val |= (1<<9 | 1<<12);
		if (phy->req_duplex == DUPLEX_FULL)
			an_1000_val |= (1<<9);
		ELINK_DEBUG_P0(sc, "Advertising 1G\n");
	} else
		an_1000_val &= ~((1<<8) | (1<<9));

	elink_cl45_write(sc, phy,
			 MDIO_AN_DEVAD, MDIO_AN_REG_8481_1000T_CTRL,
			 an_1000_val);

	/* Set 10/100 speed advertisement */
	if (phy->req_line_speed == ELINK_SPEED_AUTO_NEG) {
		if (phy->speed_cap_mask &
		    PORT_HW_CFG_SPEED_CAPABILITY_D0_100M_FULL) {
			/* Enable autoneg and restart autoneg for legacy speeds
			 */
			autoneg_val |= (1<<9 | 1<<12);
			an_10_100_val |= (1<<8);
			ELINK_DEBUG_P0(sc, "Advertising 100M-FD\n");
		}

		if (phy->speed_cap_mask &
		    PORT_HW_CFG_SPEED_CAPABILITY_D0_100M_HALF) {
			/* Enable autoneg and restart autoneg for legacy speeds
			 */
			autoneg_val |= (1<<9 | 1<<12);
			an_10_100_val |= (1<<7);
			ELINK_DEBUG_P0(sc, "Advertising 100M-HD\n");
		}

		if ((phy->speed_cap_mask &
		     PORT_HW_CFG_SPEED_CAPABILITY_D0_10M_FULL) &&
		    (phy->supported & ELINK_SUPPORTED_10baseT_Full)) {
			an_10_100_val |= (1<<6);
			autoneg_val |= (1<<9 | 1<<12);
			ELINK_DEBUG_P0(sc, "Advertising 10M-FD\n");
		}

		if ((phy->speed_cap_mask &
		     PORT_HW_CFG_SPEED_CAPABILITY_D0_10M_HALF) &&
		    (phy->supported & ELINK_SUPPORTED_10baseT_Half)) {
			an_10_100_val |= (1<<5);
			autoneg_val |= (1<<9 | 1<<12);
			ELINK_DEBUG_P0(sc, "Advertising 10M-HD\n");
		}
	}

	/* Only 10/100 are allowed to work in FORCE mode */
	if ((phy->req_line_speed == ELINK_SPEED_100) &&
	    (phy->supported &
	     (ELINK_SUPPORTED_100baseT_Half |
	      ELINK_SUPPORTED_100baseT_Full))) {
		autoneg_val |= (1<<13);
		/* Enabled AUTO-MDIX when autoneg is disabled */
		elink_cl45_write(sc, phy,
				 MDIO_AN_DEVAD, MDIO_AN_REG_8481_AUX_CTRL,
				 (1<<15 | 1<<9 | 7<<0));
		/* The PHY needs this set even for forced link. */
		an_10_100_val |= (1<<8) | (1<<7);
		ELINK_DEBUG_P0(sc, "Setting 100M force\n");
	}
	if ((phy->req_line_speed == ELINK_SPEED_10) &&
	    (phy->supported &
	     (ELINK_SUPPORTED_10baseT_Half |
	      ELINK_SUPPORTED_10baseT_Full))) {
		/* Enabled AUTO-MDIX when autoneg is disabled */
		elink_cl45_write(sc, phy,
				 MDIO_AN_DEVAD, MDIO_AN_REG_8481_AUX_CTRL,
				 (1<<15 | 1<<9 | 7<<0));
		ELINK_DEBUG_P0(sc, "Setting 10M force\n");
	}

	elink_cl45_write(sc, phy,
			 MDIO_AN_DEVAD, MDIO_AN_REG_8481_LEGACY_AN_ADV,
			 an_10_100_val);

	if (phy->req_duplex == DUPLEX_FULL)
		autoneg_val |= (1<<8);

	/* Always write this if this is not 84833/4.
	 * For 84833/4, write it only when it's a forced speed.
	 */
	if (!elink_is_8483x_8485x(phy) ||
	    ((autoneg_val & (1<<12)) == 0))
		elink_cl45_write(sc, phy,
			 MDIO_AN_DEVAD,
			 MDIO_AN_REG_8481_LEGACY_MII_CTRL, autoneg_val);

	if (((phy->req_line_speed == ELINK_SPEED_AUTO_NEG) &&
	    (phy->speed_cap_mask &
	     PORT_HW_CFG_SPEED_CAPABILITY_D0_10G)) ||
		(phy->req_line_speed == ELINK_SPEED_10000)) {
			ELINK_DEBUG_P0(sc, "Advertising 10G\n");
			/* Restart autoneg for 10G*/

			elink_cl45_read_or_write(
				sc, phy,
				MDIO_AN_DEVAD,
				MDIO_AN_REG_8481_10GBASE_T_AN_CTRL,
				0x1000);
			elink_cl45_write(sc, phy,
					 MDIO_AN_DEVAD, MDIO_AN_REG_CTRL,
					 0x3200);
	} else
		elink_cl45_write(sc, phy,
				 MDIO_AN_DEVAD,
				 MDIO_AN_REG_8481_10GBASE_T_AN_CTRL,
				 1);

	return ELINK_STATUS_OK;
}