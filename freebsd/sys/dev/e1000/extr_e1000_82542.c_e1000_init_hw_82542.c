#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct TYPE_5__ {int /*<<< orphan*/  (* clear_vfta ) (struct e1000_hw*) ;} ;
struct e1000_mac_info {scalar_t__ mta_reg_count; int /*<<< orphan*/  rar_entry_count; TYPE_2__ ops; } ;
struct TYPE_6__ {int pci_cmd_word; } ;
struct e1000_dev_spec_82542 {scalar_t__ dma_fairness; } ;
struct TYPE_4__ {struct e1000_dev_spec_82542 _82542; } ;
struct e1000_hw {scalar_t__ revision_id; TYPE_3__ bus; TYPE_1__ dev_spec; struct e1000_mac_info mac; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int CMD_MEM_WRT_INVALIDATE ; 
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  DEBUGOUT (char*) ; 
 int /*<<< orphan*/  E1000_CTRL ; 
 int E1000_CTRL_PRIOR ; 
 int /*<<< orphan*/  E1000_MTA ; 
 int /*<<< orphan*/  E1000_RCTL ; 
 int E1000_RCTL_RST ; 
 int E1000_READ_REG (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 scalar_t__ E1000_REVISION_2 ; 
 int /*<<< orphan*/  E1000_SUCCESS ; 
 int /*<<< orphan*/  E1000_VET ; 
 int /*<<< orphan*/  E1000_WRITE_FLUSH (struct e1000_hw*) ; 
 int /*<<< orphan*/  E1000_WRITE_REG (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  E1000_WRITE_REG_ARRAY (struct e1000_hw*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e1000_clear_hw_cntrs_82542 (struct e1000_hw*) ; 
 int /*<<< orphan*/  e1000_init_rx_addrs_generic (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e1000_pci_clear_mwi (struct e1000_hw*) ; 
 int /*<<< orphan*/  e1000_pci_set_mwi (struct e1000_hw*) ; 
 int /*<<< orphan*/  e1000_setup_link_82542 (struct e1000_hw*) ; 
 int /*<<< orphan*/  msec_delay (int) ; 
 int /*<<< orphan*/  stub1 (struct e1000_hw*) ; 

__attribute__((used)) static s32 e1000_init_hw_82542(struct e1000_hw *hw)
{
	struct e1000_mac_info *mac = &hw->mac;
	struct e1000_dev_spec_82542 *dev_spec = &hw->dev_spec._82542;
	s32 ret_val = E1000_SUCCESS;
	u32 ctrl;
	u16 i;

	DEBUGFUNC("e1000_init_hw_82542");

	/* Disabling VLAN filtering */
	E1000_WRITE_REG(hw, E1000_VET, 0);
	mac->ops.clear_vfta(hw);

	/* For 82542 (rev 2.0), disable MWI and put the receiver into reset */
	if (hw->revision_id == E1000_REVISION_2) {
		DEBUGOUT("Disabling MWI on 82542 rev 2.0\n");
		e1000_pci_clear_mwi(hw);
		E1000_WRITE_REG(hw, E1000_RCTL, E1000_RCTL_RST);
		E1000_WRITE_FLUSH(hw);
		msec_delay(5);
	}

	/* Setup the receive address. */
	e1000_init_rx_addrs_generic(hw, mac->rar_entry_count);

	/* For 82542 (rev 2.0), take the receiver out of reset and enable MWI */
	if (hw->revision_id == E1000_REVISION_2) {
		E1000_WRITE_REG(hw, E1000_RCTL, 0);
		E1000_WRITE_FLUSH(hw);
		msec_delay(1);
		if (hw->bus.pci_cmd_word & CMD_MEM_WRT_INVALIDATE)
			e1000_pci_set_mwi(hw);
	}

	/* Zero out the Multicast HASH table */
	DEBUGOUT("Zeroing the MTA\n");
	for (i = 0; i < mac->mta_reg_count; i++)
		E1000_WRITE_REG_ARRAY(hw, E1000_MTA, i, 0);

	/*
	 * Set the PCI priority bit correctly in the CTRL register.  This
	 * determines if the adapter gives priority to receives, or if it
	 * gives equal priority to transmits and receives.
	 */
	if (dev_spec->dma_fairness) {
		ctrl = E1000_READ_REG(hw, E1000_CTRL);
		E1000_WRITE_REG(hw, E1000_CTRL, ctrl | E1000_CTRL_PRIOR);
	}

	/* Setup link and flow control */
	ret_val = e1000_setup_link_82542(hw);

	/*
	 * Clear all of the statistics registers (clear on read).  It is
	 * important that we do this after we have tried to establish link
	 * because the symbol error count will increment wildly if there
	 * is no link.
	 */
	e1000_clear_hw_cntrs_82542(hw);

	return ret_val;
}