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
typedef  int /*<<< orphan*/  u32 ;
struct ecore_hwfn {TYPE_1__* p_rdma_info; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  tid_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ECORE_ELEM_TASK ; 
 int /*<<< orphan*/  ECORE_MSG_RDMA ; 
 int ECORE_SUCCESS ; 
 int /*<<< orphan*/  OSAL_SPIN_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSAL_SPIN_UNLOCK (int /*<<< orphan*/ *) ; 
 int ecore_cxt_dynamic_ilt_alloc (struct ecore_hwfn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ecore_rdma_bmap_alloc_id (struct ecore_hwfn*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

enum _ecore_status_t ecore_rdma_alloc_tid(void	*rdma_cxt,
					  u32	*itid)
{
	struct ecore_hwfn *p_hwfn = (struct ecore_hwfn *)rdma_cxt;
	enum _ecore_status_t rc;

	DP_VERBOSE(p_hwfn, ECORE_MSG_RDMA, "Allocate TID\n");

	OSAL_SPIN_LOCK(&p_hwfn->p_rdma_info->lock);
	rc = ecore_rdma_bmap_alloc_id(p_hwfn,
				      &p_hwfn->p_rdma_info->tid_map,
				      itid);
	OSAL_SPIN_UNLOCK(&p_hwfn->p_rdma_info->lock);
	if (rc != ECORE_SUCCESS) {
		DP_NOTICE(p_hwfn, false, "Failed in allocating tid\n");
		goto out;
	}

	rc = ecore_cxt_dynamic_ilt_alloc(p_hwfn, ECORE_ELEM_TASK, *itid);
out:
	DP_VERBOSE(p_hwfn, ECORE_MSG_RDMA, "Allocate TID - done, rc = %d\n", rc);
	return rc;
}