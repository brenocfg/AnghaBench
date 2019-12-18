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
struct TYPE_11__ {size_t instance; TYPE_3__* cq; } ;
typedef  TYPE_4__ hw_wq_t ;
struct TYPE_10__ {TYPE_1__* eq; int /*<<< orphan*/  q_list; } ;
struct TYPE_9__ {int /*<<< orphan*/  os; int /*<<< orphan*/ ** hw_wq; } ;
struct TYPE_8__ {TYPE_2__* hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  ocs_free (int /*<<< orphan*/ ,TYPE_4__*,int) ; 
 int /*<<< orphan*/  ocs_list_remove (int /*<<< orphan*/ *,TYPE_4__*) ; 

void
hw_del_wq(hw_wq_t *wq)
{
	if (wq != NULL) {
		ocs_list_remove(&wq->cq->q_list, wq);
		wq->cq->eq->hw->hw_wq[wq->instance] = NULL;
		ocs_free(wq->cq->eq->hw->os, wq, sizeof(*wq));
	}
}