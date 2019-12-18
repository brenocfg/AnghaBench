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
 int /*<<< orphan*/  __add_wait_queue (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_task_state (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void
linux_prepare_to_wait(wait_queue_head_t *wqh, wait_queue_t *wq, int state)
{

	spin_lock(&wqh->lock);
	if (list_empty(&wq->task_list))
		__add_wait_queue(wqh, wq);
	set_task_state(current, state);
	spin_unlock(&wqh->lock);
}