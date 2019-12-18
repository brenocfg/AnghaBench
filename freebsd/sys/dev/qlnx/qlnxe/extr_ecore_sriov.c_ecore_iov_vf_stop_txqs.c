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
struct ecore_vf_info {struct ecore_vf_queue* vf_queues; } ;
struct ecore_hwfn {int dummy; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;
struct TYPE_2__ {scalar_t__ p_cid; int /*<<< orphan*/  b_is_tx; } ;

/* Variables and functions */
 int ECORE_INVAL ; 
 int /*<<< orphan*/  ECORE_IOV_VALIDATE_Q_NA ; 
 int ECORE_SUCCESS ; 
 scalar_t__ OSAL_NULL ; 
 int ecore_eth_tx_queue_stop (struct ecore_hwfn*,scalar_t__) ; 
 int /*<<< orphan*/  ecore_iov_validate_txq (struct ecore_hwfn*,struct ecore_vf_info*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum _ecore_status_t ecore_iov_vf_stop_txqs(struct ecore_hwfn *p_hwfn,
						   struct ecore_vf_info *vf,
						   u16 txq_id,
						   u8 qid_usage_idx)
{
	struct ecore_vf_queue *p_queue;
	enum _ecore_status_t rc = ECORE_SUCCESS;

	if (!ecore_iov_validate_txq(p_hwfn, vf, txq_id,
				    ECORE_IOV_VALIDATE_Q_NA))
		return ECORE_INVAL;

	p_queue = &vf->vf_queues[txq_id];
	if (!p_queue->cids[qid_usage_idx].p_cid ||
	    !p_queue->cids[qid_usage_idx].b_is_tx)
		return ECORE_INVAL;

	rc = ecore_eth_tx_queue_stop(p_hwfn,
				     p_queue->cids[qid_usage_idx].p_cid);
	if (rc != ECORE_SUCCESS)
		return rc;

	p_queue->cids[qid_usage_idx].p_cid = OSAL_NULL;
	return ECORE_SUCCESS;
}