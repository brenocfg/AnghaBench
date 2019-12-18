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
struct kaiocb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct kaiocb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aio_cancel (struct kaiocb*) ; 
 int /*<<< orphan*/  aio_cancel_cleared (struct kaiocb*) ; 
 int /*<<< orphan*/  aio_job_mtx ; 
 int /*<<< orphan*/  aio_jobs ; 
 int /*<<< orphan*/  list ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
aio_cancel_daemon_job(struct kaiocb *job)
{

	mtx_lock(&aio_job_mtx);
	if (!aio_cancel_cleared(job))
		TAILQ_REMOVE(&aio_jobs, job, list);
	mtx_unlock(&aio_job_mtx);
	aio_cancel(job);
}