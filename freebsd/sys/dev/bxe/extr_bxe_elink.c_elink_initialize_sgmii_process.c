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
struct elink_vars {int line_speed; } ;
struct elink_phy {scalar_t__ req_duplex; } ;
struct elink_params {struct bxe_softc* sc; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CL22_RD_OVER_CL45 (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  CL22_WR_OVER_CL45 (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ DUPLEX_FULL ; 
 int /*<<< orphan*/  ELINK_DEBUG_P1 (struct bxe_softc*,char*,int) ; 
#define  ELINK_SPEED_10 130 
#define  ELINK_SPEED_100 129 
#define  ELINK_SPEED_1000 128 
 int ELINK_SPEED_AUTO_NEG ; 
 int /*<<< orphan*/  MDIO_COMBO_IEEE0_MII_CONTROL ; 
 int MDIO_COMBO_IEEO_MII_CONTROL_AN_EN ; 
 int MDIO_COMBO_IEEO_MII_CONTROL_FULL_DUPLEX ; 
 int MDIO_COMBO_IEEO_MII_CONTROL_MAN_SGMII_SP_100 ; 
 int MDIO_COMBO_IEEO_MII_CONTROL_MAN_SGMII_SP_1000 ; 
 int MDIO_COMBO_IEEO_MII_CONTROL_MAN_SGMII_SP_MASK ; 
 int /*<<< orphan*/  MDIO_REG_BANK_COMBO_IEEE0 ; 
 int /*<<< orphan*/  MDIO_REG_BANK_SERDES_DIGITAL ; 
 int /*<<< orphan*/  MDIO_SERDES_DIGITAL_A_1000X_CONTROL1 ; 
 int MDIO_SERDES_DIGITAL_A_1000X_CONTROL1_AUTODET ; 
 int MDIO_SERDES_DIGITAL_A_1000X_CONTROL1_FIBER_MODE ; 
 int MDIO_SERDES_DIGITAL_A_1000X_CONTROL1_INVERT_SIGNAL_DETECT ; 
 int MDIO_SERDES_DIGITAL_A_1000X_CONTROL1_MSTR_MODE ; 
 int /*<<< orphan*/  elink_restart_autoneg (struct elink_phy*,struct elink_params*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void elink_initialize_sgmii_process(struct elink_phy *phy,
					   struct elink_params *params,
					   struct elink_vars *vars)
{
	struct bxe_softc *sc = params->sc;
	uint16_t control1;

	/* In SGMII mode, the unicore is always slave */

	CL22_RD_OVER_CL45(sc, phy,
			  MDIO_REG_BANK_SERDES_DIGITAL,
			  MDIO_SERDES_DIGITAL_A_1000X_CONTROL1,
			  &control1);
	control1 |= MDIO_SERDES_DIGITAL_A_1000X_CONTROL1_INVERT_SIGNAL_DETECT;
	/* Set sgmii mode (and not fiber) */
	control1 &= ~(MDIO_SERDES_DIGITAL_A_1000X_CONTROL1_FIBER_MODE |
		      MDIO_SERDES_DIGITAL_A_1000X_CONTROL1_AUTODET |
		      MDIO_SERDES_DIGITAL_A_1000X_CONTROL1_MSTR_MODE);
	CL22_WR_OVER_CL45(sc, phy,
			  MDIO_REG_BANK_SERDES_DIGITAL,
			  MDIO_SERDES_DIGITAL_A_1000X_CONTROL1,
			  control1);

	/* If forced speed */
	if (!(vars->line_speed == ELINK_SPEED_AUTO_NEG)) {
		/* Set speed, disable autoneg */
		uint16_t mii_control;

		CL22_RD_OVER_CL45(sc, phy,
				  MDIO_REG_BANK_COMBO_IEEE0,
				  MDIO_COMBO_IEEE0_MII_CONTROL,
				  &mii_control);
		mii_control &= ~(MDIO_COMBO_IEEO_MII_CONTROL_AN_EN |
				 MDIO_COMBO_IEEO_MII_CONTROL_MAN_SGMII_SP_MASK|
				 MDIO_COMBO_IEEO_MII_CONTROL_FULL_DUPLEX);

		switch (vars->line_speed) {
		case ELINK_SPEED_100:
			mii_control |=
				MDIO_COMBO_IEEO_MII_CONTROL_MAN_SGMII_SP_100;
			break;
		case ELINK_SPEED_1000:
			mii_control |=
				MDIO_COMBO_IEEO_MII_CONTROL_MAN_SGMII_SP_1000;
			break;
		case ELINK_SPEED_10:
			/* There is nothing to set for 10M */
			break;
		default:
			/* Invalid speed for SGMII */
			ELINK_DEBUG_P1(sc, "Invalid line_speed 0x%x\n",
				  vars->line_speed);
			break;
		}

		/* Setting the full duplex */
		if (phy->req_duplex == DUPLEX_FULL)
			mii_control |=
				MDIO_COMBO_IEEO_MII_CONTROL_FULL_DUPLEX;
		CL22_WR_OVER_CL45(sc, phy,
				  MDIO_REG_BANK_COMBO_IEEE0,
				  MDIO_COMBO_IEEE0_MII_CONTROL,
				  mii_control);

	} else { /* AN mode */
		/* Enable and restart AN */
		elink_restart_autoneg(phy, params, 0);
	}
}