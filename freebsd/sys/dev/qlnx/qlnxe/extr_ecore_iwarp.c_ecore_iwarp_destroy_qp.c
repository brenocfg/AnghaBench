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
struct ecore_rdma_qp {scalar_t__ iwarp_state; int /*<<< orphan*/  shared_queue_phys_addr; scalar_t__ shared_queue; int /*<<< orphan*/  icid; struct ecore_iwarp_ep* ep; } ;
struct ecore_iwarp_fpdu {scalar_t__ incomplete_bytes; } ;
struct ecore_iwarp_ep {scalar_t__ state; } ;
struct ecore_hwfn {int /*<<< orphan*/  p_dev; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*,scalar_t__) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ ECORE_IWARP_EP_CLOSED ; 
 scalar_t__ ECORE_IWARP_QP_STATE_ERROR ; 
 int /*<<< orphan*/  ECORE_MSG_RDMA ; 
 int ECORE_SUCCESS ; 
 int /*<<< orphan*/  IWARP_SHARED_QUEUE_PAGE_SIZE ; 
 int /*<<< orphan*/  OSAL_DMA_FREE_COHERENT (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSAL_MSLEEP (int) ; 
 int /*<<< orphan*/  ecore_iwarp_destroy_ep (struct ecore_hwfn*,struct ecore_iwarp_ep*,int) ; 
 int ecore_iwarp_fw_destroy (struct ecore_hwfn*,struct ecore_rdma_qp*) ; 
 struct ecore_iwarp_fpdu* ecore_iwarp_get_curr_fpdu (struct ecore_hwfn*,int /*<<< orphan*/ ) ; 
 int ecore_iwarp_modify_qp (struct ecore_hwfn*,struct ecore_rdma_qp*,scalar_t__,int) ; 

enum _ecore_status_t
ecore_iwarp_destroy_qp(struct ecore_hwfn *p_hwfn,
		       struct ecore_rdma_qp *qp)
{
	enum _ecore_status_t rc = ECORE_SUCCESS;
	struct ecore_iwarp_ep *ep = qp->ep;
	struct ecore_iwarp_fpdu *fpdu;
	int wait_count = 0;

	fpdu = ecore_iwarp_get_curr_fpdu(p_hwfn, qp->icid);
	if (fpdu && fpdu->incomplete_bytes)
		DP_NOTICE(p_hwfn, false,
			  "Pending Partial fpdu with incomplete bytes=%d\n",
			  fpdu->incomplete_bytes);

	if (qp->iwarp_state != ECORE_IWARP_QP_STATE_ERROR) {

		rc = ecore_iwarp_modify_qp(p_hwfn, qp,
					   ECORE_IWARP_QP_STATE_ERROR,
					   false);

		if (rc != ECORE_SUCCESS)
			return rc;
	}

	/* Make sure ep is closed before returning and freeing memory. */
	if (ep) {
		while (ep->state != ECORE_IWARP_EP_CLOSED) {
			DP_VERBOSE(p_hwfn, ECORE_MSG_RDMA,
				   "Waiting for ep->state to be closed...state=%x\n",
				   ep->state);

			OSAL_MSLEEP(100);
			if (wait_count++ > 200) {
				DP_NOTICE(p_hwfn, false, "ep state close timeout state=%x\n",
					  ep->state);
				break;
			}
		}

		ecore_iwarp_destroy_ep(p_hwfn, ep, false);
	}

	rc = ecore_iwarp_fw_destroy(p_hwfn, qp);

	if (qp->shared_queue)
		OSAL_DMA_FREE_COHERENT(p_hwfn->p_dev,
				       qp->shared_queue,
				       qp->shared_queue_phys_addr,
				       IWARP_SHARED_QUEUE_PAGE_SIZE);

	return rc;
}