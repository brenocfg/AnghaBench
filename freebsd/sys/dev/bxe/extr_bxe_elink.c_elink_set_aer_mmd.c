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
struct elink_phy {scalar_t__ type; int addr; int flags; } ;
struct elink_params {int lane_config; struct bxe_softc* sc; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 scalar_t__ CHIP_IS_E2 (struct bxe_softc*) ; 
 int /*<<< orphan*/  CL22_WR_OVER_CL45 (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int ELINK_FLAGS_WC_DUAL_MODE ; 
 int /*<<< orphan*/  MDIO_AER_BLOCK_AER_REG ; 
 int /*<<< orphan*/  MDIO_REG_BANK_AER_BLOCK ; 
 int PORT_HW_CFG_LANE_SWAP_CFG_MASTER_MASK ; 
 int PORT_HW_CFG_LANE_SWAP_CFG_MASTER_SHIFT ; 
 scalar_t__ PORT_HW_CFG_XGXS_EXT_PHY_TYPE_DIRECT ; 
 scalar_t__ USES_WARPCORE (struct bxe_softc*) ; 
 int elink_get_warpcore_lane (struct elink_phy*,struct elink_params*) ; 

__attribute__((used)) static void elink_set_aer_mmd(struct elink_params *params,
			      struct elink_phy *phy)
{
	uint32_t ser_lane;
	uint16_t offset, aer_val;
	struct bxe_softc *sc = params->sc;
	ser_lane = ((params->lane_config &
		     PORT_HW_CFG_LANE_SWAP_CFG_MASTER_MASK) >>
		     PORT_HW_CFG_LANE_SWAP_CFG_MASTER_SHIFT);

	offset = (phy->type == PORT_HW_CFG_XGXS_EXT_PHY_TYPE_DIRECT) ?
		(phy->addr + ser_lane) : 0;

	if (USES_WARPCORE(sc)) {
		aer_val = elink_get_warpcore_lane(phy, params);
		/* In Dual-lane mode, two lanes are joined together,
		 * so in order to configure them, the AER broadcast method is
		 * used here.
		 * 0x200 is the broadcast address for lanes 0,1
		 * 0x201 is the broadcast address for lanes 2,3
		 */
		if (phy->flags & ELINK_FLAGS_WC_DUAL_MODE)
			aer_val = (aer_val >> 1) | 0x200;
	} else if (CHIP_IS_E2(sc))
		aer_val = 0x3800 + offset - 1;
	else
		aer_val = 0x3800 + offset;

	CL22_WR_OVER_CL45(sc, phy, MDIO_REG_BANK_AER_BLOCK,
			  MDIO_AER_BLOCK_AER_REG, aer_val);

}