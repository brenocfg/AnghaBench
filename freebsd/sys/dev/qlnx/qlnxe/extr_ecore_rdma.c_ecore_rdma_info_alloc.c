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
struct ecore_rdma_info {int /*<<< orphan*/  lock; } ;
struct ecore_hwfn {struct ecore_rdma_info* p_rdma_info; int /*<<< orphan*/  p_dev; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*) ; 
 int ECORE_NOMEM ; 
 int ECORE_SUCCESS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ OSAL_SPIN_LOCK_ALLOC (struct ecore_hwfn*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSAL_SPIN_LOCK_INIT (int /*<<< orphan*/ *) ; 
 struct ecore_rdma_info* OSAL_ZALLOC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ecore_rdma_info_free (struct ecore_hwfn*) ; 

enum _ecore_status_t ecore_rdma_info_alloc(struct ecore_hwfn    *p_hwfn)
{
	struct ecore_rdma_info *p_rdma_info;

	p_rdma_info = OSAL_ZALLOC(p_hwfn->p_dev, GFP_KERNEL, sizeof(*p_rdma_info));
	if (!p_rdma_info) {
		DP_NOTICE(p_hwfn, false,
			  "ecore rdma alloc failed: cannot allocate memory (rdma info).\n");
		return ECORE_NOMEM;
	}
	p_hwfn->p_rdma_info = p_rdma_info;

#ifdef CONFIG_ECORE_LOCK_ALLOC
	if (OSAL_SPIN_LOCK_ALLOC(p_hwfn, &p_rdma_info->lock)) {
		ecore_rdma_info_free(p_hwfn);
		return ECORE_NOMEM;
	}
#endif
	OSAL_SPIN_LOCK_INIT(&p_rdma_info->lock);

	return ECORE_SUCCESS;
}