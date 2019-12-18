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
struct elink_vars {int dummy; } ;
struct elink_phy {scalar_t__ type; } ;
struct elink_params {struct bxe_softc* sc; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 scalar_t__ CHIP_IS_E3 (struct bxe_softc*) ; 
 int /*<<< orphan*/  ELINK_DEBUG_P1 (struct bxe_softc*,char*,int) ; 
 scalar_t__ ELINK_SINGLE_MEDIA_DIRECT (struct elink_params*) ; 
 int /*<<< orphan*/  MDIO_AN_DEVAD ; 
 int /*<<< orphan*/  MDIO_AN_REG_ADV_PAUSE ; 
 int MDIO_AN_REG_ADV_PAUSE_MASK ; 
 int /*<<< orphan*/  MDIO_AN_REG_CL37_FC_LD ; 
 int /*<<< orphan*/  MDIO_AN_REG_CL37_FC_LP ; 
 int /*<<< orphan*/  MDIO_AN_REG_LP_AUTO_NEG ; 
 int MDIO_COMBO_IEEE0_AUTO_NEG_ADV_PAUSE_BOTH ; 
 int /*<<< orphan*/  MDIO_WC_REG_GP2_STATUS_GP_2_4 ; 
 int MDIO_WC_REG_GP2_STATUS_GP_2_4_CL37_LP_AN_CAP ; 
 int MDIO_WC_REG_GP2_STATUS_GP_2_4_CL73_AN_CMPL ; 
 scalar_t__ PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM54618SE ; 
 int /*<<< orphan*/  elink_cl22_read (struct bxe_softc*,struct elink_phy*,int,int*) ; 
 int /*<<< orphan*/  elink_cl45_read (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int elink_get_warpcore_lane (struct elink_phy*,struct elink_params*) ; 
 int /*<<< orphan*/  elink_pause_resolve (struct elink_phy*,struct elink_params*,struct elink_vars*,int) ; 

__attribute__((used)) static void elink_ext_phy_update_adv_fc(struct elink_phy *phy,
					struct elink_params *params,
					struct elink_vars *vars)
{
	uint16_t ld_pause;		/* local */
	uint16_t lp_pause;		/* link partner */
	uint16_t pause_result;
	struct bxe_softc *sc = params->sc;
	if (phy->type == PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM54618SE) {
		elink_cl22_read(sc, phy, 0x4, &ld_pause);
		elink_cl22_read(sc, phy, 0x5, &lp_pause);
	} else if (CHIP_IS_E3(sc) &&
		ELINK_SINGLE_MEDIA_DIRECT(params)) {
		uint8_t lane = elink_get_warpcore_lane(phy, params);
		uint16_t gp_status, gp_mask;
		elink_cl45_read(sc, phy,
				MDIO_AN_DEVAD, MDIO_WC_REG_GP2_STATUS_GP_2_4,
				&gp_status);
		gp_mask = (MDIO_WC_REG_GP2_STATUS_GP_2_4_CL73_AN_CMPL |
			   MDIO_WC_REG_GP2_STATUS_GP_2_4_CL37_LP_AN_CAP) <<
			lane;
		if ((gp_status & gp_mask) == gp_mask) {
			elink_cl45_read(sc, phy, MDIO_AN_DEVAD,
					MDIO_AN_REG_ADV_PAUSE, &ld_pause);
			elink_cl45_read(sc, phy, MDIO_AN_DEVAD,
					MDIO_AN_REG_LP_AUTO_NEG, &lp_pause);
		} else {
			elink_cl45_read(sc, phy, MDIO_AN_DEVAD,
					MDIO_AN_REG_CL37_FC_LD, &ld_pause);
			elink_cl45_read(sc, phy, MDIO_AN_DEVAD,
					MDIO_AN_REG_CL37_FC_LP, &lp_pause);
			ld_pause = ((ld_pause &
				     MDIO_COMBO_IEEE0_AUTO_NEG_ADV_PAUSE_BOTH)
				    << 3);
			lp_pause = ((lp_pause &
				     MDIO_COMBO_IEEE0_AUTO_NEG_ADV_PAUSE_BOTH)
				    << 3);
		}
	} else {
		elink_cl45_read(sc, phy,
				MDIO_AN_DEVAD,
				MDIO_AN_REG_ADV_PAUSE, &ld_pause);
		elink_cl45_read(sc, phy,
				MDIO_AN_DEVAD,
				MDIO_AN_REG_LP_AUTO_NEG, &lp_pause);
	}
	pause_result = (ld_pause &
			MDIO_AN_REG_ADV_PAUSE_MASK) >> 8;
	pause_result |= (lp_pause &
			 MDIO_AN_REG_ADV_PAUSE_MASK) >> 10;
	ELINK_DEBUG_P1(sc, "Ext PHY pause result 0x%x\n", pause_result);
	elink_pause_resolve(phy, params, vars, pause_result);

}