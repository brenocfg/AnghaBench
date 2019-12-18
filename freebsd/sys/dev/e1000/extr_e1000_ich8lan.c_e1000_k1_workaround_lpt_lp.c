#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_3__ {scalar_t__ (* write_reg ) (struct e1000_hw*,int /*<<< orphan*/ ,int) ;scalar_t__ (* read_reg ) (struct e1000_hw*,int /*<<< orphan*/ ,int*) ;int /*<<< orphan*/  (* release ) (struct e1000_hw*) ;scalar_t__ (* acquire ) (struct e1000_hw*) ;} ;
struct TYPE_4__ {int revision; TYPE_1__ ops; } ;
struct e1000_hw {TYPE_2__ phy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_FEXTNVM6 ; 
 int E1000_FEXTNVM6_ENABLE_K1_ENTRY_CONDITION ; 
 int E1000_FEXTNVM6_REQ_PLL_CLK ; 
 int /*<<< orphan*/  E1000_KMRNCTRLSTA_K1_CONFIG ; 
 int E1000_KMRNCTRLSTA_K1_ENABLE ; 
 int E1000_READ_REG (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E1000_STATUS ; 
 int E1000_STATUS_FD ; 
 int E1000_STATUS_SPEED_100 ; 
 int E1000_STATUS_SPEED_1000 ; 
 scalar_t__ E1000_SUCCESS ; 
 int /*<<< orphan*/  E1000_WRITE_REG (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  I217_INBAND_CTRL ; 
 int I217_INBAND_CTRL_LINK_STAT_TX_TIMEOUT_MASK ; 
 int I217_INBAND_CTRL_LINK_STAT_TX_TIMEOUT_SHIFT ; 
 scalar_t__ e1000_read_kmrn_reg_locked (struct e1000_hw*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ e1000_write_kmrn_reg_locked (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub1 (struct e1000_hw*) ; 
 int /*<<< orphan*/  stub2 (struct e1000_hw*) ; 
 scalar_t__ stub3 (struct e1000_hw*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ stub4 (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usec_delay (int) ; 

__attribute__((used)) static s32 e1000_k1_workaround_lpt_lp(struct e1000_hw *hw, bool link)
{
	u32 fextnvm6 = E1000_READ_REG(hw, E1000_FEXTNVM6);
	u32 status = E1000_READ_REG(hw, E1000_STATUS);
	s32 ret_val = E1000_SUCCESS;
	u16 reg;

	if (link && (status & E1000_STATUS_SPEED_1000)) {
		ret_val = hw->phy.ops.acquire(hw);
		if (ret_val)
			return ret_val;

		ret_val =
		    e1000_read_kmrn_reg_locked(hw, E1000_KMRNCTRLSTA_K1_CONFIG,
					       &reg);
		if (ret_val)
			goto release;

		ret_val =
		    e1000_write_kmrn_reg_locked(hw,
						E1000_KMRNCTRLSTA_K1_CONFIG,
						reg &
						~E1000_KMRNCTRLSTA_K1_ENABLE);
		if (ret_val)
			goto release;

		usec_delay(10);

		E1000_WRITE_REG(hw, E1000_FEXTNVM6,
				fextnvm6 | E1000_FEXTNVM6_REQ_PLL_CLK);

		ret_val =
		    e1000_write_kmrn_reg_locked(hw,
						E1000_KMRNCTRLSTA_K1_CONFIG,
						reg);
release:
		hw->phy.ops.release(hw);
	} else {
		/* clear FEXTNVM6 bit 8 on link down or 10/100 */
		fextnvm6 &= ~E1000_FEXTNVM6_REQ_PLL_CLK;

		if ((hw->phy.revision > 5) || !link ||
		    ((status & E1000_STATUS_SPEED_100) &&
		     (status & E1000_STATUS_FD)))
			goto update_fextnvm6;

		ret_val = hw->phy.ops.read_reg(hw, I217_INBAND_CTRL, &reg);
		if (ret_val)
			return ret_val;

		/* Clear link status transmit timeout */
		reg &= ~I217_INBAND_CTRL_LINK_STAT_TX_TIMEOUT_MASK;

		if (status & E1000_STATUS_SPEED_100) {
			/* Set inband Tx timeout to 5x10us for 100Half */
			reg |= 5 << I217_INBAND_CTRL_LINK_STAT_TX_TIMEOUT_SHIFT;

			/* Do not extend the K1 entry latency for 100Half */
			fextnvm6 &= ~E1000_FEXTNVM6_ENABLE_K1_ENTRY_CONDITION;
		} else {
			/* Set inband Tx timeout to 50x10us for 10Full/Half */
			reg |= 50 <<
			       I217_INBAND_CTRL_LINK_STAT_TX_TIMEOUT_SHIFT;

			/* Extend the K1 entry latency for 10 Mbps */
			fextnvm6 |= E1000_FEXTNVM6_ENABLE_K1_ENTRY_CONDITION;
		}

		ret_val = hw->phy.ops.write_reg(hw, I217_INBAND_CTRL, reg);
		if (ret_val)
			return ret_val;

update_fextnvm6:
		E1000_WRITE_REG(hw, E1000_FEXTNVM6, fextnvm6);
	}

	return ret_val;
}