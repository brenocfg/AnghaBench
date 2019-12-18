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
struct i40e_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  i40e_aq_clear_pxe_mode (struct i40e_hw*,int /*<<< orphan*/ *) ; 
 scalar_t__ i40e_check_asq_alive (struct i40e_hw*) ; 

void i40e_clear_pxe_mode(struct i40e_hw *hw)
{
	if (i40e_check_asq_alive(hw))
		i40e_aq_clear_pxe_mode(hw, NULL);
}