#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_12__ {int /*<<< orphan*/  os; TYPE_3__** hw_mq; int /*<<< orphan*/  sli; TYPE_5__* mq; int /*<<< orphan*/  mq_count; } ;
typedef  TYPE_2__ ocs_hw_t ;
struct TYPE_13__ {size_t instance; int /*<<< orphan*/  entry_count; TYPE_5__* queue; int /*<<< orphan*/  entry_size; int /*<<< orphan*/  type; TYPE_4__* cq; } ;
typedef  TYPE_3__ hw_mq_t ;
struct TYPE_14__ {int /*<<< orphan*/  q_list; int /*<<< orphan*/  queue; TYPE_1__* eq; } ;
typedef  TYPE_4__ hw_cq_t ;
struct TYPE_15__ {int /*<<< orphan*/  id; } ;
struct TYPE_11__ {TYPE_2__* hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  OCS_HW_MQ_DEPTH ; 
 int OCS_M_NOWAIT ; 
 int OCS_M_ZERO ; 
 int /*<<< orphan*/  SLI_QTYPE_MQ ; 
 int /*<<< orphan*/  ocs_free (int /*<<< orphan*/ ,TYPE_3__*,int) ; 
 int /*<<< orphan*/  ocs_list_add_tail (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  ocs_log_debug (int /*<<< orphan*/ ,char*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_log_err (int /*<<< orphan*/ ,char*) ; 
 TYPE_3__* ocs_malloc (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ sli_queue_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

hw_mq_t*
hw_new_mq(hw_cq_t *cq, uint32_t entry_count)
{
	ocs_hw_t *hw = cq->eq->hw;
	hw_mq_t *mq = ocs_malloc(hw->os, sizeof(*mq), OCS_M_ZERO | OCS_M_NOWAIT);

	if (mq != NULL) {
		mq->cq = cq;
		mq->type = SLI_QTYPE_MQ;
		mq->instance = cq->eq->hw->mq_count++;
		mq->entry_count = entry_count;
		mq->entry_size = OCS_HW_MQ_DEPTH;
		mq->queue = &hw->mq[mq->instance];

		if (sli_queue_alloc(&hw->sli, SLI_QTYPE_MQ,
				    mq->queue,
				    mq->entry_size,
				    cq->queue, 0)) {
			ocs_log_err(hw->os, "MQ allocation failure\n");
			ocs_free(hw->os, mq, sizeof(*mq));
			mq = NULL;
		} else {
			hw->hw_mq[mq->instance] = mq;
			ocs_list_add_tail(&cq->q_list, mq);
			ocs_log_debug(hw->os, "create mq[%2d] id %3d len %4d\n", mq->instance, mq->queue->id,
				mq->entry_count);
		}
	}
	return mq;
}