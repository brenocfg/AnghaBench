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
typedef  scalar_t__ u32 ;
struct TYPE_4__ {scalar_t__ asq_cmd_timeout; } ;
struct TYPE_3__ {scalar_t__ blank_nvm_mode; } ;
struct i40e_hw {TYPE_2__ aq; TYPE_1__ nvm; } ;
typedef  enum i40e_status_code { ____Placeholder_i40e_status_code } i40e_status_code ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int I40E_ERR_ADMIN_QUEUE_TIMEOUT ; 
 int /*<<< orphan*/  I40E_NVM_RESOURCE_ID ; 
 int I40E_SUCCESS ; 
 int i40e_aq_release_resource (struct i40e_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i40e_msec_delay (int) ; 

void i40e_release_nvm(struct i40e_hw *hw)
{
	enum i40e_status_code ret_code = I40E_SUCCESS;
	u32 total_delay = 0;

	DEBUGFUNC("i40e_release_nvm");

	if (hw->nvm.blank_nvm_mode)
		return;

	ret_code = i40e_aq_release_resource(hw, I40E_NVM_RESOURCE_ID, 0, NULL);

	/* there are some rare cases when trying to release the resource
	 * results in an admin Q timeout, so handle them correctly
	 */
	while ((ret_code == I40E_ERR_ADMIN_QUEUE_TIMEOUT) &&
	       (total_delay < hw->aq.asq_cmd_timeout)) {
			i40e_msec_delay(1);
			ret_code = i40e_aq_release_resource(hw,
						I40E_NVM_RESOURCE_ID, 0, NULL);
			total_delay++;
	}
}