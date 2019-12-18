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
typedef  scalar_t__ u32 ;
struct TYPE_8__ {scalar_t__ (* setup_link ) (struct e1000_hw*) ;int /*<<< orphan*/  (* clear_vfta ) (struct e1000_hw*) ;scalar_t__ (* id_led_init ) (struct e1000_hw*) ;} ;
struct e1000_mac_info {scalar_t__ mta_reg_count; TYPE_4__ ops; int /*<<< orphan*/  rar_entry_count; } ;
struct TYPE_6__ {scalar_t__ (* read_reg ) (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct TYPE_7__ {TYPE_2__ ops; } ;
struct e1000_dev_spec_82541 {int /*<<< orphan*/  spd_default; } ;
struct TYPE_5__ {struct e1000_dev_spec_82541 _82541; } ;
struct e1000_hw {TYPE_3__ phy; TYPE_1__ dev_spec; struct e1000_mac_info mac; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  DEBUGOUT (char*) ; 
 int /*<<< orphan*/  E1000_MTA ; 
 scalar_t__ E1000_READ_REG (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E1000_TXDCTL (int /*<<< orphan*/ ) ; 
 scalar_t__ E1000_TXDCTL_FULL_TX_DESC_WB ; 
 scalar_t__ E1000_TXDCTL_WTHRESH ; 
 int /*<<< orphan*/  E1000_WRITE_FLUSH (struct e1000_hw*) ; 
 int /*<<< orphan*/  E1000_WRITE_REG (struct e1000_hw*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  E1000_WRITE_REG_ARRAY (struct e1000_hw*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IGP01E1000_GMII_FIFO ; 
 int /*<<< orphan*/  e1000_clear_hw_cntrs_82541 (struct e1000_hw*) ; 
 int /*<<< orphan*/  e1000_init_rx_addrs_generic (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct e1000_hw*) ; 
 scalar_t__ stub2 (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (struct e1000_hw*) ; 
 scalar_t__ stub4 (struct e1000_hw*) ; 

__attribute__((used)) static s32 e1000_init_hw_82541(struct e1000_hw *hw)
{
	struct e1000_mac_info *mac = &hw->mac;
	struct e1000_dev_spec_82541 *dev_spec = &hw->dev_spec._82541;
	u32 i, txdctl;
	s32 ret_val;

	DEBUGFUNC("e1000_init_hw_82541");

	/* Initialize identification LED */
	ret_val = mac->ops.id_led_init(hw);
	if (ret_val) {
		DEBUGOUT("Error initializing identification LED\n");
		/* This is not fatal and we should not stop init due to this */
	}

	/* Storing the Speed Power Down  value for later use */
	ret_val = hw->phy.ops.read_reg(hw, IGP01E1000_GMII_FIFO,
				       &dev_spec->spd_default);
	if (ret_val)
		goto out;

	/* Disabling VLAN filtering */
	DEBUGOUT("Initializing the IEEE VLAN\n");
	mac->ops.clear_vfta(hw);

	/* Setup the receive address. */
	e1000_init_rx_addrs_generic(hw, mac->rar_entry_count);

	/* Zero out the Multicast HASH table */
	DEBUGOUT("Zeroing the MTA\n");
	for (i = 0; i < mac->mta_reg_count; i++) {
		E1000_WRITE_REG_ARRAY(hw, E1000_MTA, i, 0);
		/*
		 * Avoid back to back register writes by adding the register
		 * read (flush).  This is to protect against some strange
		 * bridge configurations that may issue Memory Write Block
		 * (MWB) to our register space.
		 */
		E1000_WRITE_FLUSH(hw);
	}

	/* Setup link and flow control */
	ret_val = mac->ops.setup_link(hw);

	txdctl = E1000_READ_REG(hw, E1000_TXDCTL(0));
	txdctl = (txdctl & ~E1000_TXDCTL_WTHRESH) |
		  E1000_TXDCTL_FULL_TX_DESC_WB;
	E1000_WRITE_REG(hw, E1000_TXDCTL(0), txdctl);

	/*
	 * Clear all of the statistics registers (clear on read).  It is
	 * important that we do this after we have tried to establish link
	 * because the symbol error count will increment wildly if there
	 * is no link.
	 */
	e1000_clear_hw_cntrs_82541(hw);

out:
	return ret_val;
}