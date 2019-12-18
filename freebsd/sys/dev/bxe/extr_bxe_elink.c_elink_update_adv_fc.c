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
typedef  int uint32_t ;
typedef  int uint16_t ;
struct elink_vars {int dummy; } ;
struct elink_phy {int dummy; } ;
struct elink_params {struct bxe_softc* sc; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CL22_RD_OVER_CL45 (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ELINK_DEBUG_P1 (struct bxe_softc*,char*,int) ; 
 int /*<<< orphan*/  MDIO_CL73_IEEEB1_AN_ADV1 ; 
 int MDIO_CL73_IEEEB1_AN_ADV1_PAUSE_MASK ; 
 int /*<<< orphan*/  MDIO_CL73_IEEEB1_AN_LP_ADV1 ; 
 int MDIO_CL73_IEEEB1_AN_LP_ADV1_PAUSE_MASK ; 
 int /*<<< orphan*/  MDIO_COMBO_IEEE0_AUTO_NEG_ADV ; 
 int MDIO_COMBO_IEEE0_AUTO_NEG_ADV_PAUSE_MASK ; 
 int /*<<< orphan*/  MDIO_COMBO_IEEE0_AUTO_NEG_LINK_PARTNER_ABILITY1 ; 
 int MDIO_GP_STATUS_TOP_AN_STATUS1_CL73_AUTONEG_COMPLETE ; 
 int MDIO_GP_STATUS_TOP_AN_STATUS1_CL73_MR_LP_NP_AN_ABLE ; 
 int /*<<< orphan*/  MDIO_REG_BANK_CL73_IEEEB1 ; 
 int /*<<< orphan*/  MDIO_REG_BANK_COMBO_IEEE0 ; 
 int /*<<< orphan*/  elink_pause_resolve (struct elink_phy*,struct elink_params*,struct elink_vars*,int) ; 

__attribute__((used)) static void elink_update_adv_fc(struct elink_phy *phy,
				struct elink_params *params,
				struct elink_vars *vars,
				uint32_t gp_status)
{
	uint16_t ld_pause;   /* local driver */
	uint16_t lp_pause;   /* link partner */
	uint16_t pause_result;
	struct bxe_softc *sc = params->sc;
	if ((gp_status &
	     (MDIO_GP_STATUS_TOP_AN_STATUS1_CL73_AUTONEG_COMPLETE |
	      MDIO_GP_STATUS_TOP_AN_STATUS1_CL73_MR_LP_NP_AN_ABLE)) ==
	    (MDIO_GP_STATUS_TOP_AN_STATUS1_CL73_AUTONEG_COMPLETE |
	     MDIO_GP_STATUS_TOP_AN_STATUS1_CL73_MR_LP_NP_AN_ABLE)) {

		CL22_RD_OVER_CL45(sc, phy,
				  MDIO_REG_BANK_CL73_IEEEB1,
				  MDIO_CL73_IEEEB1_AN_ADV1,
				  &ld_pause);
		CL22_RD_OVER_CL45(sc, phy,
				  MDIO_REG_BANK_CL73_IEEEB1,
				  MDIO_CL73_IEEEB1_AN_LP_ADV1,
				  &lp_pause);
		pause_result = (ld_pause &
				MDIO_CL73_IEEEB1_AN_ADV1_PAUSE_MASK) >> 8;
		pause_result |= (lp_pause &
				 MDIO_CL73_IEEEB1_AN_LP_ADV1_PAUSE_MASK) >> 10;
		ELINK_DEBUG_P1(sc, "pause_result CL73 0x%x\n", pause_result);
	} else {
		CL22_RD_OVER_CL45(sc, phy,
				  MDIO_REG_BANK_COMBO_IEEE0,
				  MDIO_COMBO_IEEE0_AUTO_NEG_ADV,
				  &ld_pause);
		CL22_RD_OVER_CL45(sc, phy,
			MDIO_REG_BANK_COMBO_IEEE0,
			MDIO_COMBO_IEEE0_AUTO_NEG_LINK_PARTNER_ABILITY1,
			&lp_pause);
		pause_result = (ld_pause &
				MDIO_COMBO_IEEE0_AUTO_NEG_ADV_PAUSE_MASK)>>5;
		pause_result |= (lp_pause &
				 MDIO_COMBO_IEEE0_AUTO_NEG_ADV_PAUSE_MASK)>>7;
		ELINK_DEBUG_P1(sc, "pause_result CL37 0x%x\n", pause_result);
	}
	elink_pause_resolve(phy, params, vars, pause_result);

}