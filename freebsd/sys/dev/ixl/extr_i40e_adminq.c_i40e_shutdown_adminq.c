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
struct TYPE_4__ {scalar_t__ va; } ;
struct TYPE_3__ {int /*<<< orphan*/  arq_spinlock; int /*<<< orphan*/  asq_spinlock; } ;
struct i40e_hw {TYPE_2__ nvm_buff; TYPE_1__ aq; } ;
typedef  enum i40e_status_code { ____Placeholder_i40e_status_code } i40e_status_code ;

/* Variables and functions */
 int I40E_SUCCESS ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  i40e_aq_queue_shutdown (struct i40e_hw*,int /*<<< orphan*/ ) ; 
 scalar_t__ i40e_check_asq_alive (struct i40e_hw*) ; 
 int /*<<< orphan*/  i40e_destroy_spinlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i40e_free_virt_mem (struct i40e_hw*,TYPE_2__*) ; 
 int /*<<< orphan*/  i40e_shutdown_arq (struct i40e_hw*) ; 
 int /*<<< orphan*/  i40e_shutdown_asq (struct i40e_hw*) ; 

enum i40e_status_code i40e_shutdown_adminq(struct i40e_hw *hw)
{
	enum i40e_status_code ret_code = I40E_SUCCESS;

	if (i40e_check_asq_alive(hw))
		i40e_aq_queue_shutdown(hw, TRUE);

	i40e_shutdown_asq(hw);
	i40e_shutdown_arq(hw);
	i40e_destroy_spinlock(&hw->aq.asq_spinlock);
	i40e_destroy_spinlock(&hw->aq.arq_spinlock);

	if (hw->nvm_buff.va)
		i40e_free_virt_mem(hw, &hw->nvm_buff);

	return ret_code;
}