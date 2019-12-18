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
struct task {scalar_t__ ta_pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct task*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ soaio_idle ; 
 int /*<<< orphan*/  soaio_jobs ; 
 int /*<<< orphan*/  soaio_jobs_lock ; 
 int /*<<< orphan*/  soaio_kproc_task ; 
 scalar_t__ soaio_max_procs ; 
 scalar_t__ soaio_num_procs ; 
 scalar_t__ soaio_queued ; 
 int /*<<< orphan*/  ta_link ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_thread ; 
 int /*<<< orphan*/  wakeup_one (scalar_t__*) ; 

void
soaio_enqueue(struct task *task)
{

	mtx_lock(&soaio_jobs_lock);
	MPASS(task->ta_pending == 0);
	task->ta_pending++;
	STAILQ_INSERT_TAIL(&soaio_jobs, task, ta_link);
	soaio_queued++;
	if (soaio_queued <= soaio_idle)
		wakeup_one(&soaio_idle);
	else if (soaio_num_procs < soaio_max_procs)
		taskqueue_enqueue(taskqueue_thread, &soaio_kproc_task);
	mtx_unlock(&soaio_jobs_lock);
}