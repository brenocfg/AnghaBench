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
struct ecore_hwfn {TYPE_1__* p_rdma_info; } ;
struct TYPE_4__ {int /*<<< orphan*/  bitmap; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; TYPE_2__ qp_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  OSAL_SPIN_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSAL_SPIN_UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ecore_bmap_is_empty (TYPE_2__*) ; 

bool ecore_rdma_allocated_qps(struct ecore_hwfn *p_hwfn)
{
	bool result;

	/* if rdma info has not been allocated, naturally there are no qps */
	if (!p_hwfn->p_rdma_info)
		return false;

	OSAL_SPIN_LOCK(&p_hwfn->p_rdma_info->lock);
	if (!p_hwfn->p_rdma_info->qp_map.bitmap)
		result = false;
	else
		result = !ecore_bmap_is_empty(&p_hwfn->p_rdma_info->qp_map);
	OSAL_SPIN_UNLOCK(&p_hwfn->p_rdma_info->lock);
	return result;
}