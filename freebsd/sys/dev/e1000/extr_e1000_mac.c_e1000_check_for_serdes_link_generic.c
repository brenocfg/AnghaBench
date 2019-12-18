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
 int E1000_READ_REG (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E1000_RXCW ; 
 int E1000_RXCW_C ; 
 int E1000_RXCW_IV ; 
 int E1000_RXCW_SYNCH ; 
 int /*<<< orphan*/  E1000_STATUS ; 
 int E1000_STATUS_LU ; 
 scalar_t__ E1000_SUCCESS ; 
 int /*<<< orphan*/  E1000_TXCW ; 
 int E1000_TXCW_ANE ; 
 int /*<<< orphan*/  E1000_WRITE_REG (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 void* FALSE ; 
 void* TRUE ; 
 scalar_t__ e1000_config_fc_after_link_up_generic (struct e1000_hw*) ; 
 int /*<<< orphan*/  usec_delay (int) ; 

s32 e1000_check_for_serdes_link_generic(struct e1000_hw *hw)
{
	struct e1000_mac_info *mac = &hw->mac;
	u32 rxcw;
	u32 ctrl;
	u32 status;
	s32 ret_val;

	DEBUGFUNC("e1000_check_for_serdes_link_generic");

	ctrl = E1000_READ_REG(hw, E1000_CTRL);
	status = E1000_READ_REG(hw, E1000_STATUS);
	rxcw = E1000_READ_REG(hw, E1000_RXCW);

	/* If we don't have link (auto-negotiation failed or link partner
	 * cannot auto-negotiate), and our link partner is not trying to
	 * auto-negotiate with us (we are receiving idles or data),
	 * we need to force link up. We also need to give auto-negotiation
	 * time to complete.
	 */
	/* (ctrl & E1000_CTRL_SWDPIN1) == 1 == have signal */
	if (!(status & E1000_STATUS_LU) && !(rxcw & E1000_RXCW_C)) {
		if (!mac->autoneg_failed) {
			mac->autoneg_failed = TRUE;
			return E1000_SUCCESS;
		}
		DEBUGOUT("NOT Rx'ing /C/, disable AutoNeg and force link.\n");

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
			return ret_val;
		}
	} else if ((ctrl & E1000_CTRL_SLU) && (rxcw & E1000_RXCW_C)) {
		/* If we are forcing link and we are receiving /C/ ordered
		 * sets, re-enable auto-negotiation in the TXCW register
		 * and disable forced link in the Device Control register
		 * in an attempt to auto-negotiate with our link partner.
		 */
		DEBUGOUT("Rx'ing /C/, enable AutoNeg and stop forcing link.\n");
		E1000_WRITE_REG(hw, E1000_TXCW, mac->txcw);
		E1000_WRITE_REG(hw, E1000_CTRL, (ctrl & ~E1000_CTRL_SLU));

		mac->serdes_has_link = TRUE;
	} else if (!(E1000_TXCW_ANE & E1000_READ_REG(hw, E1000_TXCW))) {
		/* If we force link for non-auto-negotiation switch, check
		 * link status based on MAC synchronization for internal
		 * serdes media type.
		 */
		/* SYNCH bit and IV bit are sticky. */
		usec_delay(10);
		rxcw = E1000_READ_REG(hw, E1000_RXCW);
		if (rxcw & E1000_RXCW_SYNCH) {
			if (!(rxcw & E1000_RXCW_IV)) {
				mac->serdes_has_link = TRUE;
				DEBUGOUT("SERDES: Link up - forced.\n");
			}
		} else {
			mac->serdes_has_link = FALSE;
			DEBUGOUT("SERDES: Link down - force failed.\n");
		}
	}

	if (E1000_TXCW_ANE & E1000_READ_REG(hw, E1000_TXCW)) {
		status = E1000_READ_REG(hw, E1000_STATUS);
		if (status & E1000_STATUS_LU) {
			/* SYNCH bit and IV bit are sticky, so reread rxcw. */
			usec_delay(10);
			rxcw = E1000_READ_REG(hw, E1000_RXCW);
			if (rxcw & E1000_RXCW_SYNCH) {
				if (!(rxcw & E1000_RXCW_IV)) {
					mac->serdes_has_link = TRUE;
					DEBUGOUT("SERDES: Link up - autoneg completed successfully.\n");
				} else {
					mac->serdes_has_link = FALSE;
					DEBUGOUT("SERDES: Link down - invalid codewords detected in autoneg.\n");
				}
			} else {
				mac->serdes_has_link = FALSE;
				DEBUGOUT("SERDES: Link down - no sync.\n");
			}
		} else {
			mac->serdes_has_link = FALSE;
			DEBUGOUT("SERDES: Link down - autoneg failed\n");
		}
	}

	return E1000_SUCCESS;
}