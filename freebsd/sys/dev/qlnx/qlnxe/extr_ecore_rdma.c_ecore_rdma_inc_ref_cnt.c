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
struct ecore_hwfn {TYPE_1__* p_rdma_info; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  ref_cnt; scalar_t__ active; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_INFO (struct ecore_hwfn*,char*) ; 
 int ECORE_INVAL ; 
 int ECORE_SUCCESS ; 
 int /*<<< orphan*/  OSAL_SPIN_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSAL_SPIN_UNLOCK (int /*<<< orphan*/ *) ; 

__attribute__((used)) static enum _ecore_status_t ecore_rdma_inc_ref_cnt(struct ecore_hwfn *p_hwfn)
{
	enum _ecore_status_t rc = ECORE_INVAL;

	OSAL_SPIN_LOCK(&p_hwfn->p_rdma_info->lock);
	if (p_hwfn->p_rdma_info->active) {
		p_hwfn->p_rdma_info->ref_cnt++;
		rc = ECORE_SUCCESS;
	} else {
		DP_INFO(p_hwfn, "Ref cnt requested for inactive rdma\n");
	}
	OSAL_SPIN_UNLOCK(&p_hwfn->p_rdma_info->lock);
	return rc;
}