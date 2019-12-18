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
struct proc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RFNOWAIT ; 
 int /*<<< orphan*/  aio_daemon ; 
 int /*<<< orphan*/  aio_job_mtx ; 
 int /*<<< orphan*/  aio_newproc_sem ; 
 int /*<<< orphan*/  aiod_unr ; 
 int alloc_unr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_unr (int /*<<< orphan*/ ,int) ; 
 int kproc_create (int /*<<< orphan*/ ,void*,struct proc**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  num_aio_procs ; 
 int /*<<< orphan*/  sema_wait (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
aio_newproc(int *start)
{
	int error;
	struct proc *p;
	int id;

	id = alloc_unr(aiod_unr);
	error = kproc_create(aio_daemon, (void *)(intptr_t)id, &p,
		RFNOWAIT, 0, "aiod%d", id);
	if (error == 0) {
		/*
		 * Wait until daemon is started.
		 */
		sema_wait(&aio_newproc_sem);
		mtx_lock(&aio_job_mtx);
		num_aio_procs++;
		if (start != NULL)
			(*start)--;
		mtx_unlock(&aio_job_mtx);
	} else {
		free_unr(aiod_unr, id);
	}
	return (error);
}