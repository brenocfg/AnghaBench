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
struct TYPE_2__ {int active; int ref_cnt; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*,int) ; 
 int /*<<< orphan*/  ECORE_RDMA_MAX_FLOW_TIME ; 
 int ECORE_SUCCESS ; 
 int ECORE_TIMEOUT ; 
 int /*<<< orphan*/  OSAL_MSLEEP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSAL_SPIN_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSAL_SPIN_UNLOCK (int /*<<< orphan*/ *) ; 

__attribute__((used)) static enum _ecore_status_t ecore_rdma_deactivate(struct ecore_hwfn *p_hwfn)
{
	int wait_count;

	OSAL_SPIN_LOCK(&p_hwfn->p_rdma_info->lock);
	p_hwfn->p_rdma_info->active = false;
	OSAL_SPIN_UNLOCK(&p_hwfn->p_rdma_info->lock);

	/* We'll give each flow it's time to complete... */
	wait_count = p_hwfn->p_rdma_info->ref_cnt;

	while (p_hwfn->p_rdma_info->ref_cnt) {
		OSAL_MSLEEP(ECORE_RDMA_MAX_FLOW_TIME);
		if (--wait_count == 0) {
			DP_NOTICE(p_hwfn, false,
				  "Timeout on refcnt=%d\n",
				  p_hwfn->p_rdma_info->ref_cnt);
			return ECORE_TIMEOUT;
		}
	}
	return ECORE_SUCCESS;
}