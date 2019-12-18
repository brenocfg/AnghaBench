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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {int dummy; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int ECORE_INVAL ; 
 int /*<<< orphan*/  ECORE_MSG_RDMA ; 
 int /*<<< orphan*/  ECORE_RDMA_DEREGISTER_TIMEOUT_MSEC ; 
 int ECORE_SUCCESS ; 
 int ECORE_TIMEOUT ; 
 int ECORE_UNKNOWN_ERROR ; 
 int /*<<< orphan*/  OSAL_MSLEEP (int /*<<< orphan*/ ) ; 
 scalar_t__ RDMA_RETURN_DEREGISTER_MR_BAD_STATE_ERR ; 
 scalar_t__ RDMA_RETURN_NIG_DRAIN_REQ ; 
 scalar_t__ RDMA_RETURN_OK ; 
 int ecore_mcp_drain (struct ecore_hwfn*,struct ecore_ptt*) ; 
 struct ecore_ptt* ecore_ptt_acquire (struct ecore_hwfn*) ; 
 int /*<<< orphan*/  ecore_ptt_release (struct ecore_hwfn*,struct ecore_ptt*) ; 
 int ecore_rdma_send_deregister_tid_ramrod (struct ecore_hwfn*,int /*<<< orphan*/ ,scalar_t__*) ; 

enum _ecore_status_t ecore_rdma_deregister_tid(void	*rdma_cxt,
					       u32	itid)
{
	enum _ecore_status_t                   rc;
	u8                                     fw_ret_code;
	struct ecore_ptt                       *p_ptt;
	struct ecore_hwfn *p_hwfn = (struct ecore_hwfn *)rdma_cxt;

	/* First attempt */
	rc = ecore_rdma_send_deregister_tid_ramrod(p_hwfn, itid, &fw_ret_code);
	if (rc != ECORE_SUCCESS)
		return rc;

	if (fw_ret_code != RDMA_RETURN_NIG_DRAIN_REQ)
		goto done;

	/* Second attempt, after 1msec, if device still holds data.
	 * This can occur since 'destroy QP' returns to the caller rather fast.
	 * The synchronous part of it returns after freeing a few of the
	 * resources but not all of them, allowing the consumer to continue its
	 * flow. All of the resources will be freed after the asynchronous part
	 * of the destroy QP is complete.
	 */
	OSAL_MSLEEP(ECORE_RDMA_DEREGISTER_TIMEOUT_MSEC);
	rc = ecore_rdma_send_deregister_tid_ramrod(p_hwfn, itid, &fw_ret_code);
	if (rc != ECORE_SUCCESS)
		return rc;

	if (fw_ret_code != RDMA_RETURN_NIG_DRAIN_REQ)
		goto done;

	/* Third and last attempt, perform NIG drain and resend the ramrod */
	p_ptt = ecore_ptt_acquire(p_hwfn);
	if (!p_ptt)
		return ECORE_TIMEOUT;

	rc = ecore_mcp_drain(p_hwfn, p_ptt);
	if (rc != ECORE_SUCCESS) {
		ecore_ptt_release(p_hwfn, p_ptt);
		return rc;
	}

	ecore_ptt_release(p_hwfn, p_ptt);

	rc = ecore_rdma_send_deregister_tid_ramrod(p_hwfn, itid, &fw_ret_code);
	if (rc != ECORE_SUCCESS)
		return rc;

done:
	if (fw_ret_code == RDMA_RETURN_OK) {
		DP_VERBOSE(p_hwfn, ECORE_MSG_RDMA, "De-registered itid=%d\n",
			   itid);
		return ECORE_SUCCESS;
	} else if (fw_ret_code == RDMA_RETURN_DEREGISTER_MR_BAD_STATE_ERR) {
		/* INTERNAL: This error is returned in case trying to deregister
		 * a MR that is not allocated. We define "allocated" as either:
		 * 1. Registered.
		 * 2. This is an FMR MR type, which is not currently registered
		 *    but can accept FMR WQEs on SQ.
		 */
		DP_NOTICE(p_hwfn, false, "itid=%d, fw_ret_code=%d\n", itid,
			  fw_ret_code);
		return ECORE_INVAL;
	} else { /* fw_ret_code == RDMA_RETURN_NIG_DRAIN_REQ */
		DP_NOTICE(p_hwfn, true,
			  "deregister failed after three attempts. itid=%d, fw_ret_code=%d\n",
			  itid, fw_ret_code);
		return ECORE_UNKNOWN_ERROR;
	}
}