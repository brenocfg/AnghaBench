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
struct ecore_rdma_info {int /*<<< orphan*/  lock; int /*<<< orphan*/  cid_map; } ;
struct ecore_hwfn {int /*<<< orphan*/  p_dev; struct ecore_rdma_info* p_rdma_info; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ERR (int /*<<< orphan*/ ,char*,int,int) ; 
 int ECORE_AGAIN ; 
 scalar_t__ ECORE_ROCE_CREATE_QP_ATTEMPTS ; 
 int /*<<< orphan*/  ECORE_ROCE_CREATE_QP_MSLEEP ; 
 scalar_t__ ECORE_ROCE_QP_TO_ICID (scalar_t__) ; 
 int ECORE_SUCCESS ; 
 int /*<<< orphan*/  OSAL_MSLEEP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSAL_SPIN_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSAL_SPIN_UNLOCK (int /*<<< orphan*/ *) ; 
 int ecore_bmap_test_id (struct ecore_hwfn*,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static enum _ecore_status_t ecore_roce_wait_free_cids(struct ecore_hwfn *p_hwfn, u32 qp_idx)
{
	struct ecore_rdma_info *p_rdma_info = p_hwfn->p_rdma_info;
	bool cids_free = false;
	u32 icid, iter = 0;
	int req, resp;

	icid = ECORE_ROCE_QP_TO_ICID(qp_idx);

	/* Make sure that the cids that were used by the QP index are free.
	 * This is necessary because the destroy flow returns to the user before
	 * the device finishes clean up.
	 * It can happen in the following flows:
	 * (1) ib_destroy_qp followed by an ib_create_qp
	 * (2) ib_modify_qp to RESET followed (not immediately), by an
	 *     ib_modify_qp to RTR
	 */

	do {
		OSAL_SPIN_LOCK(&p_rdma_info->lock);
		resp = ecore_bmap_test_id(p_hwfn, &p_rdma_info->cid_map, icid);
		req = ecore_bmap_test_id(p_hwfn, &p_rdma_info->cid_map, icid + 1);
		if (!resp && !req)
			cids_free = true;

		OSAL_SPIN_UNLOCK(&p_rdma_info->lock);

		if (!cids_free) {
			OSAL_MSLEEP(ECORE_ROCE_CREATE_QP_MSLEEP);
			iter++;
		}
	} while (!cids_free && iter < ECORE_ROCE_CREATE_QP_ATTEMPTS);

	if (!cids_free) {
		DP_ERR(p_hwfn->p_dev,
		       "responder and/or requester CIDs are still in use. resp=%d, req=%d\n",
		       resp, req);
		return ECORE_AGAIN;
	}

	return ECORE_SUCCESS;
}