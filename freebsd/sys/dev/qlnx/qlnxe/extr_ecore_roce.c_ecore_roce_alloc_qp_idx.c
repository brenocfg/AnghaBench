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
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct ecore_rdma_info {int /*<<< orphan*/  proto; int /*<<< orphan*/  lock; int /*<<< orphan*/  qp_map; } ;
struct ecore_hwfn {struct ecore_rdma_info* p_rdma_info; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ECORE_ELEM_CXT ; 
 int /*<<< orphan*/  ECORE_MSG_RDMA ; 
 scalar_t__ ECORE_ROCE_QP_TO_ICID (scalar_t__) ; 
 int ECORE_SUCCESS ; 
 int ECORE_UNKNOWN_ERROR ; 
 int /*<<< orphan*/  OSAL_SPIN_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSAL_SPIN_UNLOCK (int /*<<< orphan*/ *) ; 
 int ecore_cxt_dynamic_ilt_alloc (struct ecore_hwfn*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ ecore_cxt_get_proto_cid_start (struct ecore_hwfn*,int /*<<< orphan*/ ) ; 
 int ecore_rdma_bmap_alloc_id (struct ecore_hwfn*,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  ecore_roce_free_qp (struct ecore_hwfn*,scalar_t__) ; 
 int ecore_roce_wait_free_cids (struct ecore_hwfn*,scalar_t__) ; 

enum _ecore_status_t ecore_roce_alloc_qp_idx(
		struct ecore_hwfn *p_hwfn, u16 *qp_idx16)
{
	struct ecore_rdma_info *p_rdma_info = p_hwfn->p_rdma_info;
	u32 start_cid, icid, cid, qp_idx;
	enum _ecore_status_t rc;

	OSAL_SPIN_LOCK(&p_rdma_info->lock);
	rc = ecore_rdma_bmap_alloc_id(p_hwfn, &p_rdma_info->qp_map, &qp_idx);
	if (rc != ECORE_SUCCESS) {
		DP_NOTICE(p_hwfn, false, "failed to allocate qp\n");
		OSAL_SPIN_UNLOCK(&p_rdma_info->lock);
		return rc;
	}

	OSAL_SPIN_UNLOCK(&p_rdma_info->lock);

	/* Verify the cid bits that of this qp index are clear */
	rc = ecore_roce_wait_free_cids(p_hwfn, qp_idx);
	if (rc) {
		rc = ECORE_UNKNOWN_ERROR;
		goto err;
	}

	/* Allocate a DMA-able context for an ILT page, if not existing, for the
	 * associated iids.
	 * Note: If second allocation fails there's no need to free the first as
	 *       it will be used in the future.
	 */
	icid = ECORE_ROCE_QP_TO_ICID(qp_idx);
	start_cid = ecore_cxt_get_proto_cid_start(p_hwfn, p_rdma_info->proto);
	cid = start_cid + icid;

	rc = ecore_cxt_dynamic_ilt_alloc(p_hwfn, ECORE_ELEM_CXT, cid);
	if (rc != ECORE_SUCCESS)
		goto err;

	rc = ecore_cxt_dynamic_ilt_alloc(p_hwfn, ECORE_ELEM_CXT, cid + 1);
	if (rc != ECORE_SUCCESS)
		goto err;

	/* qp index is under 2^16 */
	*qp_idx16 = (u16)qp_idx;

	return ECORE_SUCCESS;

err:
	ecore_roce_free_qp(p_hwfn, (u16)qp_idx);

	DP_VERBOSE(p_hwfn, ECORE_MSG_RDMA, "rc = %d\n", rc);

	return rc;
}