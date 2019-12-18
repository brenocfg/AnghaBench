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
typedef  scalar_t__ u8 ;
typedef  size_t u16 ;
struct TYPE_2__ {size_t queue_id; } ;
struct ecore_queue_cid {scalar_t__ qid_usage_idx; TYPE_1__ rel; } ;
struct ecore_l2_info {size_t queues; int /*<<< orphan*/  lock; int /*<<< orphan*/ * pp_qid_usage; } ;
struct ecore_hwfn {struct ecore_l2_info* p_l2_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*,size_t,size_t) ; 
 scalar_t__ MAX_QUEUES_PER_QZONE ; 
 scalar_t__ OSAL_FIND_FIRST_ZERO_BIT (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  OSAL_MUTEX_ACQUIRE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSAL_MUTEX_RELEASE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSAL_SET_BIT (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool ecore_eth_queue_qid_usage_add(struct ecore_hwfn *p_hwfn,
					  struct ecore_queue_cid *p_cid)
{
	struct ecore_l2_info *p_l2_info = p_hwfn->p_l2_info;
	u16 queue_id = p_cid->rel.queue_id;
	bool b_rc = true;
	u8 first;

	OSAL_MUTEX_ACQUIRE(&p_l2_info->lock);

	if (queue_id > p_l2_info->queues) {
		DP_NOTICE(p_hwfn, true,
			  "Requested to increase usage for qzone %04x out of %08x\n",
			  queue_id, p_l2_info->queues);
		b_rc = false;
		goto out;
	}

	first = (u8)OSAL_FIND_FIRST_ZERO_BIT(p_l2_info->pp_qid_usage[queue_id],
					     MAX_QUEUES_PER_QZONE);
	if (first >= MAX_QUEUES_PER_QZONE) {
		b_rc = false;
		goto out;
	}

	OSAL_SET_BIT(first, p_l2_info->pp_qid_usage[queue_id]);
	p_cid->qid_usage_idx = first;

out:
	OSAL_MUTEX_RELEASE(&p_l2_info->lock);
	return b_rc;
}