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
struct TYPE_2__ {int /*<<< orphan*/  req; int /*<<< orphan*/  resp; } ;
struct ecore_rdma_qp {scalar_t__ cur_state; TYPE_1__ cq_prod; int /*<<< orphan*/  qp_idx; } ;
struct ecore_rdma_modify_qp_in_params {int /*<<< orphan*/  modify_flags; } ;
struct ecore_hwfn {int dummy; } ;
typedef  enum ecore_roce_qp_state { ____Placeholder_ecore_roce_qp_state } ecore_roce_qp_state ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*) ; 
 int ECORE_INVAL ; 
 int /*<<< orphan*/  ECORE_MSG_RDMA ; 
 scalar_t__ ECORE_ROCE_QP_STATE_ERR ; 
 int ECORE_ROCE_QP_STATE_INIT ; 
 int ECORE_ROCE_QP_STATE_RESET ; 
 scalar_t__ ECORE_ROCE_QP_STATE_RTR ; 
 scalar_t__ ECORE_ROCE_QP_STATE_RTS ; 
 scalar_t__ ECORE_ROCE_QP_STATE_SQD ; 
 int ECORE_SUCCESS ; 
 int ecore_roce_sp_create_requester (struct ecore_hwfn*,struct ecore_rdma_qp*) ; 
 int ecore_roce_sp_create_responder (struct ecore_hwfn*,struct ecore_rdma_qp*) ; 
 int ecore_roce_sp_destroy_qp_requester (struct ecore_hwfn*,struct ecore_rdma_qp*,scalar_t__*,int /*<<< orphan*/ *) ; 
 int ecore_roce_sp_destroy_qp_responder (struct ecore_hwfn*,struct ecore_rdma_qp*,scalar_t__*,int /*<<< orphan*/ *) ; 
 int ecore_roce_sp_modify_requester (struct ecore_hwfn*,struct ecore_rdma_qp*,int,int,int /*<<< orphan*/ ) ; 
 int ecore_roce_sp_modify_responder (struct ecore_hwfn*,struct ecore_rdma_qp*,int,int /*<<< orphan*/ ) ; 
 int ecore_roce_wait_free_cids (struct ecore_hwfn*,int /*<<< orphan*/ ) ; 

enum _ecore_status_t
ecore_roce_modify_qp(struct ecore_hwfn *p_hwfn,
		     struct ecore_rdma_qp *qp,
		     enum ecore_roce_qp_state prev_state,
		     struct ecore_rdma_modify_qp_in_params *params)
{
	u32 num_invalidated_mw = 0, num_bound_mw = 0;
	enum _ecore_status_t rc = ECORE_SUCCESS;

	/* Perform additional operations according to the current state and the
	 * next state
	 */
	if (((prev_state == ECORE_ROCE_QP_STATE_INIT) ||
	     (prev_state == ECORE_ROCE_QP_STATE_RESET)) &&
	    (qp->cur_state == ECORE_ROCE_QP_STATE_RTR))
	{
		/* Init->RTR or Reset->RTR */

		/* Verify the cid bits that of this qp index are clear */
		rc = ecore_roce_wait_free_cids(p_hwfn, qp->qp_idx);
		if (rc)
			return rc;

		rc = ecore_roce_sp_create_responder(p_hwfn, qp);
		return rc;

	} else if ((prev_state == ECORE_ROCE_QP_STATE_RTR) &&
		   (qp->cur_state == ECORE_ROCE_QP_STATE_RTS))
	{
		/* RTR-> RTS */
		rc = ecore_roce_sp_create_requester(p_hwfn, qp);
		if (rc != ECORE_SUCCESS)
			return rc;

		/* Send modify responder ramrod */
		rc = ecore_roce_sp_modify_responder(p_hwfn, qp, false,
						    params->modify_flags);
		return rc;

	} else if ((prev_state == ECORE_ROCE_QP_STATE_RTS) &&
		   (qp->cur_state == ECORE_ROCE_QP_STATE_RTS))
	{
		/* RTS->RTS */
		rc = ecore_roce_sp_modify_responder(p_hwfn, qp, false,
						    params->modify_flags);
		if (rc != ECORE_SUCCESS)
			return rc;

		rc = ecore_roce_sp_modify_requester(p_hwfn, qp, false, false,
						    params->modify_flags);
		return rc;

	} else if ((prev_state == ECORE_ROCE_QP_STATE_RTS) &&
		   (qp->cur_state == ECORE_ROCE_QP_STATE_SQD))
	{
		/* RTS->SQD */
		rc = ecore_roce_sp_modify_requester(p_hwfn, qp, true, false,
						    params->modify_flags);
		return rc;

	} else if ((prev_state == ECORE_ROCE_QP_STATE_SQD) &&
		   (qp->cur_state == ECORE_ROCE_QP_STATE_SQD))
	{
		/* SQD->SQD */
		rc = ecore_roce_sp_modify_responder(p_hwfn, qp, false,
						    params->modify_flags);
		if (rc != ECORE_SUCCESS)
			return rc;

		rc = ecore_roce_sp_modify_requester(p_hwfn,  qp, false, false,
						    params->modify_flags);
		return rc;

	} else if ((prev_state == ECORE_ROCE_QP_STATE_SQD) &&
		 (qp->cur_state == ECORE_ROCE_QP_STATE_RTS))
	{
		/* SQD->RTS */
		rc = ecore_roce_sp_modify_responder(p_hwfn,  qp, false,
						    params->modify_flags);
		if (rc != ECORE_SUCCESS)
			return rc;

		rc = ecore_roce_sp_modify_requester(p_hwfn,  qp, false, false,
						    params->modify_flags);

		return rc;
	} else if (qp->cur_state == ECORE_ROCE_QP_STATE_ERR) {
		/* ->ERR */
		rc = ecore_roce_sp_modify_responder(p_hwfn, qp, true,
						    params->modify_flags);
		if (rc != ECORE_SUCCESS)
			return rc;

		rc = ecore_roce_sp_modify_requester(p_hwfn, qp, false, true,
						    params->modify_flags);
		return rc;

	} else if (qp->cur_state == ECORE_ROCE_QP_STATE_RESET) {
		/* Any state -> RESET */

		/* Send destroy responder ramrod */
		rc = ecore_roce_sp_destroy_qp_responder(p_hwfn, qp,
							&num_invalidated_mw,
							&qp->cq_prod.resp);

		if (rc != ECORE_SUCCESS)
			return rc;

		rc = ecore_roce_sp_destroy_qp_requester(p_hwfn, qp,
							&num_bound_mw,
							&qp->cq_prod.req);


		if (rc != ECORE_SUCCESS)
			return rc;

		if (num_invalidated_mw != num_bound_mw) {
			DP_NOTICE(p_hwfn,
				  true,
				  "number of invalidate memory windows is different from bounded ones\n");
			return ECORE_INVAL;
		}
	} else {
		DP_VERBOSE(p_hwfn, ECORE_MSG_RDMA, "ECORE_SUCCESS\n");
	}

	return rc;
}