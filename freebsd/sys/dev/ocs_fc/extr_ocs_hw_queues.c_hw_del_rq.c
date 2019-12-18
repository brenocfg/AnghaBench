#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  os; int /*<<< orphan*/ ** hw_rq; } ;
typedef  TYPE_3__ ocs_hw_t ;
typedef  int /*<<< orphan*/  ocs_hw_sequence_t ;
struct TYPE_11__ {int entry_count; size_t instance; TYPE_2__* cq; struct TYPE_11__* rq_tracker; } ;
typedef  TYPE_4__ hw_rq_t ;
struct TYPE_9__ {int /*<<< orphan*/  q_list; TYPE_1__* eq; } ;
struct TYPE_8__ {TYPE_3__* hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  ocs_free (int /*<<< orphan*/ ,TYPE_4__*,int) ; 
 int /*<<< orphan*/  ocs_list_remove (int /*<<< orphan*/ *,TYPE_4__*) ; 

void
hw_del_rq(hw_rq_t *rq)
{

	if (rq != NULL) {
		ocs_hw_t *hw = rq->cq->eq->hw;
		/* Free RQ tracker */
		if (rq->rq_tracker != NULL) {
			ocs_free(hw->os, rq->rq_tracker, sizeof(ocs_hw_sequence_t*) * rq->entry_count);
			rq->rq_tracker = NULL;
		}
		ocs_list_remove(&rq->cq->q_list, rq);
		hw->hw_rq[rq->instance] = NULL;
		ocs_free(hw->os, rq, sizeof(*rq));
	}
}