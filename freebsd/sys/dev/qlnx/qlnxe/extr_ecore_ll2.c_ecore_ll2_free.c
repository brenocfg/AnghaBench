#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ecore_hwfn {TYPE_3__* p_ll2_info; int /*<<< orphan*/  p_dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  lock; } ;
struct TYPE_6__ {int /*<<< orphan*/  lock; } ;
struct TYPE_7__ {int /*<<< orphan*/  mutex; TYPE_1__ tx_queue; TYPE_2__ rx_queue; } ;

/* Variables and functions */
 int ECORE_MAX_NUM_OF_LL2_CONNECTIONS ; 
 int /*<<< orphan*/  OSAL_FREE (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  OSAL_MUTEX_DEALLOC (int /*<<< orphan*/ *) ; 
 TYPE_3__* OSAL_NULL ; 
 int /*<<< orphan*/  OSAL_SPIN_LOCK_DEALLOC (int /*<<< orphan*/ *) ; 

void ecore_ll2_free(struct ecore_hwfn *p_hwfn)
{
#ifdef CONFIG_ECORE_LOCK_ALLOC
	int i;
#endif
	if (!p_hwfn->p_ll2_info)
		return;

#ifdef CONFIG_ECORE_LOCK_ALLOC
	for (i = 0; i < ECORE_MAX_NUM_OF_LL2_CONNECTIONS; i++) {
		OSAL_SPIN_LOCK_DEALLOC(&p_hwfn->p_ll2_info[i].rx_queue.lock);
		OSAL_SPIN_LOCK_DEALLOC(&p_hwfn->p_ll2_info[i].tx_queue.lock);
		OSAL_MUTEX_DEALLOC(&p_hwfn->p_ll2_info[i].mutex);
	}
#endif
	OSAL_FREE(p_hwfn->p_dev, p_hwfn->p_ll2_info);
	p_hwfn->p_ll2_info = OSAL_NULL;
}