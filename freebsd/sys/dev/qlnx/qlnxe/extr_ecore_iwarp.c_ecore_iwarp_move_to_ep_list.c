#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ecore_iwarp_ep {int /*<<< orphan*/  list_entry; TYPE_3__* listener; } ;
struct ecore_hwfn {TYPE_2__* p_rdma_info; } ;
typedef  int /*<<< orphan*/  osal_list_t ;
struct TYPE_6__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  ep_list; } ;
struct TYPE_4__ {int /*<<< orphan*/  iw_lock; } ;
struct TYPE_5__ {TYPE_1__ iwarp; } ;

/* Variables and functions */
 int /*<<< orphan*/  OSAL_LIST_PUSH_TAIL (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSAL_LIST_REMOVE_ENTRY (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSAL_SPIN_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSAL_SPIN_UNLOCK (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ecore_iwarp_move_to_ep_list(struct ecore_hwfn *p_hwfn,
			    osal_list_t *list, struct ecore_iwarp_ep *ep)
{
	OSAL_SPIN_LOCK(&ep->listener->lock);
	OSAL_LIST_REMOVE_ENTRY(&ep->list_entry, &ep->listener->ep_list);
	OSAL_SPIN_UNLOCK(&ep->listener->lock);
	OSAL_SPIN_LOCK(&p_hwfn->p_rdma_info->iwarp.iw_lock);
	OSAL_LIST_PUSH_TAIL(&ep->list_entry, list);
	OSAL_SPIN_UNLOCK(&p_hwfn->p_rdma_info->iwarp.iw_lock);
}