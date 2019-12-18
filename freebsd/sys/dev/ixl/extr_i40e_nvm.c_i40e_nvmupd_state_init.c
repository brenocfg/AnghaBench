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
struct i40e_nvm_access {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  asq_last_status; } ;
struct i40e_hw {void* nvmupd_state; void* nvm_wait_opcode; void* nvm_release_on_done; TYPE_1__ aq; } ;
typedef  enum i40e_status_code { ____Placeholder_i40e_status_code } i40e_status_code ;
typedef  enum i40e_nvmupd_cmd { ____Placeholder_i40e_nvmupd_cmd } i40e_nvmupd_cmd ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int EIO ; 
 int ESRCH ; 
 int /*<<< orphan*/  I40E_DEBUG_NVM ; 
 int I40E_ERR_NVM ; 
#define  I40E_NVMUPD_CSUM_SA 136 
#define  I40E_NVMUPD_EXEC_AQ 135 
#define  I40E_NVMUPD_GET_AQ_EVENT 134 
#define  I40E_NVMUPD_GET_AQ_RESULT 133 
#define  I40E_NVMUPD_READ_SA 132 
#define  I40E_NVMUPD_READ_SNT 131 
 void* I40E_NVMUPD_STATE_INIT_WAIT ; 
 void* I40E_NVMUPD_STATE_READING ; 
 void* I40E_NVMUPD_STATE_WRITE_WAIT ; 
#define  I40E_NVMUPD_WRITE_ERA 130 
#define  I40E_NVMUPD_WRITE_SA 129 
#define  I40E_NVMUPD_WRITE_SNT 128 
 int /*<<< orphan*/  I40E_RESOURCE_READ ; 
 int /*<<< orphan*/  I40E_RESOURCE_WRITE ; 
 int I40E_SUCCESS ; 
 void* TRUE ; 
 int i40e_acquire_nvm (struct i40e_hw*,int /*<<< orphan*/ ) ; 
 int i40e_aq_rc_to_posix (int,int /*<<< orphan*/ ) ; 
 void* i40e_aqc_opc_nvm_erase ; 
 void* i40e_aqc_opc_nvm_update ; 
 int /*<<< orphan*/  i40e_debug (struct i40e_hw*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * i40e_nvm_update_state_str ; 
 int i40e_nvmupd_exec_aq (struct i40e_hw*,struct i40e_nvm_access*,int /*<<< orphan*/ *,int*) ; 
 int i40e_nvmupd_get_aq_event (struct i40e_hw*,struct i40e_nvm_access*,int /*<<< orphan*/ *,int*) ; 
 int i40e_nvmupd_get_aq_result (struct i40e_hw*,struct i40e_nvm_access*,int /*<<< orphan*/ *,int*) ; 
 int i40e_nvmupd_nvm_erase (struct i40e_hw*,struct i40e_nvm_access*,int*) ; 
 int i40e_nvmupd_nvm_read (struct i40e_hw*,struct i40e_nvm_access*,int /*<<< orphan*/ *,int*) ; 
 int i40e_nvmupd_nvm_write (struct i40e_hw*,struct i40e_nvm_access*,int /*<<< orphan*/ *,int*) ; 
 int i40e_nvmupd_validate_command (struct i40e_hw*,struct i40e_nvm_access*,int*) ; 
 int /*<<< orphan*/  i40e_release_nvm (struct i40e_hw*) ; 
 int i40e_update_nvm_checksum (struct i40e_hw*) ; 

__attribute__((used)) static enum i40e_status_code i40e_nvmupd_state_init(struct i40e_hw *hw,
						    struct i40e_nvm_access *cmd,
						    u8 *bytes, int *perrno)
{
	enum i40e_status_code status = I40E_SUCCESS;
	enum i40e_nvmupd_cmd upd_cmd;

	DEBUGFUNC("i40e_nvmupd_state_init");

	upd_cmd = i40e_nvmupd_validate_command(hw, cmd, perrno);

	switch (upd_cmd) {
	case I40E_NVMUPD_READ_SA:
		status = i40e_acquire_nvm(hw, I40E_RESOURCE_READ);
		if (status) {
			*perrno = i40e_aq_rc_to_posix(status,
						     hw->aq.asq_last_status);
		} else {
			status = i40e_nvmupd_nvm_read(hw, cmd, bytes, perrno);
			i40e_release_nvm(hw);
		}
		break;

	case I40E_NVMUPD_READ_SNT:
		status = i40e_acquire_nvm(hw, I40E_RESOURCE_READ);
		if (status) {
			*perrno = i40e_aq_rc_to_posix(status,
						     hw->aq.asq_last_status);
		} else {
			status = i40e_nvmupd_nvm_read(hw, cmd, bytes, perrno);
			if (status)
				i40e_release_nvm(hw);
			else
				hw->nvmupd_state = I40E_NVMUPD_STATE_READING;
		}
		break;

	case I40E_NVMUPD_WRITE_ERA:
		status = i40e_acquire_nvm(hw, I40E_RESOURCE_WRITE);
		if (status) {
			*perrno = i40e_aq_rc_to_posix(status,
						     hw->aq.asq_last_status);
		} else {
			status = i40e_nvmupd_nvm_erase(hw, cmd, perrno);
			if (status) {
				i40e_release_nvm(hw);
			} else {
				hw->nvm_release_on_done = TRUE;
				hw->nvm_wait_opcode = i40e_aqc_opc_nvm_erase;
				hw->nvmupd_state = I40E_NVMUPD_STATE_INIT_WAIT;
			}
		}
		break;

	case I40E_NVMUPD_WRITE_SA:
		status = i40e_acquire_nvm(hw, I40E_RESOURCE_WRITE);
		if (status) {
			*perrno = i40e_aq_rc_to_posix(status,
						     hw->aq.asq_last_status);
		} else {
			status = i40e_nvmupd_nvm_write(hw, cmd, bytes, perrno);
			if (status) {
				i40e_release_nvm(hw);
			} else {
				hw->nvm_release_on_done = TRUE;
				hw->nvm_wait_opcode = i40e_aqc_opc_nvm_update;
				hw->nvmupd_state = I40E_NVMUPD_STATE_INIT_WAIT;
			}
		}
		break;

	case I40E_NVMUPD_WRITE_SNT:
		status = i40e_acquire_nvm(hw, I40E_RESOURCE_WRITE);
		if (status) {
			*perrno = i40e_aq_rc_to_posix(status,
						     hw->aq.asq_last_status);
		} else {
			status = i40e_nvmupd_nvm_write(hw, cmd, bytes, perrno);
			if (status) {
				i40e_release_nvm(hw);
			} else {
				hw->nvm_wait_opcode = i40e_aqc_opc_nvm_update;
				hw->nvmupd_state = I40E_NVMUPD_STATE_WRITE_WAIT;
			}
		}
		break;

	case I40E_NVMUPD_CSUM_SA:
		status = i40e_acquire_nvm(hw, I40E_RESOURCE_WRITE);
		if (status) {
			*perrno = i40e_aq_rc_to_posix(status,
						     hw->aq.asq_last_status);
		} else {
			status = i40e_update_nvm_checksum(hw);
			if (status) {
				*perrno = hw->aq.asq_last_status ?
				   i40e_aq_rc_to_posix(status,
						       hw->aq.asq_last_status) :
				   -EIO;
				i40e_release_nvm(hw);
			} else {
				hw->nvm_release_on_done = TRUE;
				hw->nvm_wait_opcode = i40e_aqc_opc_nvm_update;
				hw->nvmupd_state = I40E_NVMUPD_STATE_INIT_WAIT;
			}
		}
		break;

	case I40E_NVMUPD_EXEC_AQ:
		status = i40e_nvmupd_exec_aq(hw, cmd, bytes, perrno);
		break;

	case I40E_NVMUPD_GET_AQ_RESULT:
		status = i40e_nvmupd_get_aq_result(hw, cmd, bytes, perrno);
		break;

	case I40E_NVMUPD_GET_AQ_EVENT:
		status = i40e_nvmupd_get_aq_event(hw, cmd, bytes, perrno);
		break;

	default:
		i40e_debug(hw, I40E_DEBUG_NVM,
			   "NVMUPD: bad cmd %s in init state\n",
			   i40e_nvm_update_state_str[upd_cmd]);
		status = I40E_ERR_NVM;
		*perrno = -ESRCH;
		break;
	}
	return status;
}