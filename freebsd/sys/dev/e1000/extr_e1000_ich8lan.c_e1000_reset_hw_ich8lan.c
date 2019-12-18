#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_8__ {scalar_t__ type; } ;
struct TYPE_6__ {scalar_t__ (* get_cfg_done ) (struct e1000_hw*) ;int /*<<< orphan*/  (* check_reset_block ) (struct e1000_hw*) ;} ;
struct TYPE_7__ {TYPE_2__ ops; } ;
struct e1000_dev_spec_ich8lan {int /*<<< orphan*/  nvm_k1_enabled; } ;
struct TYPE_5__ {struct e1000_dev_spec_ich8lan ich8lan; } ;
struct e1000_hw {TYPE_4__ mac; TYPE_3__ phy; TYPE_1__ dev_spec; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  DEBUGOUT (char*) ; 
 int /*<<< orphan*/  E1000_CRC_OFFSET ; 
 int /*<<< orphan*/  E1000_CTRL ; 
 int E1000_CTRL_PHY_RST ; 
 int E1000_CTRL_RST ; 
 int /*<<< orphan*/  E1000_FEXTNVM3 ; 
 int E1000_FEXTNVM3_PHY_CFG_COUNTER_50MSEC ; 
 int E1000_FEXTNVM3_PHY_CFG_COUNTER_MASK ; 
 int /*<<< orphan*/  E1000_FWSM ; 
 int E1000_ICH_FWSM_FW_VALID ; 
 int /*<<< orphan*/  E1000_ICR ; 
 int /*<<< orphan*/  E1000_IMC ; 
 int /*<<< orphan*/  E1000_KABGTXD ; 
 int E1000_KABGTXD_BGSQLBIAS ; 
 int /*<<< orphan*/  E1000_NVM_K1_CONFIG ; 
 int E1000_NVM_K1_ENABLE ; 
 int /*<<< orphan*/  E1000_PBA ; 
 int E1000_PBA_8K ; 
 int /*<<< orphan*/  E1000_PBS ; 
 int E1000_PBS_16K ; 
 int /*<<< orphan*/  E1000_RCTL ; 
 int E1000_READ_REG (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 scalar_t__ E1000_SUCCESS ; 
 int /*<<< orphan*/  E1000_TCTL ; 
 int E1000_TCTL_PSP ; 
 int /*<<< orphan*/  E1000_WRITE_FLUSH (struct e1000_hw*) ; 
 int /*<<< orphan*/  E1000_WRITE_REG (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ e1000_acquire_swflag_ich8lan (struct e1000_hw*) ; 
 scalar_t__ e1000_disable_pcie_master_generic (struct e1000_hw*) ; 
 int /*<<< orphan*/  e1000_gate_hw_phy_config_ich8lan (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 scalar_t__ e1000_ich8lan ; 
 scalar_t__ e1000_pch2lan ; 
 scalar_t__ e1000_pchlan ; 
 scalar_t__ e1000_post_phy_reset_ich8lan (struct e1000_hw*) ; 
 scalar_t__ e1000_read_nvm (struct e1000_hw*,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  msec_delay (int) ; 
 int /*<<< orphan*/  stub1 (struct e1000_hw*) ; 
 scalar_t__ stub2 (struct e1000_hw*) ; 

__attribute__((used)) static s32 e1000_reset_hw_ich8lan(struct e1000_hw *hw)
{
	struct e1000_dev_spec_ich8lan *dev_spec = &hw->dev_spec.ich8lan;
	u16 kum_cfg;
	u32 ctrl, reg;
	s32 ret_val;

	DEBUGFUNC("e1000_reset_hw_ich8lan");

	/* Prevent the PCI-E bus from sticking if there is no TLP connection
	 * on the last TLP read/write transaction when MAC is reset.
	 */
	ret_val = e1000_disable_pcie_master_generic(hw);
	if (ret_val)
		DEBUGOUT("PCI-E Master disable polling has failed.\n");

	DEBUGOUT("Masking off all interrupts\n");
	E1000_WRITE_REG(hw, E1000_IMC, 0xffffffff);

	/* Disable the Transmit and Receive units.  Then delay to allow
	 * any pending transactions to complete before we hit the MAC
	 * with the global reset.
	 */
	E1000_WRITE_REG(hw, E1000_RCTL, 0);
	E1000_WRITE_REG(hw, E1000_TCTL, E1000_TCTL_PSP);
	E1000_WRITE_FLUSH(hw);

	msec_delay(10);

	/* Workaround for ICH8 bit corruption issue in FIFO memory */
	if (hw->mac.type == e1000_ich8lan) {
		/* Set Tx and Rx buffer allocation to 8k apiece. */
		E1000_WRITE_REG(hw, E1000_PBA, E1000_PBA_8K);
		/* Set Packet Buffer Size to 16k. */
		E1000_WRITE_REG(hw, E1000_PBS, E1000_PBS_16K);
	}

	if (hw->mac.type == e1000_pchlan) {
		/* Save the NVM K1 bit setting*/
		ret_val = e1000_read_nvm(hw, E1000_NVM_K1_CONFIG, 1, &kum_cfg);
		if (ret_val)
			return ret_val;

		if (kum_cfg & E1000_NVM_K1_ENABLE)
			dev_spec->nvm_k1_enabled = TRUE;
		else
			dev_spec->nvm_k1_enabled = FALSE;
	}

	ctrl = E1000_READ_REG(hw, E1000_CTRL);

	if (!hw->phy.ops.check_reset_block(hw)) {
		/* Full-chip reset requires MAC and PHY reset at the same
		 * time to make sure the interface between MAC and the
		 * external PHY is reset.
		 */
		ctrl |= E1000_CTRL_PHY_RST;

		/* Gate automatic PHY configuration by hardware on
		 * non-managed 82579
		 */
		if ((hw->mac.type == e1000_pch2lan) &&
		    !(E1000_READ_REG(hw, E1000_FWSM) & E1000_ICH_FWSM_FW_VALID))
			e1000_gate_hw_phy_config_ich8lan(hw, TRUE);
	}
	ret_val = e1000_acquire_swflag_ich8lan(hw);
	DEBUGOUT("Issuing a global reset to ich8lan\n");
	E1000_WRITE_REG(hw, E1000_CTRL, (ctrl | E1000_CTRL_RST));
	/* cannot issue a flush here because it hangs the hardware */
	msec_delay(20);

	/* Set Phy Config Counter to 50msec */
	if (hw->mac.type == e1000_pch2lan) {
		reg = E1000_READ_REG(hw, E1000_FEXTNVM3);
		reg &= ~E1000_FEXTNVM3_PHY_CFG_COUNTER_MASK;
		reg |= E1000_FEXTNVM3_PHY_CFG_COUNTER_50MSEC;
		E1000_WRITE_REG(hw, E1000_FEXTNVM3, reg);
	}


	if (ctrl & E1000_CTRL_PHY_RST) {
		ret_val = hw->phy.ops.get_cfg_done(hw);
		if (ret_val)
			return ret_val;

		ret_val = e1000_post_phy_reset_ich8lan(hw);
		if (ret_val)
			return ret_val;
	}

	/* For PCH, this write will make sure that any noise
	 * will be detected as a CRC error and be dropped rather than show up
	 * as a bad packet to the DMA engine.
	 */
	if (hw->mac.type == e1000_pchlan)
		E1000_WRITE_REG(hw, E1000_CRC_OFFSET, 0x65656565);

	E1000_WRITE_REG(hw, E1000_IMC, 0xffffffff);
	E1000_READ_REG(hw, E1000_ICR);

	reg = E1000_READ_REG(hw, E1000_KABGTXD);
	reg |= E1000_KABGTXD_BGSQLBIAS;
	E1000_WRITE_REG(hw, E1000_KABGTXD, reg);

	return E1000_SUCCESS;
}