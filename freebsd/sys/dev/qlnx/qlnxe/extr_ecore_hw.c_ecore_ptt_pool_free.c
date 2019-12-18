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
struct ecore_hwfn {TYPE_1__* p_ptt_pool; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  OSAL_SPIN_LOCK_DEALLOC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __ecore_ptt_pool_free (struct ecore_hwfn*) ; 

void ecore_ptt_pool_free(struct ecore_hwfn *p_hwfn)
{
#ifdef CONFIG_ECORE_LOCK_ALLOC
	if (p_hwfn->p_ptt_pool)
		OSAL_SPIN_LOCK_DEALLOC(&p_hwfn->p_ptt_pool->lock);
#endif
	__ecore_ptt_pool_free(p_hwfn);
}