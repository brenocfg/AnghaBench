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
typedef  size_t u8 ;
typedef  size_t u32 ;
typedef  size_t u16 ;
struct ixgbe_hw {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 size_t IXGBE_DCB_MAX_TRAFFIC_CLASS ; 
 size_t IXGBE_DCB_MAX_USER_PRIORITY ; 
 int /*<<< orphan*/  IXGBE_RTRPCS ; 
 size_t IXGBE_RTRPCS_ARBDIS ; 
 size_t IXGBE_RTRPCS_RAC ; 
 size_t IXGBE_RTRPCS_RRM ; 
 int /*<<< orphan*/  IXGBE_RTRPT4C (size_t) ; 
 size_t IXGBE_RTRPT4C_BWG_SHIFT ; 
 size_t IXGBE_RTRPT4C_LSP ; 
 size_t IXGBE_RTRPT4C_MCL_SHIFT ; 
 int /*<<< orphan*/  IXGBE_RTRUP2TC ; 
 size_t IXGBE_RTRUP2TC_UP_SHIFT ; 
 int /*<<< orphan*/  IXGBE_SUCCESS ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,size_t) ; 
 size_t ixgbe_dcb_tsa_strict ; 

s32 ixgbe_dcb_config_rx_arbiter_82599(struct ixgbe_hw *hw, u16 *refill,
				      u16 *max, u8 *bwg_id, u8 *tsa,
				      u8 *map)
{
	u32 reg = 0;
	u32 credit_refill = 0;
	u32 credit_max = 0;
	u8  i = 0;

	/*
	 * Disable the arbiter before changing parameters
	 * (always enable recycle mode; WSP)
	 */
	reg = IXGBE_RTRPCS_RRM | IXGBE_RTRPCS_RAC | IXGBE_RTRPCS_ARBDIS;
	IXGBE_WRITE_REG(hw, IXGBE_RTRPCS, reg);

	/*
	 * map all UPs to TCs. up_to_tc_bitmap for each TC has corresponding
	 * bits sets for the UPs that needs to be mappped to that TC.
	 * e.g if priorities 6 and 7 are to be mapped to a TC then the
	 * up_to_tc_bitmap value for that TC will be 11000000 in binary.
	 */
	reg = 0;
	for (i = 0; i < IXGBE_DCB_MAX_USER_PRIORITY; i++)
		reg |= (map[i] << (i * IXGBE_RTRUP2TC_UP_SHIFT));

	IXGBE_WRITE_REG(hw, IXGBE_RTRUP2TC, reg);

	/* Configure traffic class credits and priority */
	for (i = 0; i < IXGBE_DCB_MAX_TRAFFIC_CLASS; i++) {
		credit_refill = refill[i];
		credit_max = max[i];
		reg = credit_refill | (credit_max << IXGBE_RTRPT4C_MCL_SHIFT);

		reg |= (u32)(bwg_id[i]) << IXGBE_RTRPT4C_BWG_SHIFT;

		if (tsa[i] == ixgbe_dcb_tsa_strict)
			reg |= IXGBE_RTRPT4C_LSP;

		IXGBE_WRITE_REG(hw, IXGBE_RTRPT4C(i), reg);
	}

	/*
	 * Configure Rx packet plane (recycle mode; WSP) and
	 * enable arbiter
	 */
	reg = IXGBE_RTRPCS_RRM | IXGBE_RTRPCS_RAC;
	IXGBE_WRITE_REG(hw, IXGBE_RTRPCS, reg);

	return IXGBE_SUCCESS;
}