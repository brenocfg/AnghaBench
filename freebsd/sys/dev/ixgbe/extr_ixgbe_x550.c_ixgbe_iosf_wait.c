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
typedef  scalar_t__ u32 ;
struct ixgbe_hw {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_REPORT1 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  IXGBE_ERROR_POLLING ; 
 int /*<<< orphan*/  IXGBE_ERR_PHY ; 
 scalar_t__ IXGBE_MDIO_COMMAND_TIMEOUT ; 
 scalar_t__ IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 scalar_t__ IXGBE_SB_IOSF_CTRL_BUSY ; 
 int /*<<< orphan*/  IXGBE_SB_IOSF_INDIRECT_CTRL ; 
 int /*<<< orphan*/  IXGBE_SUCCESS ; 
 int /*<<< orphan*/  usec_delay (int) ; 

__attribute__((used)) static s32 ixgbe_iosf_wait(struct ixgbe_hw *hw, u32 *ctrl)
{
	u32 i, command = 0;

	/* Check every 10 usec to see if the address cycle completed.
	 * The SB IOSF BUSY bit will clear when the operation is
	 * complete
	 */
	for (i = 0; i < IXGBE_MDIO_COMMAND_TIMEOUT; i++) {
		command = IXGBE_READ_REG(hw, IXGBE_SB_IOSF_INDIRECT_CTRL);
		if ((command & IXGBE_SB_IOSF_CTRL_BUSY) == 0)
			break;
		usec_delay(10);
	}
	if (ctrl)
		*ctrl = command;
	if (i == IXGBE_MDIO_COMMAND_TIMEOUT) {
		ERROR_REPORT1(IXGBE_ERROR_POLLING, "Wait timed out\n");
		return IXGBE_ERR_PHY;
	}

	return IXGBE_SUCCESS;
}