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
struct elink_vars {int line_speed; scalar_t__ duplex; int /*<<< orphan*/  link_status; } ;
struct elink_phy {int dummy; } ;
struct elink_params {int feature_config_flags; struct bxe_softc* sc; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 scalar_t__ DUPLEX_FULL ; 
 scalar_t__ DUPLEX_HALF ; 
 int /*<<< orphan*/  ELINK_DEBUG_P1 (struct bxe_softc*,char*,int) ; 
 int /*<<< orphan*/  ELINK_DEBUG_P2 (struct bxe_softc*,char*,int,int) ; 
 int ELINK_FEATURE_CONFIG_IEEE_PHY_TEST ; 
 int ELINK_SPEED_10 ; 
 int ELINK_SPEED_100 ; 
 int ELINK_SPEED_1000 ; 
 int ELINK_SPEED_10000 ; 
 int /*<<< orphan*/  LINK_STATUS_AUTO_NEGOTIATE_COMPLETE ; 
 int /*<<< orphan*/  LINK_STATUS_LINK_PARTNER_1000TFD_CAPABLE ; 
 int /*<<< orphan*/  LINK_STATUS_LINK_PARTNER_1000THD_CAPABLE ; 
 int /*<<< orphan*/  LINK_STATUS_LINK_PARTNER_100T4_CAPABLE ; 
 int /*<<< orphan*/  LINK_STATUS_LINK_PARTNER_100TXFD_CAPABLE ; 
 int /*<<< orphan*/  LINK_STATUS_LINK_PARTNER_100TXHD_CAPABLE ; 
 int /*<<< orphan*/  LINK_STATUS_LINK_PARTNER_10GXFD_CAPABLE ; 
 int /*<<< orphan*/  LINK_STATUS_LINK_PARTNER_10TFD_CAPABLE ; 
 int /*<<< orphan*/  LINK_STATUS_LINK_PARTNER_10THD_CAPABLE ; 
 int /*<<< orphan*/  LINK_STATUS_PARALLEL_DETECTION_USED ; 
 int /*<<< orphan*/  MDIO_AN_DEVAD ; 
 int MDIO_AN_REG_1000T_STATUS ; 
 int /*<<< orphan*/  MDIO_AN_REG_8481_EXPANSION_REG_ACCESS ; 
 int MDIO_AN_REG_8481_EXPANSION_REG_RD_RW ; 
 int MDIO_AN_REG_8481_LEGACY_AN_EXPANSION ; 
 int MDIO_AN_REG_8481_LEGACY_MII_CTRL ; 
 int MDIO_AN_REG_8481_LEGACY_MII_STATUS ; 
 int MDIO_AN_REG_CL37_FC_LP ; 
 int MDIO_AN_REG_MASTER_STATUS ; 
 int /*<<< orphan*/  MDIO_PMA_DEVAD ; 
 int MDIO_PMA_REG_8481_PMD_SIGNAL ; 
 int /*<<< orphan*/  elink_cl45_read (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  elink_cl45_write (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  elink_eee_an_resolve (struct elink_phy*,struct elink_params*,struct elink_vars*) ; 
 int /*<<< orphan*/  elink_ext_phy_10G_an_resolve (struct bxe_softc*,struct elink_phy*,struct elink_vars*) ; 
 int /*<<< orphan*/  elink_ext_phy_resolve_fc (struct elink_phy*,struct elink_params*,struct elink_vars*) ; 
 scalar_t__ elink_is_8483x_8485x (struct elink_phy*) ; 

__attribute__((used)) static uint8_t elink_848xx_read_status(struct elink_phy *phy,
				  struct elink_params *params,
				  struct elink_vars *vars)
{
	struct bxe_softc *sc = params->sc;
	uint16_t val, val1, val2;
	uint8_t link_up = 0;


	/* Check 10G-BaseT link status */
	/* Check PMD signal ok */
	elink_cl45_read(sc, phy,
			MDIO_AN_DEVAD, 0xFFFA, &val1);
	elink_cl45_read(sc, phy,
			MDIO_PMA_DEVAD, MDIO_PMA_REG_8481_PMD_SIGNAL,
			&val2);
	ELINK_DEBUG_P1(sc, "BCM848xx: PMD_SIGNAL 1.a811 = 0x%x\n", val2);

	/* Check link 10G */
	if (val2 & (1<<11)) {
		vars->line_speed = ELINK_SPEED_10000;
		vars->duplex = DUPLEX_FULL;
		link_up = 1;
		elink_ext_phy_10G_an_resolve(sc, phy, vars);
	} else { /* Check Legacy speed link */
		uint16_t legacy_status, legacy_speed;

		/* Enable expansion register 0x42 (Operation mode status) */
		elink_cl45_write(sc, phy,
				 MDIO_AN_DEVAD,
				 MDIO_AN_REG_8481_EXPANSION_REG_ACCESS, 0xf42);

		/* Get legacy speed operation status */
		elink_cl45_read(sc, phy,
				MDIO_AN_DEVAD,
				MDIO_AN_REG_8481_EXPANSION_REG_RD_RW,
				&legacy_status);

		ELINK_DEBUG_P1(sc, "Legacy speed status = 0x%x\n",
		   legacy_status);
		link_up = ((legacy_status & (1<<11)) == (1<<11));
		legacy_speed = (legacy_status & (3<<9));
		if (legacy_speed == (0<<9))
			vars->line_speed = ELINK_SPEED_10;
		else if (legacy_speed == (1<<9))
			vars->line_speed = ELINK_SPEED_100;
		else if (legacy_speed == (2<<9))
			vars->line_speed = ELINK_SPEED_1000;
		else { /* Should not happen: Treat as link down */
			vars->line_speed = 0;
			link_up = 0;
		}

		if (params->feature_config_flags &
			ELINK_FEATURE_CONFIG_IEEE_PHY_TEST) {
			uint16_t mii_ctrl;

			elink_cl45_read(sc, phy,
					MDIO_AN_DEVAD,
					MDIO_AN_REG_8481_LEGACY_MII_CTRL,
					&mii_ctrl);
			/* For IEEE testing, check for a fake link. */
			link_up |= ((mii_ctrl & 0x3040) == 0x40);
		}

		if (link_up) {
			if (legacy_status & (1<<8))
				vars->duplex = DUPLEX_FULL;
			else
				vars->duplex = DUPLEX_HALF;

			ELINK_DEBUG_P2(sc,
			   "Link is up in %dMbps, is_duplex_full= %d\n",
			   vars->line_speed,
			   (vars->duplex == DUPLEX_FULL));
			/* Check legacy speed AN resolution */
			elink_cl45_read(sc, phy,
					MDIO_AN_DEVAD,
					MDIO_AN_REG_8481_LEGACY_MII_STATUS,
					&val);
			if (val & (1<<5))
				vars->link_status |=
					LINK_STATUS_AUTO_NEGOTIATE_COMPLETE;
			elink_cl45_read(sc, phy,
					MDIO_AN_DEVAD,
					MDIO_AN_REG_8481_LEGACY_AN_EXPANSION,
					&val);
			if ((val & (1<<0)) == 0)
				vars->link_status |=
					LINK_STATUS_PARALLEL_DETECTION_USED;
		}
	}
	if (link_up) {
		ELINK_DEBUG_P1(sc, "BCM848x3: link speed is %d\n",
			   vars->line_speed);
		elink_ext_phy_resolve_fc(phy, params, vars);

		/* Read LP advertised speeds */
		elink_cl45_read(sc, phy, MDIO_AN_DEVAD,
				MDIO_AN_REG_CL37_FC_LP, &val);
		if (val & (1<<5))
			vars->link_status |=
				LINK_STATUS_LINK_PARTNER_10THD_CAPABLE;
		if (val & (1<<6))
			vars->link_status |=
				LINK_STATUS_LINK_PARTNER_10TFD_CAPABLE;
		if (val & (1<<7))
			vars->link_status |=
				LINK_STATUS_LINK_PARTNER_100TXHD_CAPABLE;
		if (val & (1<<8))
			vars->link_status |=
				LINK_STATUS_LINK_PARTNER_100TXFD_CAPABLE;
		if (val & (1<<9))
			vars->link_status |=
				LINK_STATUS_LINK_PARTNER_100T4_CAPABLE;

		elink_cl45_read(sc, phy, MDIO_AN_DEVAD,
				MDIO_AN_REG_1000T_STATUS, &val);

		if (val & (1<<10))
			vars->link_status |=
				LINK_STATUS_LINK_PARTNER_1000THD_CAPABLE;
		if (val & (1<<11))
			vars->link_status |=
				LINK_STATUS_LINK_PARTNER_1000TFD_CAPABLE;

		elink_cl45_read(sc, phy, MDIO_AN_DEVAD,
				MDIO_AN_REG_MASTER_STATUS, &val);

		if (val & (1<<11))
			vars->link_status |=
				LINK_STATUS_LINK_PARTNER_10GXFD_CAPABLE;

		/* Determine if EEE was negotiated */
		if (elink_is_8483x_8485x(phy))
			elink_eee_an_resolve(phy, params, vars);
	}

	return link_up;
}