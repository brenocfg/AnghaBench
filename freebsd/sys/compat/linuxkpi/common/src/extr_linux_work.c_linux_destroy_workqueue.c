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
struct workqueue_struct {int /*<<< orphan*/  exec_mtx; int /*<<< orphan*/  taskqueue; int /*<<< orphan*/  draining; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drain_workqueue (struct workqueue_struct*) ; 
 int /*<<< orphan*/  kfree (struct workqueue_struct*) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_free (int /*<<< orphan*/ ) ; 

void
linux_destroy_workqueue(struct workqueue_struct *wq)
{
	atomic_inc(&wq->draining);
	drain_workqueue(wq);
	taskqueue_free(wq->taskqueue);
	mtx_destroy(&wq->exec_mtx);
	kfree(wq);
}