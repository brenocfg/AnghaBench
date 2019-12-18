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
struct ecore_ptt {int /*<<< orphan*/  list_entry; } ;
struct ecore_hwfn {TYPE_1__* p_ptt_pool; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  free_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  OSAL_LIST_PUSH_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSAL_SPIN_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSAL_SPIN_UNLOCK (int /*<<< orphan*/ *) ; 

void ecore_ptt_release(struct ecore_hwfn *p_hwfn,
		       struct ecore_ptt *p_ptt) {
	/* This PTT should not be set to pretend if it is being released */
	/* TODO - add some pretend sanity checks, to make sure pretend isn't set on this ptt */

	OSAL_SPIN_LOCK(&p_hwfn->p_ptt_pool->lock);
	OSAL_LIST_PUSH_HEAD(&p_ptt->list_entry, &p_hwfn->p_ptt_pool->free_list);
	OSAL_SPIN_UNLOCK(&p_hwfn->p_ptt_pool->lock);
}