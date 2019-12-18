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
typedef  int u8 ;
typedef  int u32 ;
struct ixgbe_hw {int dummy; } ;
struct TYPE_2__ {int pg_tcs; } ;
struct ixgbe_dcb_config {int vt_mode; TYPE_1__ num_tcs; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  IXGBE_ERR_PARAM ; 
 int /*<<< orphan*/  IXGBE_RQSMR (int) ; 
 int /*<<< orphan*/  IXGBE_SUCCESS ; 
 int /*<<< orphan*/  IXGBE_TQSM (int) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 
 int TRUE ; 

s32 ixgbe_dcb_config_tc_stats_82599(struct ixgbe_hw *hw,
				    struct ixgbe_dcb_config *dcb_config)
{
	u32 reg = 0;
	u8  i   = 0;
	u8 tc_count = 8;
	bool vt_mode = FALSE;

	if (dcb_config != NULL) {
		tc_count = dcb_config->num_tcs.pg_tcs;
		vt_mode = dcb_config->vt_mode;
	}

	if (!((tc_count == 8 && vt_mode == FALSE) || tc_count == 4))
		return IXGBE_ERR_PARAM;

	if (tc_count == 8 && vt_mode == FALSE) {
		/*
		 * Receive Queues stats setting
		 * 32 RQSMR registers, each configuring 4 queues.
		 *
		 * Set all 16 queues of each TC to the same stat
		 * with TC 'n' going to stat 'n'.
		 */
		for (i = 0; i < 32; i++) {
			reg = 0x01010101 * (i / 4);
			IXGBE_WRITE_REG(hw, IXGBE_RQSMR(i), reg);
		}
		/*
		 * Transmit Queues stats setting
		 * 32 TQSM registers, each controlling 4 queues.
		 *
		 * Set all queues of each TC to the same stat
		 * with TC 'n' going to stat 'n'.
		 * Tx queues are allocated non-uniformly to TCs:
		 * 32, 32, 16, 16, 8, 8, 8, 8.
		 */
		for (i = 0; i < 32; i++) {
			if (i < 8)
				reg = 0x00000000;
			else if (i < 16)
				reg = 0x01010101;
			else if (i < 20)
				reg = 0x02020202;
			else if (i < 24)
				reg = 0x03030303;
			else if (i < 26)
				reg = 0x04040404;
			else if (i < 28)
				reg = 0x05050505;
			else if (i < 30)
				reg = 0x06060606;
			else
				reg = 0x07070707;
			IXGBE_WRITE_REG(hw, IXGBE_TQSM(i), reg);
		}
	} else if (tc_count == 4 && vt_mode == FALSE) {
		/*
		 * Receive Queues stats setting
		 * 32 RQSMR registers, each configuring 4 queues.
		 *
		 * Set all 16 queues of each TC to the same stat
		 * with TC 'n' going to stat 'n'.
		 */
		for (i = 0; i < 32; i++) {
			if (i % 8 > 3)
				/* In 4 TC mode, odd 16-queue ranges are
				 *  not used.
				*/
				continue;
			reg = 0x01010101 * (i / 8);
			IXGBE_WRITE_REG(hw, IXGBE_RQSMR(i), reg);
		}
		/*
		 * Transmit Queues stats setting
		 * 32 TQSM registers, each controlling 4 queues.
		 *
		 * Set all queues of each TC to the same stat
		 * with TC 'n' going to stat 'n'.
		 * Tx queues are allocated non-uniformly to TCs:
		 * 64, 32, 16, 16.
		 */
		for (i = 0; i < 32; i++) {
			if (i < 16)
				reg = 0x00000000;
			else if (i < 24)
				reg = 0x01010101;
			else if (i < 28)
				reg = 0x02020202;
			else
				reg = 0x03030303;
			IXGBE_WRITE_REG(hw, IXGBE_TQSM(i), reg);
		}
	} else if (tc_count == 4 && vt_mode == TRUE) {
		/*
		 * Receive Queues stats setting
		 * 32 RQSMR registers, each configuring 4 queues.
		 *
		 * Queue Indexing in 32 VF with DCB mode maps 4 TC's to each
		 * pool. Set all 32 queues of each TC across pools to the same
		 * stat with TC 'n' going to stat 'n'.
		 */
		for (i = 0; i < 32; i++)
			IXGBE_WRITE_REG(hw, IXGBE_RQSMR(i), 0x03020100);
		/*
		 * Transmit Queues stats setting
		 * 32 TQSM registers, each controlling 4 queues.
		 *
		 * Queue Indexing in 32 VF with DCB mode maps 4 TC's to each
		 * pool. Set all 32 queues of each TC across pools to the same
		 * stat with TC 'n' going to stat 'n'.
		 */
		for (i = 0; i < 32; i++)
			IXGBE_WRITE_REG(hw, IXGBE_TQSM(i), 0x03020100);
	}

	return IXGBE_SUCCESS;
}