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
struct TYPE_3__ {size_t queue_id; } ;
struct ecore_queue_cid {TYPE_1__ rel; int /*<<< orphan*/  qid_usage_idx; } ;
struct ecore_hwfn {TYPE_2__* p_l2_info; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; int /*<<< orphan*/ * pp_qid_usage; } ;

/* Variables and functions */
 int /*<<< orphan*/  OSAL_CLEAR_BIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSAL_MUTEX_ACQUIRE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSAL_MUTEX_RELEASE (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ecore_eth_queue_qid_usage_del(struct ecore_hwfn *p_hwfn,
					  struct ecore_queue_cid *p_cid)
{
	OSAL_MUTEX_ACQUIRE(&p_hwfn->p_l2_info->lock);

	OSAL_CLEAR_BIT(p_cid->qid_usage_idx,
		       p_hwfn->p_l2_info->pp_qid_usage[p_cid->rel.queue_id]);

	OSAL_MUTEX_RELEASE(&p_hwfn->p_l2_info->lock);
}