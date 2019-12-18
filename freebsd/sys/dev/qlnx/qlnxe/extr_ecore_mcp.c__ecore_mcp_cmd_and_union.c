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
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct ecore_ptt {int dummy; } ;
struct ecore_mcp_mb_params {int /*<<< orphan*/  mcp_resp; int /*<<< orphan*/  mcp_param; int /*<<< orphan*/  param; int /*<<< orphan*/  cmd; } ;
struct ecore_mcp_cmd_elem {scalar_t__ b_is_completed; } ;
struct ecore_hwfn {TYPE_1__* mcp_info; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;
struct TYPE_2__ {int /*<<< orphan*/  cmd_lock; scalar_t__ drv_mb_seq; } ;

/* Variables and functions */
 int /*<<< orphan*/  AVOID_BLOCK ; 
 int /*<<< orphan*/  CAN_SLEEP ; 
 scalar_t__ DIV_ROUND_UP (scalar_t__,int) ; 
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int ECORE_AGAIN ; 
 int /*<<< orphan*/  ECORE_HW_ERR_MFW_RESP_FAIL ; 
 scalar_t__ ECORE_MB_FLAGS_IS_SET (struct ecore_mcp_mb_params*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ECORE_MSG_SP ; 
 int ECORE_NOMEM ; 
 int ECORE_SUCCESS ; 
 int /*<<< orphan*/  FW_MSG_CODE_MASK ; 
 int /*<<< orphan*/  OSAL_MFW_CMD_PREEMPT (struct ecore_hwfn*) ; 
 int /*<<< orphan*/  OSAL_MSLEEP (scalar_t__) ; 
 int /*<<< orphan*/  OSAL_SPIN_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSAL_SPIN_UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSAL_UDELAY (scalar_t__) ; 
 int /*<<< orphan*/  __ecore_mcp_cmd_and_union (struct ecore_hwfn*,struct ecore_ptt*,struct ecore_mcp_mb_params*,scalar_t__) ; 
 int /*<<< orphan*/  ecore_hw_err_notify (struct ecore_hwfn*,int /*<<< orphan*/ ) ; 
 struct ecore_mcp_cmd_elem* ecore_mcp_cmd_add_elem (struct ecore_hwfn*,struct ecore_mcp_mb_params*,scalar_t__) ; 
 int /*<<< orphan*/  ecore_mcp_cmd_del_elem (struct ecore_hwfn*,struct ecore_mcp_cmd_elem*) ; 
 int /*<<< orphan*/  ecore_mcp_cmd_set_blocking (struct ecore_hwfn*,int) ; 
 int /*<<< orphan*/  ecore_mcp_has_pending_cmd (struct ecore_hwfn*) ; 
 int /*<<< orphan*/  ecore_mcp_print_cpu_info (struct ecore_hwfn*,struct ecore_ptt*) ; 
 int /*<<< orphan*/  ecore_mcp_reread_offsets (struct ecore_hwfn*,struct ecore_ptt*) ; 
 int ecore_mcp_update_pending_cmd (struct ecore_hwfn*,struct ecore_ptt*) ; 

__attribute__((used)) static enum _ecore_status_t
_ecore_mcp_cmd_and_union(struct ecore_hwfn *p_hwfn, struct ecore_ptt *p_ptt,
			 struct ecore_mcp_mb_params *p_mb_params,
			 u32 max_retries, u32 usecs)
{
	u32 cnt = 0, msecs = DIV_ROUND_UP(usecs, 1000);
	struct ecore_mcp_cmd_elem *p_cmd_elem;
	u16 seq_num;
	enum _ecore_status_t rc = ECORE_SUCCESS;

	/* Wait until the mailbox is non-occupied */
	do {
		/* Exit the loop if there is no pending command, or if the
		 * pending command is completed during this iteration.
		 * The spinlock stays locked until the command is sent.
		 */

		OSAL_SPIN_LOCK(&p_hwfn->mcp_info->cmd_lock);

		if (!ecore_mcp_has_pending_cmd(p_hwfn))
			break;

		rc = ecore_mcp_update_pending_cmd(p_hwfn, p_ptt);
		if (rc == ECORE_SUCCESS)
			break;
		else if (rc != ECORE_AGAIN)
			goto err;

		OSAL_SPIN_UNLOCK(&p_hwfn->mcp_info->cmd_lock);
		if (ECORE_MB_FLAGS_IS_SET(p_mb_params, CAN_SLEEP)) {
			OSAL_MSLEEP(msecs);
		} else {
			OSAL_UDELAY(usecs);
		}
		OSAL_MFW_CMD_PREEMPT(p_hwfn);
	} while (++cnt < max_retries);

	if (cnt >= max_retries) {
		DP_NOTICE(p_hwfn, false,
			  "The MFW mailbox is occupied by an uncompleted command. Failed to send command 0x%08x [param 0x%08x].\n",
			  p_mb_params->cmd, p_mb_params->param);
		return ECORE_AGAIN;
	}

	/* Send the mailbox command */
	ecore_mcp_reread_offsets(p_hwfn, p_ptt);
	seq_num = ++p_hwfn->mcp_info->drv_mb_seq;
	p_cmd_elem = ecore_mcp_cmd_add_elem(p_hwfn, p_mb_params, seq_num);
	if (!p_cmd_elem) {
		rc = ECORE_NOMEM;
		goto err;
	}

	__ecore_mcp_cmd_and_union(p_hwfn, p_ptt, p_mb_params, seq_num);
	OSAL_SPIN_UNLOCK(&p_hwfn->mcp_info->cmd_lock);

	/* Wait for the MFW response */
	do {
		/* Exit the loop if the command is already completed, or if the
		 * command is completed during this iteration.
		 * The spinlock stays locked until the list element is removed.
		 */

		if (ECORE_MB_FLAGS_IS_SET(p_mb_params, CAN_SLEEP)) {
			OSAL_MSLEEP(msecs);
		} else {
			OSAL_UDELAY(usecs);
		}
		OSAL_SPIN_LOCK(&p_hwfn->mcp_info->cmd_lock);

		if (p_cmd_elem->b_is_completed)
			break;

		rc = ecore_mcp_update_pending_cmd(p_hwfn, p_ptt);
		if (rc == ECORE_SUCCESS)
			break;
		else if (rc != ECORE_AGAIN)
			goto err;

		OSAL_SPIN_UNLOCK(&p_hwfn->mcp_info->cmd_lock);
		OSAL_MFW_CMD_PREEMPT(p_hwfn);
	} while (++cnt < max_retries);

	if (cnt >= max_retries) {
		DP_NOTICE(p_hwfn, false,
			  "The MFW failed to respond to command 0x%08x [param 0x%08x].\n",
			  p_mb_params->cmd, p_mb_params->param);
		ecore_mcp_print_cpu_info(p_hwfn, p_ptt);

		OSAL_SPIN_LOCK(&p_hwfn->mcp_info->cmd_lock);
		ecore_mcp_cmd_del_elem(p_hwfn, p_cmd_elem);
		OSAL_SPIN_UNLOCK(&p_hwfn->mcp_info->cmd_lock);

		if (!ECORE_MB_FLAGS_IS_SET(p_mb_params, AVOID_BLOCK))
			ecore_mcp_cmd_set_blocking(p_hwfn, true);
		ecore_hw_err_notify(p_hwfn, ECORE_HW_ERR_MFW_RESP_FAIL);
		return ECORE_AGAIN;
	}

	ecore_mcp_cmd_del_elem(p_hwfn, p_cmd_elem);
	OSAL_SPIN_UNLOCK(&p_hwfn->mcp_info->cmd_lock);

	DP_VERBOSE(p_hwfn, ECORE_MSG_SP,
		   "MFW mailbox: response 0x%08x param 0x%08x [after %d.%03d ms]\n",
		   p_mb_params->mcp_resp, p_mb_params->mcp_param,
		   (cnt * usecs) / 1000, (cnt * usecs) % 1000);

	/* Clear the sequence number from the MFW response */
	p_mb_params->mcp_resp &= FW_MSG_CODE_MASK;

	return ECORE_SUCCESS;

err:
	OSAL_SPIN_UNLOCK(&p_hwfn->mcp_info->cmd_lock);
	return rc;
}