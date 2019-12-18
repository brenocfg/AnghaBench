#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ecore_hwfn {TYPE_1__* p_rdma_info; int /*<<< orphan*/  p_dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  OSAL_FREE (int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__* OSAL_NULL ; 
 int /*<<< orphan*/  OSAL_SPIN_LOCK_DEALLOC (int /*<<< orphan*/ *) ; 

void ecore_rdma_info_free(struct ecore_hwfn *p_hwfn)
{
#ifdef CONFIG_ECORE_LOCK_ALLOC
	OSAL_SPIN_LOCK_DEALLOC(&p_hwfn->p_rdma_info->lock);
#endif
	OSAL_FREE(p_hwfn->p_dev, p_hwfn->p_rdma_info);
	p_hwfn->p_rdma_info = OSAL_NULL;
}