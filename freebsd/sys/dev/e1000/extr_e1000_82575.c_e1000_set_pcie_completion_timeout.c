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
typedef  int /*<<< orphan*/  u16 ;
struct e1000_hw {int dummy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_GCR ; 
 int E1000_GCR_CAP_VER2 ; 
 int E1000_GCR_CMPL_TMOUT_10ms ; 
 int E1000_GCR_CMPL_TMOUT_MASK ; 
 int E1000_GCR_CMPL_TMOUT_RESEND ; 
 int E1000_READ_REG (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 scalar_t__ E1000_SUCCESS ; 
 int /*<<< orphan*/  E1000_WRITE_REG (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PCIE_DEVICE_CONTROL2 ; 
 int /*<<< orphan*/  PCIE_DEVICE_CONTROL2_16ms ; 
 scalar_t__ e1000_read_pcie_cap_reg (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ e1000_write_pcie_cap_reg (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static s32 e1000_set_pcie_completion_timeout(struct e1000_hw *hw)
{
	u32 gcr = E1000_READ_REG(hw, E1000_GCR);
	s32 ret_val = E1000_SUCCESS;
	u16 pcie_devctl2;

	/* only take action if timeout value is defaulted to 0 */
	if (gcr & E1000_GCR_CMPL_TMOUT_MASK)
		goto out;

	/*
	 * if capababilities version is type 1 we can write the
	 * timeout of 10ms to 200ms through the GCR register
	 */
	if (!(gcr & E1000_GCR_CAP_VER2)) {
		gcr |= E1000_GCR_CMPL_TMOUT_10ms;
		goto out;
	}

	/*
	 * for version 2 capabilities we need to write the config space
	 * directly in order to set the completion timeout value for
	 * 16ms to 55ms
	 */
	ret_val = e1000_read_pcie_cap_reg(hw, PCIE_DEVICE_CONTROL2,
					  &pcie_devctl2);
	if (ret_val)
		goto out;

	pcie_devctl2 |= PCIE_DEVICE_CONTROL2_16ms;

	ret_val = e1000_write_pcie_cap_reg(hw, PCIE_DEVICE_CONTROL2,
					   &pcie_devctl2);
out:
	/* disable completion timeout resend */
	gcr &= ~E1000_GCR_CMPL_TMOUT_RESEND;

	E1000_WRITE_REG(hw, E1000_GCR, gcr);
	return ret_val;
}