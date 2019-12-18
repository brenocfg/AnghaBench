#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct thread {struct proc* td_proc; } ;
struct sigevent {int dummy; } ;
struct proc {struct kaioinfo* p_aioinfo; } ;
struct kevent {int flags; uintptr_t ident; intptr_t data; int /*<<< orphan*/  udata; int /*<<< orphan*/  filter; } ;
struct kaioinfo {int /*<<< orphan*/  kaio_liojoblist; int /*<<< orphan*/  kaio_flags; } ;
struct TYPE_4__ {int /*<<< orphan*/  sival_ptr; } ;
struct TYPE_5__ {scalar_t__ sigev_notify; int /*<<< orphan*/  sigev_signo; int /*<<< orphan*/  sigev_notify_kqueue; TYPE_1__ sigev_value; } ;
struct aioliojob {int lioj_flags; int lioj_count; int lioj_finished_count; int /*<<< orphan*/  lioj_ksi; int /*<<< orphan*/  klist; TYPE_2__ lioj_signal; } ;
struct aiocb_ops {int dummy; } ;
struct aiocb {int dummy; } ;
typedef  int /*<<< orphan*/  kev ;

/* Variables and functions */
 int /*<<< orphan*/  AIO_LOCK (struct kaioinfo*) ; 
 int /*<<< orphan*/  AIO_MTX (struct kaioinfo*) ; 
 int /*<<< orphan*/  AIO_UNLOCK (struct kaioinfo*) ; 
 int EAGAIN ; 
 int EINTR ; 
 int EINVAL ; 
 int EIO ; 
 int ERESTART ; 
 int /*<<< orphan*/  EVFILT_LIO ; 
 int EV_ADD ; 
 int EV_ENABLE ; 
 int EV_FLAG1 ; 
 int /*<<< orphan*/  KAIO_WAKEUP ; 
 int /*<<< orphan*/  KNOTE_LOCKED (int /*<<< orphan*/ *,int) ; 
 int LIOJ_KEVENT_POSTED ; 
 int LIOJ_SIGNAL ; 
 int LIOJ_SIGNAL_POSTED ; 
 int /*<<< orphan*/  LIO_NOP ; 
 int LIO_NOWAIT ; 
 int LIO_WAIT ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int PCATCH ; 
 int PRIBIO ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 scalar_t__ SIGEV_KEVENT ; 
 scalar_t__ SIGEV_NONE ; 
 scalar_t__ SIGEV_SIGNAL ; 
 scalar_t__ SIGEV_THREAD_ID ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct aioliojob*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct aioliojob*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _SIG_VALID (int /*<<< orphan*/ ) ; 
 int aio_aqueue (struct thread*,struct aiocb*,struct aioliojob*,int /*<<< orphan*/ ,struct aiocb_ops*) ; 
 int /*<<< orphan*/  aio_init_aioinfo (struct proc*) ; 
 int /*<<< orphan*/  aio_sendsig (struct proc*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aiolio_zone ; 
 int /*<<< orphan*/  bcopy (struct sigevent*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  knlist_delete (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  knlist_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int kqfd_register (int /*<<< orphan*/ ,struct kevent*,struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ksiginfo_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lioj_list ; 
 int max_aio_queue_per_proc ; 
 int /*<<< orphan*/  memset (struct kevent*,int /*<<< orphan*/ ,int) ; 
 int msleep (struct kaioinfo**,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigqueue_take (int /*<<< orphan*/ *) ; 
 struct aioliojob* uma_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,struct aioliojob*) ; 

__attribute__((used)) static int
kern_lio_listio(struct thread *td, int mode, struct aiocb * const *uacb_list,
    struct aiocb **acb_list, int nent, struct sigevent *sig,
    struct aiocb_ops *ops)
{
	struct proc *p = td->td_proc;
	struct aiocb *job;
	struct kaioinfo *ki;
	struct aioliojob *lj;
	struct kevent kev;
	int error;
	int nagain, nerror;
	int i;

	if ((mode != LIO_NOWAIT) && (mode != LIO_WAIT))
		return (EINVAL);

	if (nent < 0 || nent > max_aio_queue_per_proc)
		return (EINVAL);

	if (p->p_aioinfo == NULL)
		aio_init_aioinfo(p);

	ki = p->p_aioinfo;

	lj = uma_zalloc(aiolio_zone, M_WAITOK);
	lj->lioj_flags = 0;
	lj->lioj_count = 0;
	lj->lioj_finished_count = 0;
	knlist_init_mtx(&lj->klist, AIO_MTX(ki));
	ksiginfo_init(&lj->lioj_ksi);

	/*
	 * Setup signal.
	 */
	if (sig && (mode == LIO_NOWAIT)) {
		bcopy(sig, &lj->lioj_signal, sizeof(lj->lioj_signal));
		if (lj->lioj_signal.sigev_notify == SIGEV_KEVENT) {
			/* Assume only new style KEVENT */
			memset(&kev, 0, sizeof(kev));
			kev.filter = EVFILT_LIO;
			kev.flags = EV_ADD | EV_ENABLE | EV_FLAG1;
			kev.ident = (uintptr_t)uacb_list; /* something unique */
			kev.data = (intptr_t)lj;
			/* pass user defined sigval data */
			kev.udata = lj->lioj_signal.sigev_value.sival_ptr;
			error = kqfd_register(
			    lj->lioj_signal.sigev_notify_kqueue, &kev, td,
			    M_WAITOK);
			if (error) {
				uma_zfree(aiolio_zone, lj);
				return (error);
			}
		} else if (lj->lioj_signal.sigev_notify == SIGEV_NONE) {
			;
		} else if (lj->lioj_signal.sigev_notify == SIGEV_SIGNAL ||
			   lj->lioj_signal.sigev_notify == SIGEV_THREAD_ID) {
				if (!_SIG_VALID(lj->lioj_signal.sigev_signo)) {
					uma_zfree(aiolio_zone, lj);
					return EINVAL;
				}
				lj->lioj_flags |= LIOJ_SIGNAL;
		} else {
			uma_zfree(aiolio_zone, lj);
			return EINVAL;
		}
	}

	AIO_LOCK(ki);
	TAILQ_INSERT_TAIL(&ki->kaio_liojoblist, lj, lioj_list);
	/*
	 * Add extra aiocb count to avoid the lio to be freed
	 * by other threads doing aio_waitcomplete or aio_return,
	 * and prevent event from being sent until we have queued
	 * all tasks.
	 */
	lj->lioj_count = 1;
	AIO_UNLOCK(ki);

	/*
	 * Get pointers to the list of I/O requests.
	 */
	nagain = 0;
	nerror = 0;
	for (i = 0; i < nent; i++) {
		job = acb_list[i];
		if (job != NULL) {
			error = aio_aqueue(td, job, lj, LIO_NOP, ops);
			if (error == EAGAIN)
				nagain++;
			else if (error != 0)
				nerror++;
		}
	}

	error = 0;
	AIO_LOCK(ki);
	if (mode == LIO_WAIT) {
		while (lj->lioj_count - 1 != lj->lioj_finished_count) {
			ki->kaio_flags |= KAIO_WAKEUP;
			error = msleep(&p->p_aioinfo, AIO_MTX(ki),
			    PRIBIO | PCATCH, "aiospn", 0);
			if (error == ERESTART)
				error = EINTR;
			if (error)
				break;
		}
	} else {
		if (lj->lioj_count - 1 == lj->lioj_finished_count) {
			if (lj->lioj_signal.sigev_notify == SIGEV_KEVENT) {
				lj->lioj_flags |= LIOJ_KEVENT_POSTED;
				KNOTE_LOCKED(&lj->klist, 1);
			}
			if ((lj->lioj_flags & (LIOJ_SIGNAL|LIOJ_SIGNAL_POSTED))
			    == LIOJ_SIGNAL
			    && (lj->lioj_signal.sigev_notify == SIGEV_SIGNAL ||
			    lj->lioj_signal.sigev_notify == SIGEV_THREAD_ID)) {
				aio_sendsig(p, &lj->lioj_signal,
					    &lj->lioj_ksi);
				lj->lioj_flags |= LIOJ_SIGNAL_POSTED;
			}
		}
	}
	lj->lioj_count--;
	if (lj->lioj_count == 0) {
		TAILQ_REMOVE(&ki->kaio_liojoblist, lj, lioj_list);
		knlist_delete(&lj->klist, curthread, 1);
		PROC_LOCK(p);
		sigqueue_take(&lj->lioj_ksi);
		PROC_UNLOCK(p);
		AIO_UNLOCK(ki);
		uma_zfree(aiolio_zone, lj);
	} else
		AIO_UNLOCK(ki);

	if (nerror)
		return (EIO);
	else if (nagain)
		return (EAGAIN);
	else
		return (error);
}