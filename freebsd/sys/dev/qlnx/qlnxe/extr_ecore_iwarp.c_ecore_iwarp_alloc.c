#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ecore_hwfn {TYPE_2__* p_rdma_info; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;
struct TYPE_3__ {int /*<<< orphan*/  ep_free_list; int /*<<< orphan*/  qp_lock; int /*<<< orphan*/  iw_lock; } ;
struct TYPE_4__ {TYPE_1__ iwarp; int /*<<< orphan*/  tcp_cid_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ECORE_IWARP_PREALLOC_CNT ; 
 int /*<<< orphan*/  ECORE_MSG_RDMA ; 
 int ECORE_SUCCESS ; 
 int /*<<< orphan*/  OSAL_LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSAL_SPIN_LOCK_ALLOC (struct ecore_hwfn*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSAL_SPIN_LOCK_INIT (int /*<<< orphan*/ *) ; 
 int ecore_iwarp_prealloc_ep (struct ecore_hwfn*,int) ; 
 int ecore_ooo_alloc (struct ecore_hwfn*) ; 
 int ecore_rdma_bmap_alloc (struct ecore_hwfn*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

enum _ecore_status_t
ecore_iwarp_alloc(struct ecore_hwfn *p_hwfn)
{
	enum _ecore_status_t rc;

#ifdef CONFIG_ECORE_LOCK_ALLOC
	OSAL_SPIN_LOCK_ALLOC(p_hwfn, &p_hwfn->p_rdma_info->iwarp.iw_lock);
	OSAL_SPIN_LOCK_ALLOC(p_hwfn, &p_hwfn->p_rdma_info->iwarp.qp_lock);
#endif
	OSAL_SPIN_LOCK_INIT(&p_hwfn->p_rdma_info->iwarp.iw_lock);
	OSAL_SPIN_LOCK_INIT(&p_hwfn->p_rdma_info->iwarp.qp_lock);

	/* Allocate bitmap for tcp cid. These are used by passive side
	 * to ensure it can allocate a tcp cid during dpc that was
	 * pre-acquired and doesn't require dynamic allocation of ilt
	 */
	rc = ecore_rdma_bmap_alloc(p_hwfn, &p_hwfn->p_rdma_info->tcp_cid_map,
				   ECORE_IWARP_PREALLOC_CNT,
				   "TCP_CID");
	if (rc != ECORE_SUCCESS) {
		DP_VERBOSE(p_hwfn, ECORE_MSG_RDMA,
			   "Failed to allocate tcp cid, rc = %d\n",
			   rc);
		return rc;
	}

	OSAL_LIST_INIT(&p_hwfn->p_rdma_info->iwarp.ep_free_list);
//DAVIDS	OSAL_SPIN_LOCK_INIT(&p_hwfn->p_rdma_info->iwarp.iw_lock);
	rc = ecore_iwarp_prealloc_ep(p_hwfn, true);
	if (rc != ECORE_SUCCESS) {
		DP_VERBOSE(p_hwfn, ECORE_MSG_RDMA,
			   "ecore_iwarp_prealloc_ep failed, rc = %d\n",
			   rc);
		return rc;
	}
	DP_VERBOSE(p_hwfn, ECORE_MSG_RDMA,
			   "ecore_iwarp_prealloc_ep success, rc = %d\n",
			   rc);

	return ecore_ooo_alloc(p_hwfn);
}