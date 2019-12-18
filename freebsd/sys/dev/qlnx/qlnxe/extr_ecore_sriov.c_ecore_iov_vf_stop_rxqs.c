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
typedef  size_t u8 ;
typedef  size_t u16 ;
struct ecore_vf_queue {TYPE_1__* cids; } ;
struct ecore_vf_info {int /*<<< orphan*/  num_active_rxqs; int /*<<< orphan*/  relative_vf_id; struct ecore_vf_queue* vf_queues; } ;
struct ecore_queue_cid {int /*<<< orphan*/  qid_usage_idx; } ;
struct ecore_hwfn {int dummy; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;
struct TYPE_2__ {scalar_t__ p_cid; scalar_t__ b_is_tx; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,size_t,size_t,...) ; 
 int ECORE_INVAL ; 
 int /*<<< orphan*/  ECORE_IOV_VALIDATE_Q_NA ; 
 int /*<<< orphan*/  ECORE_MSG_IOV ; 
 int ECORE_SUCCESS ; 
 scalar_t__ OSAL_NULL ; 
 int ecore_eth_rx_queue_stop (struct ecore_hwfn*,scalar_t__,int,int) ; 
 struct ecore_queue_cid* ecore_iov_get_vf_rx_queue_cid (struct ecore_vf_queue*) ; 
 int /*<<< orphan*/  ecore_iov_validate_rxq (struct ecore_hwfn*,struct ecore_vf_info*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum _ecore_status_t ecore_iov_vf_stop_rxqs(struct ecore_hwfn *p_hwfn,
						   struct ecore_vf_info *vf,
						   u16 rxq_id,
						   u8 qid_usage_idx,
						   bool cqe_completion)
{
	struct ecore_vf_queue *p_queue;
	enum _ecore_status_t rc = ECORE_SUCCESS;

	if (!ecore_iov_validate_rxq(p_hwfn, vf, rxq_id,
				    ECORE_IOV_VALIDATE_Q_NA)) {
		DP_VERBOSE(p_hwfn, ECORE_MSG_IOV,
			   "VF[%d] Tried Closing Rx 0x%04x.%02x which is inactive\n",
			   vf->relative_vf_id, rxq_id, qid_usage_idx);
		return ECORE_INVAL;
	}

	p_queue = &vf->vf_queues[rxq_id];

	/* We've validated the index and the existance of the active RXQ -
	 * now we need to make sure that it's using the correct qid.
	 */
	if (!p_queue->cids[qid_usage_idx].p_cid ||
	    p_queue->cids[qid_usage_idx].b_is_tx) {
		struct ecore_queue_cid *p_cid;

		p_cid = ecore_iov_get_vf_rx_queue_cid(p_queue);
		DP_VERBOSE(p_hwfn, ECORE_MSG_IOV,
			   "VF[%d] - Tried Closing Rx 0x%04x.%02x, but Rx is at %04x.%02x\n",
			    vf->relative_vf_id, rxq_id, qid_usage_idx,
			    rxq_id, p_cid->qid_usage_idx);
		return ECORE_INVAL;
	}

	/* Now that we know we have a valid Rx-queue - close it */
	rc = ecore_eth_rx_queue_stop(p_hwfn,
				     p_queue->cids[qid_usage_idx].p_cid,
				     false, cqe_completion);
	if (rc != ECORE_SUCCESS)
		return rc;

	p_queue->cids[qid_usage_idx].p_cid = OSAL_NULL;
	vf->num_active_rxqs--;

	return ECORE_SUCCESS;
}