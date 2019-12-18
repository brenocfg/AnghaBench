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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct TYPE_2__ {scalar_t__ sr_size; } ;
struct i40e_hw {TYPE_1__ nvm; int /*<<< orphan*/  nvm_wb_desc; } ;
struct i40e_asq_cmd_details {int /*<<< orphan*/ * wb_desc; } ;
typedef  enum i40e_status_code { ____Placeholder_i40e_status_code } i40e_status_code ;
typedef  int /*<<< orphan*/  cmd_details ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  DEBUGOUT (char*) ; 
 int I40E_ERR_NVM ; 
 scalar_t__ I40E_SR_SECTOR_SIZE_IN_WORDS ; 
 int i40e_aq_update_nvm (struct i40e_hw*,int /*<<< orphan*/ ,int,int,void*,int,int /*<<< orphan*/ ,struct i40e_asq_cmd_details*) ; 
 int /*<<< orphan*/  memset (struct i40e_asq_cmd_details*,int /*<<< orphan*/ ,int) ; 

enum i40e_status_code i40e_write_nvm_aq(struct i40e_hw *hw, u8 module_pointer,
					u32 offset, u16 words, void *data,
					bool last_command)
{
	enum i40e_status_code ret_code = I40E_ERR_NVM;
	struct i40e_asq_cmd_details cmd_details;

	DEBUGFUNC("i40e_write_nvm_aq");

	memset(&cmd_details, 0, sizeof(cmd_details));
	cmd_details.wb_desc = &hw->nvm_wb_desc;

	/* Here we are checking the SR limit only for the flat memory model.
	 * We cannot do it for the module-based model, as we did not acquire
	 * the NVM resource yet (we cannot get the module pointer value).
	 * Firmware will check the module-based model.
	 */
	if ((offset + words) > hw->nvm.sr_size)
		DEBUGOUT("NVM write error: offset beyond Shadow RAM limit.\n");
	else if (words > I40E_SR_SECTOR_SIZE_IN_WORDS)
		/* We can write only up to 4KB (one sector), in one AQ write */
		DEBUGOUT("NVM write fail error: cannot write more than 4KB in a single write.\n");
	else if (((offset + (words - 1)) / I40E_SR_SECTOR_SIZE_IN_WORDS)
		 != (offset / I40E_SR_SECTOR_SIZE_IN_WORDS))
		/* A single write cannot spread over two sectors */
		DEBUGOUT("NVM write error: cannot spread over two sectors in a single write.\n");
	else
		ret_code = i40e_aq_update_nvm(hw, module_pointer,
					      2 * offset,  /*bytes*/
					      2 * words,   /*bytes*/
					      data, last_command, 0,
					      &cmd_details);

	return ret_code;
}