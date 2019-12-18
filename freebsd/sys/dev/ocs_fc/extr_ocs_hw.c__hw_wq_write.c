#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int wqec; } ;
typedef  TYPE_2__ sli4_generic_wqe_t ;
struct TYPE_10__ {scalar_t__ wqebuf; } ;
typedef  TYPE_3__ ocs_hw_wqe_t ;
typedef  scalar_t__ int32_t ;
struct TYPE_11__ {scalar_t__ wqec_count; scalar_t__ wqec_set_count; TYPE_5__* queue; TYPE_1__* hw; int /*<<< orphan*/  free_count; } ;
typedef  TYPE_4__ hw_wq_t ;
struct TYPE_12__ {int /*<<< orphan*/  id; } ;
struct TYPE_8__ {int /*<<< orphan*/  q_hist; int /*<<< orphan*/  sli; } ;

/* Variables and functions */
 scalar_t__ _sli_queue_write (int /*<<< orphan*/ *,TYPE_5__*,scalar_t__) ; 
 int /*<<< orphan*/  ocs_queue_history_wq (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int32_t
_hw_wq_write(hw_wq_t *wq, ocs_hw_wqe_t *wqe)
{
	int32_t rc;
	int32_t queue_rc;

	/* Every so often, set the wqec bit to generate comsummed completions */
	if (wq->wqec_count) {
		wq->wqec_count--;
	}
	if (wq->wqec_count == 0) {
		sli4_generic_wqe_t *genwqe = (void*)wqe->wqebuf;
		genwqe->wqec = 1;
		wq->wqec_count = wq->wqec_set_count;
	}

	/* Decrement WQ free count */
	wq->free_count--;

	queue_rc = _sli_queue_write(&wq->hw->sli, wq->queue, wqe->wqebuf);

	if (queue_rc < 0) {
		rc = -1;
	} else {
		rc = 0;
		ocs_queue_history_wq(&wq->hw->q_hist, (void *) wqe->wqebuf, wq->queue->id, queue_rc);
	}

	return rc;
}