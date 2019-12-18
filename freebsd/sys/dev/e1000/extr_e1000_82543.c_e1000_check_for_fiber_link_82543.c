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
typedef  int u32 ;
struct e1000_mac_info {int txcw; void* serdes_has_link; void* autoneg_failed; } ;
struct e1000_hw {struct e1000_mac_info mac; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  DEBUGOUT (char*) ; 
 int /*<<< orphan*/  E1000_CTRL ; 
 int E1000_CTRL_FD ; 
 int E1000_CTRL_SLU ; 
 int E1000_CTRL_SWDPIN1 ; 
 int E1000_READ_REG (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E1000_RXCW ; 
 int E1000_RXCW_C ; 
 int /*<<< orphan*/  E1000_STATUS ; 
 int E1000_STATUS_LU ; 
 scalar_t__ E1000_SUCCESS ; 
 int /*<<< orphan*/  E1000_TXCW ; 
 int E1000_TXCW_ANE ; 
 int /*<<< orphan*/  E1000_WRITE_REG (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 void* TRUE ; 
 scalar_t__ e1000_config_fc_after_link_up_generic (struct e1000_hw*) ; 

__attribute__((used)) static s32 e1000_check_for_fiber_link_82543(struct e1000_hw *hw)
{
	struct e1000_mac_info *mac = &hw->mac;
	u32 rxcw, ctrl, status;
	s32 ret_val = E1000_SUCCESS;

	DEBUGFUNC("e1000_check_for_fiber_link_82543");

	ctrl = E1000_READ_REG(hw, E1000_CTRL);
	status = E1000_READ_REG(hw, E1000_STATUS);
	rxcw = E1000_READ_REG(hw, E1000_RXCW);

	/*
	 * If we don't have link (auto-negotiation failed or link partner
	 * cannot auto-negotiate), the cable is plugged in (we have signal),
	 * and our link partner is not trying to auto-negotiate with us (we
	 * are receiving idles or data), we need to force link up. We also
	 * need to give auto-negotiation time to complete, in case the cable
	 * was just plugged in. The autoneg_failed flag does this.
	 */
	/* (ctrl & E1000_CTRL_SWDPIN1) == 0 == have signal */
	if ((!(ctrl & E1000_CTRL_SWDPIN1)) &&
	    (!(status & E1000_STATUS_LU)) &&
	    (!(rxcw & E1000_RXCW_C))) {
		if (!mac->autoneg_failed) {
			mac->autoneg_failed = TRUE;
			ret_val = 0;
			goto out;
		}
		DEBUGOUT("NOT RXing /C/, disable AutoNeg and force link.\n");

		/* Disable auto-negotiation in the TXCW register */
		E1000_WRITE_REG(hw, E1000_TXCW, (mac->txcw & ~E1000_TXCW_ANE));

		/* Force link-up and also force full-duplex. */
		ctrl = E1000_READ_REG(hw, E1000_CTRL);
		ctrl |= (E1000_CTRL_SLU | E1000_CTRL_FD);
		E1000_WRITE_REG(hw, E1000_CTRL, ctrl);

		/* Configure Flow Control after forcing link up. */
		ret_val = e1000_config_fc_after_link_up_generic(hw);
		if (ret_val) {
			DEBUGOUT("Error configuring flow control\n");
			goto out;
		}
	} else if ((ctrl & E1000_CTRL_SLU) && (rxcw & E1000_RXCW_C)) {
		/*
		 * If we are forcing link and we are receiving /C/ ordered
		 * sets, re-enable auto-negotiation in the TXCW register
		 * and disable forced link in the Device Control register
		 * in an attempt to auto-negotiate with our link partner.
		 */
		DEBUGOUT("RXing /C/, enable AutoNeg and stop forcing link.\n");
		E1000_WRITE_REG(hw, E1000_TXCW, mac->txcw);
		E1000_WRITE_REG(hw, E1000_CTRL, (ctrl & ~E1000_CTRL_SLU));

		mac->serdes_has_link = TRUE;
	}

out:
	return ret_val;
}