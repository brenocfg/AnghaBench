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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct i40e_hw {int dummy; } ;
typedef  enum i40e_status_code { ____Placeholder_i40e_status_code } i40e_status_code ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_HMC_LAN_RX ; 
 int i40e_clear_hmc_context (struct i40e_hw*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int i40e_hmc_get_object_va (struct i40e_hw*,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

enum i40e_status_code i40e_clear_lan_rx_queue_context(struct i40e_hw *hw,
						      u16 queue)
{
	enum i40e_status_code err;
	u8 *context_bytes;

	err = i40e_hmc_get_object_va(hw, &context_bytes, I40E_HMC_LAN_RX, queue);
	if (err < 0)
		return err;

	return i40e_clear_hmc_context(hw, context_bytes, I40E_HMC_LAN_RX);
}