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
struct elink_vars {int duplex; int link_status; int flow_ctrl; } ;
struct elink_phy {scalar_t__ req_line_speed; } ;
struct elink_params {struct bxe_softc* sc; } ;
struct bxe_softc {int dummy; } ;
typedef  scalar_t__ elink_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  CL22_RD_OVER_CL45 (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int DUPLEX_FULL ; 
 int DUPLEX_HALF ; 
 int /*<<< orphan*/  ELINK_DEBUG_P1 (struct bxe_softc*,char*,int) ; 
 int /*<<< orphan*/  ELINK_DEBUG_P3 (struct bxe_softc*,char*,int,int,int) ; 
 int ELINK_GP_STATUS_SPEED_MASK ; 
 scalar_t__ ELINK_SINGLE_MEDIA_DIRECT (struct elink_params*) ; 
 scalar_t__ ELINK_SPEED_AUTO_NEG ; 
 scalar_t__ ELINK_STATUS_ERROR ; 
 scalar_t__ ELINK_STATUS_OK ; 
 int LINK_STATUS_AUTO_NEGOTIATE_COMPLETE ; 
 int LINK_STATUS_LINK_PARTNER_1000TFD_CAPABLE ; 
 int LINK_STATUS_LINK_PARTNER_10GXFD_CAPABLE ; 
 int LINK_STATUS_LINK_PARTNER_2500XFD_CAPABLE ; 
 int MDIO_CL73_IEEEB1_AN_ADV2_ADVR_1000M_KX ; 
 int MDIO_CL73_IEEEB1_AN_ADV2_ADVR_10G_KR ; 
 int MDIO_CL73_IEEEB1_AN_ADV2_ADVR_10G_KX4 ; 
 int /*<<< orphan*/  MDIO_CL73_IEEEB1_AN_LP_ADV2 ; 
 int /*<<< orphan*/  MDIO_GP_STATUS_TOP_AN_STATUS1 ; 
 int MDIO_GP_STATUS_TOP_AN_STATUS1_DUPLEX_STATUS ; 
 int MDIO_GP_STATUS_TOP_AN_STATUS1_LINK_STATUS ; 
 int /*<<< orphan*/  MDIO_OVER_1G_LP_UP1 ; 
 int MDIO_OVER_1G_UP1_10G ; 
 int MDIO_OVER_1G_UP1_10GH ; 
 int MDIO_OVER_1G_UP1_2_5G ; 
 int /*<<< orphan*/  MDIO_REG_BANK_CL73_IEEEB1 ; 
 int /*<<< orphan*/  MDIO_REG_BANK_GP_STATUS ; 
 int /*<<< orphan*/  MDIO_REG_BANK_OVER_1G ; 
 int /*<<< orphan*/  elink_check_fallback_to_cl37 (struct elink_phy*,struct elink_params*) ; 
 int /*<<< orphan*/  elink_flow_ctrl_resolve (struct elink_phy*,struct elink_params*,struct elink_vars*,int) ; 
 scalar_t__ elink_get_link_speed_duplex (struct elink_phy*,struct elink_params*,struct elink_vars*,int,int,int) ; 
 int /*<<< orphan*/  elink_xgxs_an_resolve (struct elink_phy*,struct elink_params*,struct elink_vars*,int) ; 

__attribute__((used)) static elink_status_t elink_link_settings_status(struct elink_phy *phy,
				      struct elink_params *params,
				      struct elink_vars *vars)
{
	struct bxe_softc *sc = params->sc;

	uint16_t gp_status, duplex = DUPLEX_HALF, link_up = 0, speed_mask;
	elink_status_t rc = ELINK_STATUS_OK;

	/* Read gp_status */
	CL22_RD_OVER_CL45(sc, phy,
			  MDIO_REG_BANK_GP_STATUS,
			  MDIO_GP_STATUS_TOP_AN_STATUS1,
			  &gp_status);
	if (gp_status & MDIO_GP_STATUS_TOP_AN_STATUS1_DUPLEX_STATUS) {
		duplex = DUPLEX_FULL;
		ELINK_DEBUG_P1(sc, "duplex status read from phy is = %x\n",
				duplex);
	} else {
		ELINK_DEBUG_P1(sc, "phy status does not allow interface to be FULL_DUPLEX : %x\n",
			gp_status);
	}		


	if (gp_status & MDIO_GP_STATUS_TOP_AN_STATUS1_LINK_STATUS)
		link_up = 1;
	speed_mask = gp_status & ELINK_GP_STATUS_SPEED_MASK;
	ELINK_DEBUG_P3(sc, "gp_status 0x%x, is_link_up %d, speed_mask 0x%x\n",
		       gp_status, link_up, speed_mask);
	rc = elink_get_link_speed_duplex(phy, params, vars, link_up, speed_mask,
					 duplex);
	if (rc == ELINK_STATUS_ERROR)
		return rc;

	if (gp_status & MDIO_GP_STATUS_TOP_AN_STATUS1_LINK_STATUS) {
		if (ELINK_SINGLE_MEDIA_DIRECT(params)) {
			vars->duplex = duplex;
			elink_flow_ctrl_resolve(phy, params, vars, gp_status);
			if (phy->req_line_speed == ELINK_SPEED_AUTO_NEG)
				elink_xgxs_an_resolve(phy, params, vars,
						      gp_status);
		}
	} else { /* Link_down */
		if ((phy->req_line_speed == ELINK_SPEED_AUTO_NEG) &&
		    ELINK_SINGLE_MEDIA_DIRECT(params)) {
			/* Check signal is detected */
			elink_check_fallback_to_cl37(phy, params);
		}
	}

	/* Read LP advertised speeds*/
	if (ELINK_SINGLE_MEDIA_DIRECT(params) &&
	    (vars->link_status & LINK_STATUS_AUTO_NEGOTIATE_COMPLETE)) {
		uint16_t val;

		CL22_RD_OVER_CL45(sc, phy, MDIO_REG_BANK_CL73_IEEEB1,
				  MDIO_CL73_IEEEB1_AN_LP_ADV2, &val);

		if (val & MDIO_CL73_IEEEB1_AN_ADV2_ADVR_1000M_KX)
			vars->link_status |=
				LINK_STATUS_LINK_PARTNER_1000TFD_CAPABLE;
		if (val & (MDIO_CL73_IEEEB1_AN_ADV2_ADVR_10G_KX4 |
			   MDIO_CL73_IEEEB1_AN_ADV2_ADVR_10G_KR))
			vars->link_status |=
				LINK_STATUS_LINK_PARTNER_10GXFD_CAPABLE;

		CL22_RD_OVER_CL45(sc, phy, MDIO_REG_BANK_OVER_1G,
				  MDIO_OVER_1G_LP_UP1, &val);

		if (val & MDIO_OVER_1G_UP1_2_5G)
			vars->link_status |=
				LINK_STATUS_LINK_PARTNER_2500XFD_CAPABLE;
		if (val & (MDIO_OVER_1G_UP1_10G | MDIO_OVER_1G_UP1_10GH))
			vars->link_status |=
				LINK_STATUS_LINK_PARTNER_10GXFD_CAPABLE;
	}

	ELINK_DEBUG_P3(sc, "duplex %x  flow_ctrl 0x%x link_status 0x%x\n",
		   vars->duplex, vars->flow_ctrl, vars->link_status);
	return rc;
}