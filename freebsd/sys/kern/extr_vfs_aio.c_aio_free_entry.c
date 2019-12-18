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
struct proc {struct kaioinfo* p_aioinfo; } ;
struct kaioinfo {scalar_t__ kaio_count; int /*<<< orphan*/  kaio_liojoblist; int /*<<< orphan*/  kaio_all; int /*<<< orphan*/  kaio_done; } ;
struct kaiocb {int jobflags; scalar_t__ lioj_count; int /*<<< orphan*/  cred; scalar_t__ fd_file; int /*<<< orphan*/  ksi; int /*<<< orphan*/  klist; int /*<<< orphan*/  lioj_ksi; int /*<<< orphan*/  lioj_finished_count; struct kaiocb* lio; struct proc* userproc; } ;
struct aioliojob {int jobflags; scalar_t__ lioj_count; int /*<<< orphan*/  cred; scalar_t__ fd_file; int /*<<< orphan*/  ksi; int /*<<< orphan*/  klist; int /*<<< orphan*/  lioj_ksi; int /*<<< orphan*/  lioj_finished_count; struct aioliojob* lio; struct proc* userproc; } ;

/* Variables and functions */
 int /*<<< orphan*/  AIO_LOCK (struct kaioinfo*) ; 
 int /*<<< orphan*/  AIO_LOCK_ASSERT (struct kaioinfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AIO_UNLOCK (struct kaioinfo*) ; 
 int KAIOCB_FINISHED ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct kaiocb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aiocb_zone ; 
 int /*<<< orphan*/  aiolio_zone ; 
 int /*<<< orphan*/  allist ; 
 int /*<<< orphan*/  atomic_subtract_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  crfree (int /*<<< orphan*/ ) ; 
 struct proc* curproc ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  fdrop (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  knlist_delete (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lioj_list ; 
 int /*<<< orphan*/  num_queue_count ; 
 int /*<<< orphan*/  plist ; 
 int /*<<< orphan*/  sigqueue_take (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,struct kaiocb*) ; 

__attribute__((used)) static int
aio_free_entry(struct kaiocb *job)
{
	struct kaioinfo *ki;
	struct aioliojob *lj;
	struct proc *p;

	p = job->userproc;
	MPASS(curproc == p);
	ki = p->p_aioinfo;
	MPASS(ki != NULL);

	AIO_LOCK_ASSERT(ki, MA_OWNED);
	MPASS(job->jobflags & KAIOCB_FINISHED);

	atomic_subtract_int(&num_queue_count, 1);

	ki->kaio_count--;
	MPASS(ki->kaio_count >= 0);

	TAILQ_REMOVE(&ki->kaio_done, job, plist);
	TAILQ_REMOVE(&ki->kaio_all, job, allist);

	lj = job->lio;
	if (lj) {
		lj->lioj_count--;
		lj->lioj_finished_count--;

		if (lj->lioj_count == 0) {
			TAILQ_REMOVE(&ki->kaio_liojoblist, lj, lioj_list);
			/* lio is going away, we need to destroy any knotes */
			knlist_delete(&lj->klist, curthread, 1);
			PROC_LOCK(p);
			sigqueue_take(&lj->lioj_ksi);
			PROC_UNLOCK(p);
			uma_zfree(aiolio_zone, lj);
		}
	}

	/* job is going away, we need to destroy any knotes */
	knlist_delete(&job->klist, curthread, 1);
	PROC_LOCK(p);
	sigqueue_take(&job->ksi);
	PROC_UNLOCK(p);

	AIO_UNLOCK(ki);

	/*
	 * The thread argument here is used to find the owning process
	 * and is also passed to fo_close() which may pass it to various
	 * places such as devsw close() routines.  Because of that, we
	 * need a thread pointer from the process owning the job that is
	 * persistent and won't disappear out from under us or move to
	 * another process.
	 *
	 * Currently, all the callers of this function call it to remove
	 * a kaiocb from the current process' job list either via a
	 * syscall or due to the current process calling exit() or
	 * execve().  Thus, we know that p == curproc.  We also know that
	 * curthread can't exit since we are curthread.
	 *
	 * Therefore, we use curthread as the thread to pass to
	 * knlist_delete().  This does mean that it is possible for the
	 * thread pointer at close time to differ from the thread pointer
	 * at open time, but this is already true of file descriptors in
	 * a multithreaded process.
	 */
	if (job->fd_file)
		fdrop(job->fd_file, curthread);
	crfree(job->cred);
	uma_zfree(aiocb_zone, job);
	AIO_LOCK(ki);

	return (0);
}