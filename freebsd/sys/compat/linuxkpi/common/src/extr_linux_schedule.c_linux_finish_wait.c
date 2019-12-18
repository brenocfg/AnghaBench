#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  task_list; } ;
typedef  TYPE_1__ wait_queue_t ;
struct TYPE_8__ {int /*<<< orphan*/  lock; } ;
typedef  TYPE_2__ wait_queue_head_t ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  __remove_wait_queue (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_task_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void
linux_finish_wait(wait_queue_head_t *wqh, wait_queue_t *wq)
{

	spin_lock(&wqh->lock);
	set_task_state(current, TASK_RUNNING);
	if (!list_empty(&wq->task_list)) {
		__remove_wait_queue(wqh, wq);
		INIT_LIST_HEAD(&wq->task_list);
	}
	spin_unlock(&wqh->lock);
}