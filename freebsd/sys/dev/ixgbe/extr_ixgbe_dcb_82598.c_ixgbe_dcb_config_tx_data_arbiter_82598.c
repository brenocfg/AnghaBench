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
typedef  int u32 ;
typedef  int u16 ;
struct ixgbe_hw {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 size_t IXGBE_DCB_MAX_TRAFFIC_CLASS ; 
 int /*<<< orphan*/  IXGBE_DTXCTL ; 
 int IXGBE_DTXCTL_ENDBUBD ; 
 int /*<<< orphan*/  IXGBE_PDPMCS ; 
 int IXGBE_PDPMCS_ARBDIS ; 
 int IXGBE_PDPMCS_TPPAC ; 
 int IXGBE_PDPMCS_TRM ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_SUCCESS ; 
 int /*<<< orphan*/  IXGBE_TDPT2TCCR (size_t) ; 
 int IXGBE_TDPT2TCCR_BWG_SHIFT ; 
 int IXGBE_TDPT2TCCR_GSP ; 
 int IXGBE_TDPT2TCCR_LSP ; 
 int IXGBE_TDPT2TCCR_MCL_SHIFT ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 
 size_t ixgbe_dcb_tsa_group_strict_cee ; 
 size_t ixgbe_dcb_tsa_strict ; 

s32 ixgbe_dcb_config_tx_data_arbiter_82598(struct ixgbe_hw *hw,
					   u16 *refill, u16 *max, u8 *bwg_id,
					   u8 *tsa)
{
	u32 reg;
	u8 i;

	reg = IXGBE_READ_REG(hw, IXGBE_PDPMCS);
	/* Enable Data Plane Arbiter */
	reg &= ~IXGBE_PDPMCS_ARBDIS;
	/* Enable DFP and Transmit Recycle Mode */
	reg |= (IXGBE_PDPMCS_TPPAC | IXGBE_PDPMCS_TRM);

	IXGBE_WRITE_REG(hw, IXGBE_PDPMCS, reg);

	/* Configure traffic class credits and priority */
	for (i = 0; i < IXGBE_DCB_MAX_TRAFFIC_CLASS; i++) {
		reg = refill[i];
		reg |= (u32)(max[i]) << IXGBE_TDPT2TCCR_MCL_SHIFT;
		reg |= (u32)(bwg_id[i]) << IXGBE_TDPT2TCCR_BWG_SHIFT;

		if (tsa[i] == ixgbe_dcb_tsa_group_strict_cee)
			reg |= IXGBE_TDPT2TCCR_GSP;

		if (tsa[i] == ixgbe_dcb_tsa_strict)
			reg |= IXGBE_TDPT2TCCR_LSP;

		IXGBE_WRITE_REG(hw, IXGBE_TDPT2TCCR(i), reg);
	}

	/* Enable Tx packet buffer division */
	reg = IXGBE_READ_REG(hw, IXGBE_DTXCTL);
	reg |= IXGBE_DTXCTL_ENDBUBD;
	IXGBE_WRITE_REG(hw, IXGBE_DTXCTL, reg);

	return IXGBE_SUCCESS;
}