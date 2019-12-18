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
struct vmspace {int dummy; } ;
struct task {int ta_pending; int /*<<< orphan*/  ta_context; int /*<<< orphan*/  (* ta_func ) (int /*<<< orphan*/ ,int) ;} ;
struct proc {struct vmspace* p_vmspace; } ;

/* Variables and functions */
 int EWOULDBLOCK ; 
 int /*<<< orphan*/  MPASS (int) ; 
 scalar_t__ STAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 struct task* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct proc* curproc ; 
 int /*<<< orphan*/  free_unr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kproc_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int mtx_sleep (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  soaio_idle ; 
 int /*<<< orphan*/  soaio_jobs ; 
 int /*<<< orphan*/  soaio_jobs_lock ; 
 int /*<<< orphan*/  soaio_kproc_unr ; 
 int /*<<< orphan*/  soaio_lifetime ; 
 scalar_t__ soaio_num_procs ; 
 scalar_t__ soaio_queued ; 
 scalar_t__ soaio_starting ; 
 scalar_t__ soaio_target_procs ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ta_link ; 
 struct vmspace* vmspace_acquire_ref (struct proc*) ; 
 int /*<<< orphan*/  vmspace_switch_aio (struct vmspace*) ; 

__attribute__((used)) static void
soaio_kproc_loop(void *arg)
{
	struct proc *p;
	struct vmspace *myvm;
	struct task *task;
	int error, id, pending;

	id = (intptr_t)arg;

	/*
	 * Grab an extra reference on the daemon's vmspace so that it
	 * doesn't get freed by jobs that switch to a different
	 * vmspace.
	 */
	p = curproc;
	myvm = vmspace_acquire_ref(p);

	mtx_lock(&soaio_jobs_lock);
	MPASS(soaio_starting > 0);
	soaio_starting--;
	for (;;) {
		while (!STAILQ_EMPTY(&soaio_jobs)) {
			task = STAILQ_FIRST(&soaio_jobs);
			STAILQ_REMOVE_HEAD(&soaio_jobs, ta_link);
			soaio_queued--;
			pending = task->ta_pending;
			task->ta_pending = 0;
			mtx_unlock(&soaio_jobs_lock);

			task->ta_func(task->ta_context, pending);

			mtx_lock(&soaio_jobs_lock);
		}
		MPASS(soaio_queued == 0);

		if (p->p_vmspace != myvm) {
			mtx_unlock(&soaio_jobs_lock);
			vmspace_switch_aio(myvm);
			mtx_lock(&soaio_jobs_lock);
			continue;
		}

		soaio_idle++;
		error = mtx_sleep(&soaio_idle, &soaio_jobs_lock, 0, "-",
		    soaio_lifetime);
		soaio_idle--;
		if (error == EWOULDBLOCK && STAILQ_EMPTY(&soaio_jobs) &&
		    soaio_num_procs > soaio_target_procs)
			break;
	}
	soaio_num_procs--;
	mtx_unlock(&soaio_jobs_lock);
	free_unr(soaio_kproc_unr, id);
	kproc_exit(0);
}