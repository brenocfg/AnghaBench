#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {int type; } ;
struct e1000_hw {TYPE_1__ mac; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  DEBUGOUT (char*) ; 
 int /*<<< orphan*/  E1000_CTRL ; 
 int E1000_CTRL_PHY_RST ; 
 int E1000_CTRL_RST ; 
 int /*<<< orphan*/  E1000_ICR ; 
 int /*<<< orphan*/  E1000_IMC ; 
 int /*<<< orphan*/  E1000_LEDCTL ; 
 int /*<<< orphan*/  E1000_MANC ; 
 int E1000_MANC_ARP_EN ; 
 int /*<<< orphan*/  E1000_RCTL ; 
 int E1000_READ_REG (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E1000_SUCCESS ; 
 int /*<<< orphan*/  E1000_TCTL ; 
 int E1000_TCTL_PSP ; 
 int /*<<< orphan*/  E1000_WRITE_FLUSH (struct e1000_hw*) ; 
 int /*<<< orphan*/  E1000_WRITE_REG (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  E1000_WRITE_REG_IO (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 int IGP_ACTIVITY_LED_ENABLE ; 
 int IGP_ACTIVITY_LED_MASK ; 
 int IGP_LED3_MODE ; 
#define  e1000_82541 129 
#define  e1000_82541_rev_2 128 
 int e1000_82547 ; 
 int /*<<< orphan*/  e1000_phy_init_script_82541 (struct e1000_hw*) ; 
 int /*<<< orphan*/  msec_delay (int) ; 

__attribute__((used)) static s32 e1000_reset_hw_82541(struct e1000_hw *hw)
{
	u32 ledctl, ctrl, manc;

	DEBUGFUNC("e1000_reset_hw_82541");

	DEBUGOUT("Masking off all interrupts\n");
	E1000_WRITE_REG(hw, E1000_IMC, 0xFFFFFFFF);

	E1000_WRITE_REG(hw, E1000_RCTL, 0);
	E1000_WRITE_REG(hw, E1000_TCTL, E1000_TCTL_PSP);
	E1000_WRITE_FLUSH(hw);

	/*
	 * Delay to allow any outstanding PCI transactions to complete
	 * before resetting the device.
	 */
	msec_delay(10);

	ctrl = E1000_READ_REG(hw, E1000_CTRL);

	/* Must reset the Phy before resetting the MAC */
	if ((hw->mac.type == e1000_82541) || (hw->mac.type == e1000_82547)) {
		E1000_WRITE_REG(hw, E1000_CTRL, (ctrl | E1000_CTRL_PHY_RST));
		E1000_WRITE_FLUSH(hw);
		msec_delay(5);
	}

	DEBUGOUT("Issuing a global reset to 82541/82547 MAC\n");
	switch (hw->mac.type) {
	case e1000_82541:
	case e1000_82541_rev_2:
		/*
		 * These controllers can't ack the 64-bit write when
		 * issuing the reset, so we use IO-mapping as a
		 * workaround to issue the reset.
		 */
		E1000_WRITE_REG_IO(hw, E1000_CTRL, ctrl | E1000_CTRL_RST);
		break;
	default:
		E1000_WRITE_REG(hw, E1000_CTRL, ctrl | E1000_CTRL_RST);
		break;
	}

	/* Wait for NVM reload */
	msec_delay(20);

	/* Disable HW ARPs on ASF enabled adapters */
	manc = E1000_READ_REG(hw, E1000_MANC);
	manc &= ~E1000_MANC_ARP_EN;
	E1000_WRITE_REG(hw, E1000_MANC, manc);

	if ((hw->mac.type == e1000_82541) || (hw->mac.type == e1000_82547)) {
		e1000_phy_init_script_82541(hw);

		/* Configure activity LED after Phy reset */
		ledctl = E1000_READ_REG(hw, E1000_LEDCTL);
		ledctl &= IGP_ACTIVITY_LED_MASK;
		ledctl |= (IGP_ACTIVITY_LED_ENABLE | IGP_LED3_MODE);
		E1000_WRITE_REG(hw, E1000_LEDCTL, ledctl);
	}

	/* Once again, mask the interrupts */
	DEBUGOUT("Masking off all interrupts\n");
	E1000_WRITE_REG(hw, E1000_IMC, 0xFFFFFFFF);

	/* Clear any pending interrupt events. */
	E1000_READ_REG(hw, E1000_ICR);

	return E1000_SUCCESS;
}