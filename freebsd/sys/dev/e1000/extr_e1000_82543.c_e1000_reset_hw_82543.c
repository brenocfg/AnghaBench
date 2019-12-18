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
struct TYPE_5__ {int /*<<< orphan*/  (* reload ) (struct e1000_hw*) ;} ;
struct TYPE_6__ {TYPE_2__ ops; } ;
struct TYPE_4__ {scalar_t__ type; } ;
struct e1000_hw {TYPE_3__ nvm; TYPE_1__ mac; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  DEBUGOUT (char*) ; 
 int /*<<< orphan*/  E1000_CTRL ; 
 int E1000_CTRL_RST ; 
 int /*<<< orphan*/  E1000_ICR ; 
 int /*<<< orphan*/  E1000_IMC ; 
 int /*<<< orphan*/  E1000_RCTL ; 
 int E1000_READ_REG (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E1000_SUCCESS ; 
 int /*<<< orphan*/  E1000_TCTL ; 
 int E1000_TCTL_PSP ; 
 int /*<<< orphan*/  E1000_WRITE_FLUSH (struct e1000_hw*) ; 
 int /*<<< orphan*/  E1000_WRITE_REG (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  E1000_WRITE_REG_IO (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ e1000_82543 ; 
 int /*<<< orphan*/  e1000_set_tbi_sbp_82543 (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msec_delay (int) ; 
 int /*<<< orphan*/  stub1 (struct e1000_hw*) ; 

__attribute__((used)) static s32 e1000_reset_hw_82543(struct e1000_hw *hw)
{
	u32 ctrl;
	s32 ret_val = E1000_SUCCESS;

	DEBUGFUNC("e1000_reset_hw_82543");

	DEBUGOUT("Masking off all interrupts\n");
	E1000_WRITE_REG(hw, E1000_IMC, 0xffffffff);

	E1000_WRITE_REG(hw, E1000_RCTL, 0);
	E1000_WRITE_REG(hw, E1000_TCTL, E1000_TCTL_PSP);
	E1000_WRITE_FLUSH(hw);

	e1000_set_tbi_sbp_82543(hw, FALSE);

	/*
	 * Delay to allow any outstanding PCI transactions to complete before
	 * resetting the device
	 */
	msec_delay(10);

	ctrl = E1000_READ_REG(hw, E1000_CTRL);

	DEBUGOUT("Issuing a global reset to 82543/82544 MAC\n");
	if (hw->mac.type == e1000_82543) {
		E1000_WRITE_REG(hw, E1000_CTRL, ctrl | E1000_CTRL_RST);
	} else {
		/*
		 * The 82544 can't ACK the 64-bit write when issuing the
		 * reset, so use IO-mapping as a workaround.
		 */
		E1000_WRITE_REG_IO(hw, E1000_CTRL, ctrl | E1000_CTRL_RST);
	}

	/*
	 * After MAC reset, force reload of NVM to restore power-on
	 * settings to device.
	 */
	hw->nvm.ops.reload(hw);
	msec_delay(2);

	/* Masking off and clearing any pending interrupts */
	E1000_WRITE_REG(hw, E1000_IMC, 0xffffffff);
	E1000_READ_REG(hw, E1000_ICR);

	return ret_val;
}