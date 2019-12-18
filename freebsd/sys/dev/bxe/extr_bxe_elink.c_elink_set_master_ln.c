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
struct elink_phy {int dummy; } ;
struct elink_params {int lane_config; struct bxe_softc* sc; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CL22_RD_OVER_CL45 (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  CL22_WR_OVER_CL45 (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MDIO_REG_BANK_XGXS_BLOCK2 ; 
 int /*<<< orphan*/  MDIO_XGXS_BLOCK2_TEST_MODE_LANE ; 
 int PORT_HW_CFG_LANE_SWAP_CFG_MASTER_MASK ; 
 int PORT_HW_CFG_LANE_SWAP_CFG_MASTER_SHIFT ; 

__attribute__((used)) static void elink_set_master_ln(struct elink_params *params,
				struct elink_phy *phy)
{
	struct bxe_softc *sc = params->sc;
	uint16_t new_master_ln, ser_lane;
	ser_lane = ((params->lane_config &
		     PORT_HW_CFG_LANE_SWAP_CFG_MASTER_MASK) >>
		    PORT_HW_CFG_LANE_SWAP_CFG_MASTER_SHIFT);

	/* Set the master_ln for AN */
	CL22_RD_OVER_CL45(sc, phy,
			  MDIO_REG_BANK_XGXS_BLOCK2,
			  MDIO_XGXS_BLOCK2_TEST_MODE_LANE,
			  &new_master_ln);

	CL22_WR_OVER_CL45(sc, phy,
			  MDIO_REG_BANK_XGXS_BLOCK2 ,
			  MDIO_XGXS_BLOCK2_TEST_MODE_LANE,
			  (new_master_ln | ser_lane));
}