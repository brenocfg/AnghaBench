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
struct kaiocb {int /*<<< orphan*/  userproc; int /*<<< orphan*/ * handle_fn; } ;
typedef  int /*<<< orphan*/  aio_handle_fn_t ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct kaiocb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aio_cancel (struct kaiocb*) ; 
 int /*<<< orphan*/  aio_cancel_daemon_job ; 
 int /*<<< orphan*/  aio_job_mtx ; 
 int /*<<< orphan*/  aio_jobs ; 
 int /*<<< orphan*/  aio_kick_nowait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aio_set_cancel_function (struct kaiocb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

void
aio_schedule(struct kaiocb *job, aio_handle_fn_t *func)
{

	mtx_lock(&aio_job_mtx);
	if (!aio_set_cancel_function(job, aio_cancel_daemon_job)) {
		mtx_unlock(&aio_job_mtx);
		aio_cancel(job);
		return;
	}
	job->handle_fn = func;
	TAILQ_INSERT_TAIL(&aio_jobs, job, list);
	aio_kick_nowait(job->userproc);
	mtx_unlock(&aio_job_mtx);
}