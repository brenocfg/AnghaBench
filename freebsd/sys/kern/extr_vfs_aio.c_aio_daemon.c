#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vmspace {int vm_refcnt; } ;
struct thread {struct proc* td_proc; } ;
struct proc {struct vmspace* p_vmspace; int /*<<< orphan*/ * p_textvp; } ;
struct kaioinfo {int /*<<< orphan*/  kaio_active_count; } ;
struct kaiocb {int /*<<< orphan*/  (* handle_fn ) (struct kaiocb*) ;TYPE_1__* userproc; } ;
struct aioproc {int aioprocflags; struct proc* aioproc; } ;
struct TYPE_2__ {struct kaioinfo* p_aioinfo; } ;

/* Variables and functions */
 int AIOP_FREE ; 
 scalar_t__ EWOULDBLOCK ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  PRIBIO ; 
 scalar_t__ TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (int /*<<< orphan*/ *,struct aioproc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct aioproc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aio_freeproc ; 
 int /*<<< orphan*/  aio_job_mtx ; 
 int /*<<< orphan*/  aio_jobs ; 
 int /*<<< orphan*/  aio_newproc_sem ; 
 struct kaiocb* aio_selectjob (struct aioproc*) ; 
 int /*<<< orphan*/  aiod_lifetime ; 
 int /*<<< orphan*/  aiod_unr ; 
 int /*<<< orphan*/  aiop_zone ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  free_unr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kproc_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list ; 
 scalar_t__ msleep (struct proc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ num_aio_procs ; 
 int /*<<< orphan*/  sema_post (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct kaiocb*) ; 
 scalar_t__ target_aio_procs ; 
 struct aioproc* uma_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,struct aioproc*) ; 
 struct vmspace* vmspace_acquire_ref (struct proc*) ; 
 int /*<<< orphan*/  vmspace_free (struct vmspace*) ; 
 int /*<<< orphan*/  vmspace_switch_aio (struct vmspace*) ; 

__attribute__((used)) static void
aio_daemon(void *_id)
{
	struct kaiocb *job;
	struct aioproc *aiop;
	struct kaioinfo *ki;
	struct proc *p;
	struct vmspace *myvm;
	struct thread *td = curthread;
	int id = (intptr_t)_id;

	/*
	 * Grab an extra reference on the daemon's vmspace so that it
	 * doesn't get freed by jobs that switch to a different
	 * vmspace.
	 */
	p = td->td_proc;
	myvm = vmspace_acquire_ref(p);

	KASSERT(p->p_textvp == NULL, ("kthread has a textvp"));

	/*
	 * Allocate and ready the aio control info.  There is one aiop structure
	 * per daemon.
	 */
	aiop = uma_zalloc(aiop_zone, M_WAITOK);
	aiop->aioproc = p;
	aiop->aioprocflags = 0;

	/*
	 * Wakeup parent process.  (Parent sleeps to keep from blasting away
	 * and creating too many daemons.)
	 */
	sema_post(&aio_newproc_sem);

	mtx_lock(&aio_job_mtx);
	for (;;) {
		/*
		 * Take daemon off of free queue
		 */
		if (aiop->aioprocflags & AIOP_FREE) {
			TAILQ_REMOVE(&aio_freeproc, aiop, list);
			aiop->aioprocflags &= ~AIOP_FREE;
		}

		/*
		 * Check for jobs.
		 */
		while ((job = aio_selectjob(aiop)) != NULL) {
			mtx_unlock(&aio_job_mtx);

			ki = job->userproc->p_aioinfo;
			job->handle_fn(job);

			mtx_lock(&aio_job_mtx);
			/* Decrement the active job count. */
			ki->kaio_active_count--;
		}

		/*
		 * Disconnect from user address space.
		 */
		if (p->p_vmspace != myvm) {
			mtx_unlock(&aio_job_mtx);
			vmspace_switch_aio(myvm);
			mtx_lock(&aio_job_mtx);
			/*
			 * We have to restart to avoid race, we only sleep if
			 * no job can be selected.
			 */
			continue;
		}

		mtx_assert(&aio_job_mtx, MA_OWNED);

		TAILQ_INSERT_HEAD(&aio_freeproc, aiop, list);
		aiop->aioprocflags |= AIOP_FREE;

		/*
		 * If daemon is inactive for a long time, allow it to exit,
		 * thereby freeing resources.
		 */
		if (msleep(p, &aio_job_mtx, PRIBIO, "aiordy",
		    aiod_lifetime) == EWOULDBLOCK && TAILQ_EMPTY(&aio_jobs) &&
		    (aiop->aioprocflags & AIOP_FREE) &&
		    num_aio_procs > target_aio_procs)
			break;
	}
	TAILQ_REMOVE(&aio_freeproc, aiop, list);
	num_aio_procs--;
	mtx_unlock(&aio_job_mtx);
	uma_zfree(aiop_zone, aiop);
	free_unr(aiod_unr, id);
	vmspace_free(myvm);

	KASSERT(p->p_vmspace == myvm,
	    ("AIOD: bad vmspace for exiting daemon"));
	KASSERT(myvm->vm_refcnt > 1,
	    ("AIOD: bad vm refcnt for exiting daemon: %d", myvm->vm_refcnt));
	kproc_exit(0);
}