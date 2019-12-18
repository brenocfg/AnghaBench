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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct TYPE_6__ {scalar_t__ lan_id; } ;
struct TYPE_4__ {int /*<<< orphan*/  set_lben; } ;
struct ixgbe_hw {TYPE_3__ bus; TYPE_1__ mac; } ;
struct TYPE_5__ {int /*<<< orphan*/  checksum; int /*<<< orphan*/  buf_len; int /*<<< orphan*/  cmd; } ;
struct ixgbe_hic_disable_rxen {scalar_t__ port_number; TYPE_2__ hdr; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FW_DEFAULT_CHECKSUM ; 
 int /*<<< orphan*/  FW_DISABLE_RXEN_CMD ; 
 int /*<<< orphan*/  FW_DISABLE_RXEN_LEN ; 
 int /*<<< orphan*/  IXGBE_HI_COMMAND_TIMEOUT ; 
 int /*<<< orphan*/  IXGBE_PFDTXGSWC ; 
 int IXGBE_PFDTXGSWC_VT_LBEN ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_RXCTRL ; 
 int IXGBE_RXCTRL_RXEN ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ ixgbe_host_interface_command (struct ixgbe_hw*,int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ixgbe_disable_rx_x550(struct ixgbe_hw *hw)
{
	u32 rxctrl, pfdtxgswc;
	s32 status;
	struct ixgbe_hic_disable_rxen fw_cmd;

	DEBUGFUNC("ixgbe_enable_rx_dma_x550");

	rxctrl = IXGBE_READ_REG(hw, IXGBE_RXCTRL);
	if (rxctrl & IXGBE_RXCTRL_RXEN) {
		pfdtxgswc = IXGBE_READ_REG(hw, IXGBE_PFDTXGSWC);
		if (pfdtxgswc & IXGBE_PFDTXGSWC_VT_LBEN) {
			pfdtxgswc &= ~IXGBE_PFDTXGSWC_VT_LBEN;
			IXGBE_WRITE_REG(hw, IXGBE_PFDTXGSWC, pfdtxgswc);
			hw->mac.set_lben = TRUE;
		} else {
			hw->mac.set_lben = FALSE;
		}

		fw_cmd.hdr.cmd = FW_DISABLE_RXEN_CMD;
		fw_cmd.hdr.buf_len = FW_DISABLE_RXEN_LEN;
		fw_cmd.hdr.checksum = FW_DEFAULT_CHECKSUM;
		fw_cmd.port_number = (u8)hw->bus.lan_id;

		status = ixgbe_host_interface_command(hw, (u32 *)&fw_cmd,
					sizeof(struct ixgbe_hic_disable_rxen),
					IXGBE_HI_COMMAND_TIMEOUT, TRUE);

		/* If we fail - disable RX using register write */
		if (status) {
			rxctrl = IXGBE_READ_REG(hw, IXGBE_RXCTRL);
			if (rxctrl & IXGBE_RXCTRL_RXEN) {
				rxctrl &= ~IXGBE_RXCTRL_RXEN;
				IXGBE_WRITE_REG(hw, IXGBE_RXCTRL, rxctrl);
			}
		}
	}
}