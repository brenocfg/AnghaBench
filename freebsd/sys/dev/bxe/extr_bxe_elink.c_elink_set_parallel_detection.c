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
struct elink_phy {int speed_cap_mask; scalar_t__ type; } ;
struct elink_params {struct bxe_softc* sc; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CL22_RD_OVER_CL45 (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  CL22_WR_OVER_CL45 (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ELINK_DEBUG_P0 (struct bxe_softc*,char*) ; 
 int /*<<< orphan*/  ELINK_DEBUG_P2 (struct bxe_softc*,char*,int,int) ; 
 int /*<<< orphan*/  MDIO_10G_PARALLEL_DETECT_PAR_DET_10G_CONTROL ; 
 int MDIO_10G_PARALLEL_DETECT_PAR_DET_10G_CONTROL_PARDET10G_EN ; 
 int /*<<< orphan*/  MDIO_10G_PARALLEL_DETECT_PAR_DET_10G_LINK ; 
 int MDIO_10G_PARALLEL_DETECT_PAR_DET_10G_LINK_CNT ; 
 int /*<<< orphan*/  MDIO_REG_BANK_10G_PARALLEL_DETECT ; 
 int /*<<< orphan*/  MDIO_REG_BANK_SERDES_DIGITAL ; 
 int /*<<< orphan*/  MDIO_REG_BANK_XGXS_BLOCK2 ; 
 int /*<<< orphan*/  MDIO_SERDES_DIGITAL_A_1000X_CONTROL2 ; 
 int MDIO_SERDES_DIGITAL_A_1000X_CONTROL2_PRL_DT_EN ; 
 int /*<<< orphan*/  MDIO_XGXS_BLOCK2_UNICORE_MODE_10G ; 
 int MDIO_XGXS_BLOCK2_UNICORE_MODE_10G_CX4_XGXS ; 
 int MDIO_XGXS_BLOCK2_UNICORE_MODE_10G_HIGIG_XGXS ; 
 int PORT_HW_CFG_SPEED_CAPABILITY_D0_10G ; 
 int PORT_HW_CFG_SPEED_CAPABILITY_D0_1G ; 
 scalar_t__ PORT_HW_CFG_XGXS_EXT_PHY_TYPE_DIRECT ; 

__attribute__((used)) static void elink_set_parallel_detection(struct elink_phy *phy,
					 struct elink_params *params)
{
	struct bxe_softc *sc = params->sc;
	uint16_t control2;
	CL22_RD_OVER_CL45(sc, phy,
			  MDIO_REG_BANK_SERDES_DIGITAL,
			  MDIO_SERDES_DIGITAL_A_1000X_CONTROL2,
			  &control2);
	if (phy->speed_cap_mask & PORT_HW_CFG_SPEED_CAPABILITY_D0_1G)
		control2 |= MDIO_SERDES_DIGITAL_A_1000X_CONTROL2_PRL_DT_EN;
	else
		control2 &= ~MDIO_SERDES_DIGITAL_A_1000X_CONTROL2_PRL_DT_EN;
	ELINK_DEBUG_P2(sc, "phy->speed_cap_mask = 0x%x, control2 = 0x%x\n",
		phy->speed_cap_mask, control2);
	CL22_WR_OVER_CL45(sc, phy,
			  MDIO_REG_BANK_SERDES_DIGITAL,
			  MDIO_SERDES_DIGITAL_A_1000X_CONTROL2,
			  control2);

	if ((phy->type == PORT_HW_CFG_XGXS_EXT_PHY_TYPE_DIRECT) &&
	     (phy->speed_cap_mask &
		    PORT_HW_CFG_SPEED_CAPABILITY_D0_10G)) {
		ELINK_DEBUG_P0(sc, "XGXS\n");

		CL22_WR_OVER_CL45(sc, phy,
				 MDIO_REG_BANK_10G_PARALLEL_DETECT,
				 MDIO_10G_PARALLEL_DETECT_PAR_DET_10G_LINK,
				 MDIO_10G_PARALLEL_DETECT_PAR_DET_10G_LINK_CNT);

		CL22_RD_OVER_CL45(sc, phy,
				  MDIO_REG_BANK_10G_PARALLEL_DETECT,
				  MDIO_10G_PARALLEL_DETECT_PAR_DET_10G_CONTROL,
				  &control2);


		control2 |=
		    MDIO_10G_PARALLEL_DETECT_PAR_DET_10G_CONTROL_PARDET10G_EN;

		CL22_WR_OVER_CL45(sc, phy,
				  MDIO_REG_BANK_10G_PARALLEL_DETECT,
				  MDIO_10G_PARALLEL_DETECT_PAR_DET_10G_CONTROL,
				  control2);

		/* Disable parallel detection of HiG */
		CL22_WR_OVER_CL45(sc, phy,
				  MDIO_REG_BANK_XGXS_BLOCK2,
				  MDIO_XGXS_BLOCK2_UNICORE_MODE_10G,
				  MDIO_XGXS_BLOCK2_UNICORE_MODE_10G_CX4_XGXS |
				  MDIO_XGXS_BLOCK2_UNICORE_MODE_10G_HIGIG_XGXS);
	}
}