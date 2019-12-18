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
struct elink_vars {int line_speed; scalar_t__ duplex; int link_status; } ;
struct elink_phy {int flags; } ;
struct elink_params {struct bxe_softc* sc; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 scalar_t__ DUPLEX_FULL ; 
 void* DUPLEX_HALF ; 
 int /*<<< orphan*/  ELINK_DEBUG_P1 (struct bxe_softc*,char*,int) ; 
 int /*<<< orphan*/  ELINK_DEBUG_P2 (struct bxe_softc*,char*,int,int) ; 
 int ELINK_FLAGS_EEE ; 
 void* ELINK_SPEED_10 ; 
 void* ELINK_SPEED_100 ; 
 void* ELINK_SPEED_1000 ; 
 int LINK_STATUS_AUTO_NEGOTIATE_COMPLETE ; 
 int LINK_STATUS_LINK_PARTNER_1000TFD_CAPABLE ; 
 int LINK_STATUS_LINK_PARTNER_1000THD_CAPABLE ; 
 int LINK_STATUS_LINK_PARTNER_100T4_CAPABLE ; 
 int LINK_STATUS_LINK_PARTNER_100TXFD_CAPABLE ; 
 int LINK_STATUS_LINK_PARTNER_100TXHD_CAPABLE ; 
 int LINK_STATUS_LINK_PARTNER_10TFD_CAPABLE ; 
 int LINK_STATUS_LINK_PARTNER_10THD_CAPABLE ; 
 int LINK_STATUS_PARALLEL_DETECTION_USED ; 
 int MDIO_REG_GPHY_AUX_STATUS ; 
 int MDIO_REG_INTR_STATUS ; 
 int /*<<< orphan*/  elink_cl22_read (struct bxe_softc*,struct elink_phy*,int,int*) ; 
 int /*<<< orphan*/  elink_eee_an_resolve (struct elink_phy*,struct elink_params*,struct elink_vars*) ; 
 scalar_t__ elink_eee_has_cap (struct elink_params*) ; 
 int /*<<< orphan*/  elink_ext_phy_resolve_fc (struct elink_phy*,struct elink_params*,struct elink_vars*) ; 

__attribute__((used)) static uint8_t elink_54618se_read_status(struct elink_phy *phy,
				    struct elink_params *params,
				    struct elink_vars *vars)
{
	struct bxe_softc *sc = params->sc;
	uint16_t val;
	uint8_t link_up = 0;
	uint16_t legacy_status, legacy_speed;

	/* Get speed operation status */
	elink_cl22_read(sc, phy,
			MDIO_REG_GPHY_AUX_STATUS,
			&legacy_status);
	ELINK_DEBUG_P1(sc, "54618SE read_status: 0x%x\n", legacy_status);

	/* Read status to clear the PHY interrupt. */
	elink_cl22_read(sc, phy,
			MDIO_REG_INTR_STATUS,
			&val);

	link_up = ((legacy_status & (1<<2)) == (1<<2));

	if (link_up) {
		legacy_speed = (legacy_status & (7<<8));
		if (legacy_speed == (7<<8)) {
			vars->line_speed = ELINK_SPEED_1000;
			vars->duplex = DUPLEX_FULL;
		} else if (legacy_speed == (6<<8)) {
			vars->line_speed = ELINK_SPEED_1000;
			vars->duplex = DUPLEX_HALF;
		} else if (legacy_speed == (5<<8)) {
			vars->line_speed = ELINK_SPEED_100;
			vars->duplex = DUPLEX_FULL;
		}
		/* Omitting 100Base-T4 for now */
		else if (legacy_speed == (3<<8)) {
			vars->line_speed = ELINK_SPEED_100;
			vars->duplex = DUPLEX_HALF;
		} else if (legacy_speed == (2<<8)) {
			vars->line_speed = ELINK_SPEED_10;
			vars->duplex = DUPLEX_FULL;
		} else if (legacy_speed == (1<<8)) {
			vars->line_speed = ELINK_SPEED_10;
			vars->duplex = DUPLEX_HALF;
		} else /* Should not happen */
			vars->line_speed = 0;

		ELINK_DEBUG_P2(sc,
		   "Link is up in %dMbps, is_duplex_full= %d\n",
		   vars->line_speed,
		   (vars->duplex == DUPLEX_FULL));

		/* Check legacy speed AN resolution */
		elink_cl22_read(sc, phy,
				0x01,
				&val);
		if (val & (1<<5))
			vars->link_status |=
				LINK_STATUS_AUTO_NEGOTIATE_COMPLETE;
		elink_cl22_read(sc, phy,
				0x06,
				&val);
		if ((val & (1<<0)) == 0)
			vars->link_status |=
				LINK_STATUS_PARALLEL_DETECTION_USED;

		ELINK_DEBUG_P1(sc, "BCM54618SE: link speed is %d\n",
			   vars->line_speed);

		elink_ext_phy_resolve_fc(phy, params, vars);

		if (vars->link_status & LINK_STATUS_AUTO_NEGOTIATE_COMPLETE) {
			/* Report LP advertised speeds */
			elink_cl22_read(sc, phy, 0x5, &val);

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

			elink_cl22_read(sc, phy, 0xa, &val);
			if (val & (1<<10))
				vars->link_status |=
				  LINK_STATUS_LINK_PARTNER_1000THD_CAPABLE;
			if (val & (1<<11))
				vars->link_status |=
				  LINK_STATUS_LINK_PARTNER_1000TFD_CAPABLE;

			if ((phy->flags & ELINK_FLAGS_EEE) &&
			    elink_eee_has_cap(params))
				elink_eee_an_resolve(phy, params, vars);
		}
	}
	return link_up;
}