#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct rcu_head {int dummy; } ;
struct linux_epoch_head {int /*<<< orphan*/  lock; int /*<<< orphan*/  task; int /*<<< orphan*/  cb_head; } ;
struct callback_head {int /*<<< orphan*/  func; } ;
typedef  int /*<<< orphan*/  rcu_callback_t ;

/* Variables and functions */
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct callback_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  entry ; 
 struct linux_epoch_head linux_epoch_head ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_fast ; 

void
linux_call_rcu(struct rcu_head *context, rcu_callback_t func)
{
	struct callback_head *rcu = (struct callback_head *)context;
	struct linux_epoch_head *head = &linux_epoch_head;

	mtx_lock(&head->lock);
	rcu->func = func;
	STAILQ_INSERT_TAIL(&head->cb_head, rcu, entry);
	taskqueue_enqueue(taskqueue_fast, &head->task);
	mtx_unlock(&head->lock);
}