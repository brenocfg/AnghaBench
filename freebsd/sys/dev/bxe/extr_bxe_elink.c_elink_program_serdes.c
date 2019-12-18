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
struct elink_vars {scalar_t__ line_speed; } ;
struct elink_phy {scalar_t__ req_duplex; } ;
struct elink_params {struct bxe_softc* sc; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CL22_RD_OVER_CL45 (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  CL22_WR_OVER_CL45 (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ DUPLEX_FULL ; 
 int /*<<< orphan*/  ELINK_DEBUG_P1 (struct bxe_softc*,char*,int) ; 
 scalar_t__ ELINK_SPEED_10 ; 
 scalar_t__ ELINK_SPEED_100 ; 
 scalar_t__ ELINK_SPEED_1000 ; 
 scalar_t__ ELINK_SPEED_10000 ; 
 int /*<<< orphan*/  MDIO_COMBO_IEEE0_MII_CONTROL ; 
 int MDIO_COMBO_IEEO_MII_CONTROL_AN_EN ; 
 int MDIO_COMBO_IEEO_MII_CONTROL_FULL_DUPLEX ; 
 int MDIO_COMBO_IEEO_MII_CONTROL_MAN_SGMII_SP_MASK ; 
 int /*<<< orphan*/  MDIO_REG_BANK_COMBO_IEEE0 ; 
 int /*<<< orphan*/  MDIO_REG_BANK_SERDES_DIGITAL ; 
 int /*<<< orphan*/  MDIO_SERDES_DIGITAL_MISC1 ; 
 int MDIO_SERDES_DIGITAL_MISC1_FORCE_SPEED_10G_CX4 ; 
 int MDIO_SERDES_DIGITAL_MISC1_FORCE_SPEED_MASK ; 
 int MDIO_SERDES_DIGITAL_MISC1_FORCE_SPEED_SEL ; 
 int MDIO_SERDES_DIGITAL_MISC1_REFCLK_SEL_156_25M ; 

__attribute__((used)) static void elink_program_serdes(struct elink_phy *phy,
				 struct elink_params *params,
				 struct elink_vars *vars)
{
	struct bxe_softc *sc = params->sc;
	uint16_t reg_val;

	/* Program duplex, disable autoneg and sgmii*/
	CL22_RD_OVER_CL45(sc, phy,
			  MDIO_REG_BANK_COMBO_IEEE0,
			  MDIO_COMBO_IEEE0_MII_CONTROL, &reg_val);
	reg_val &= ~(MDIO_COMBO_IEEO_MII_CONTROL_FULL_DUPLEX |
		     MDIO_COMBO_IEEO_MII_CONTROL_AN_EN |
		     MDIO_COMBO_IEEO_MII_CONTROL_MAN_SGMII_SP_MASK);
	if (phy->req_duplex == DUPLEX_FULL)
		reg_val |= MDIO_COMBO_IEEO_MII_CONTROL_FULL_DUPLEX;
	CL22_WR_OVER_CL45(sc, phy,
			  MDIO_REG_BANK_COMBO_IEEE0,
			  MDIO_COMBO_IEEE0_MII_CONTROL, reg_val);

	/* Program speed
	 *  - needed only if the speed is greater than 1G (2.5G or 10G)
	 */
	CL22_RD_OVER_CL45(sc, phy,
			  MDIO_REG_BANK_SERDES_DIGITAL,
			  MDIO_SERDES_DIGITAL_MISC1, &reg_val);
	/* Clearing the speed value before setting the right speed */
	ELINK_DEBUG_P1(sc, "MDIO_REG_BANK_SERDES_DIGITAL = 0x%x\n", reg_val);

	reg_val &= ~(MDIO_SERDES_DIGITAL_MISC1_FORCE_SPEED_MASK |
		     MDIO_SERDES_DIGITAL_MISC1_FORCE_SPEED_SEL);

	if (!((vars->line_speed == ELINK_SPEED_1000) ||
	      (vars->line_speed == ELINK_SPEED_100) ||
	      (vars->line_speed == ELINK_SPEED_10))) {

		reg_val |= (MDIO_SERDES_DIGITAL_MISC1_REFCLK_SEL_156_25M |
			    MDIO_SERDES_DIGITAL_MISC1_FORCE_SPEED_SEL);
		if (vars->line_speed == ELINK_SPEED_10000)
			reg_val |=
				MDIO_SERDES_DIGITAL_MISC1_FORCE_SPEED_10G_CX4;
	}

	CL22_WR_OVER_CL45(sc, phy,
			  MDIO_REG_BANK_SERDES_DIGITAL,
			  MDIO_SERDES_DIGITAL_MISC1, reg_val);

}