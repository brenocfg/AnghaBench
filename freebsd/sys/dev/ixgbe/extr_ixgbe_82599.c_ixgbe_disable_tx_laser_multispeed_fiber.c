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
typedef  int /*<<< orphan*/  u32 ;
struct ixgbe_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_ESDP ; 
 int /*<<< orphan*/  IXGBE_ESDP_SDP3 ; 
 int /*<<< orphan*/  IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_WRITE_FLUSH (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ixgbe_check_reset_blocked (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  usec_delay (int) ; 

void ixgbe_disable_tx_laser_multispeed_fiber(struct ixgbe_hw *hw)
{
	u32 esdp_reg = IXGBE_READ_REG(hw, IXGBE_ESDP);

	/* Blocked by MNG FW so bail */
	if (ixgbe_check_reset_blocked(hw))
		return;

	/* Disable Tx laser; allow 100us to go dark per spec */
	esdp_reg |= IXGBE_ESDP_SDP3;
	IXGBE_WRITE_REG(hw, IXGBE_ESDP, esdp_reg);
	IXGBE_WRITE_FLUSH(hw);
	usec_delay(100);
}