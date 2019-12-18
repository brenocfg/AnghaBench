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
struct ixgbe_hw {int dummy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  DEBUGOUT (char*) ; 
 scalar_t__ IXGBE_ERR_FDIR_REINIT_FAILED ; 
 int /*<<< orphan*/  IXGBE_FDIRCMD ; 
 int IXGBE_FDIRCMD_CLEARHT ; 
 int /*<<< orphan*/  IXGBE_FDIRCTRL ; 
 int IXGBE_FDIRCTRL_INIT_DONE ; 
 int /*<<< orphan*/  IXGBE_FDIRFREE ; 
 int /*<<< orphan*/  IXGBE_FDIRFSTAT ; 
 int /*<<< orphan*/  IXGBE_FDIRHASH ; 
 int /*<<< orphan*/  IXGBE_FDIRLEN ; 
 int /*<<< orphan*/  IXGBE_FDIRMATCH ; 
 int /*<<< orphan*/  IXGBE_FDIRMISS ; 
 int /*<<< orphan*/  IXGBE_FDIRUSTAT ; 
 int IXGBE_FDIR_INIT_DONE_POLL ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 scalar_t__ IXGBE_SUCCESS ; 
 int /*<<< orphan*/  IXGBE_WRITE_FLUSH (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ixgbe_fdir_check_cmd_complete (struct ixgbe_hw*,int*) ; 
 int /*<<< orphan*/  msec_delay (int) ; 

s32 ixgbe_reinit_fdir_tables_82599(struct ixgbe_hw *hw)
{
	s32 err;
	int i;
	u32 fdirctrl = IXGBE_READ_REG(hw, IXGBE_FDIRCTRL);
	u32 fdircmd;
	fdirctrl &= ~IXGBE_FDIRCTRL_INIT_DONE;

	DEBUGFUNC("ixgbe_reinit_fdir_tables_82599");

	/*
	 * Before starting reinitialization process,
	 * FDIRCMD.CMD must be zero.
	 */
	err = ixgbe_fdir_check_cmd_complete(hw, &fdircmd);
	if (err) {
		DEBUGOUT("Flow Director previous command did not complete, aborting table re-initialization.\n");
		return err;
	}

	IXGBE_WRITE_REG(hw, IXGBE_FDIRFREE, 0);
	IXGBE_WRITE_FLUSH(hw);
	/*
	 * 82599 adapters flow director init flow cannot be restarted,
	 * Workaround 82599 silicon errata by performing the following steps
	 * before re-writing the FDIRCTRL control register with the same value.
	 * - write 1 to bit 8 of FDIRCMD register &
	 * - write 0 to bit 8 of FDIRCMD register
	 */
	IXGBE_WRITE_REG(hw, IXGBE_FDIRCMD,
			(IXGBE_READ_REG(hw, IXGBE_FDIRCMD) |
			 IXGBE_FDIRCMD_CLEARHT));
	IXGBE_WRITE_FLUSH(hw);
	IXGBE_WRITE_REG(hw, IXGBE_FDIRCMD,
			(IXGBE_READ_REG(hw, IXGBE_FDIRCMD) &
			 ~IXGBE_FDIRCMD_CLEARHT));
	IXGBE_WRITE_FLUSH(hw);
	/*
	 * Clear FDIR Hash register to clear any leftover hashes
	 * waiting to be programmed.
	 */
	IXGBE_WRITE_REG(hw, IXGBE_FDIRHASH, 0x00);
	IXGBE_WRITE_FLUSH(hw);

	IXGBE_WRITE_REG(hw, IXGBE_FDIRCTRL, fdirctrl);
	IXGBE_WRITE_FLUSH(hw);

	/* Poll init-done after we write FDIRCTRL register */
	for (i = 0; i < IXGBE_FDIR_INIT_DONE_POLL; i++) {
		if (IXGBE_READ_REG(hw, IXGBE_FDIRCTRL) &
				   IXGBE_FDIRCTRL_INIT_DONE)
			break;
		msec_delay(1);
	}
	if (i >= IXGBE_FDIR_INIT_DONE_POLL) {
		DEBUGOUT("Flow Director Signature poll time exceeded!\n");
		return IXGBE_ERR_FDIR_REINIT_FAILED;
	}

	/* Clear FDIR statistics registers (read to clear) */
	IXGBE_READ_REG(hw, IXGBE_FDIRUSTAT);
	IXGBE_READ_REG(hw, IXGBE_FDIRFSTAT);
	IXGBE_READ_REG(hw, IXGBE_FDIRMATCH);
	IXGBE_READ_REG(hw, IXGBE_FDIRMISS);
	IXGBE_READ_REG(hw, IXGBE_FDIRLEN);

	return IXGBE_SUCCESS;
}