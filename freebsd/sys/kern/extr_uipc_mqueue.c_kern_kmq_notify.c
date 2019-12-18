#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct thread {struct proc* td_proc; } ;
struct sigevent {scalar_t__ sigev_notify; int /*<<< orphan*/  sigev_signo; } ;
struct proc {struct filedesc* p_fd; } ;
struct TYPE_3__ {int ksi_flags; int ksi_mqd; int /*<<< orphan*/  ksi_code; } ;
struct mqueue_notifier {struct sigevent nt_sigev; TYPE_1__ nt_ksi; struct proc* nt_proc; } ;
struct mqueue {scalar_t__ mq_receivers; int /*<<< orphan*/  mq_mutex; int /*<<< orphan*/  mq_msgq; struct mqueue_notifier* mq_notifier; } ;
struct filedesc {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_ARG_FD (int) ; 
 int EBADF ; 
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  FILEDESC_SLOCK (struct filedesc*) ; 
 int /*<<< orphan*/  FILEDESC_SUNLOCK (struct filedesc*) ; 
 int KSI_EXT ; 
 int KSI_INS ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 scalar_t__ SIGEV_NONE ; 
 scalar_t__ SIGEV_SIGNAL ; 
 scalar_t__ SIGEV_THREAD_ID ; 
 int /*<<< orphan*/  SI_MESGQ ; 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _SIG_VALID (int /*<<< orphan*/ ) ; 
 int cap_check (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cap_event_rights ; 
 int /*<<< orphan*/  cap_rights (struct filedesc*,int) ; 
 int /*<<< orphan*/  fdrop (struct file*,struct thread*) ; 
 struct file* fget_locked (struct filedesc*,int) ; 
 int getmq (struct thread*,int,struct file**,int /*<<< orphan*/ *,struct mqueue**) ; 
 int /*<<< orphan*/  ksiginfo_init (TYPE_1__*) ; 
 int /*<<< orphan*/  mqueue_send_notification (struct mqueue*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 struct mqueue_notifier* notifier_alloc () ; 
 int /*<<< orphan*/  notifier_free (struct mqueue_notifier*) ; 
 int /*<<< orphan*/  notifier_insert (struct proc*,struct mqueue_notifier*) ; 
 int /*<<< orphan*/  notifier_remove (struct proc*,struct mqueue*,int) ; 
 struct mqueue_notifier* notifier_search (struct proc*,int) ; 
 int /*<<< orphan*/  sigqueue_take (TYPE_1__*) ; 

__attribute__((used)) static int
kern_kmq_notify(struct thread *td, int mqd, struct sigevent *sigev)
{
	struct filedesc *fdp;
	struct proc *p;
	struct mqueue *mq;
	struct file *fp, *fp2;
	struct mqueue_notifier *nt, *newnt = NULL;
	int error;

	AUDIT_ARG_FD(mqd);
	if (sigev != NULL) {
		if (sigev->sigev_notify != SIGEV_SIGNAL &&
		    sigev->sigev_notify != SIGEV_THREAD_ID &&
		    sigev->sigev_notify != SIGEV_NONE)
			return (EINVAL);
		if ((sigev->sigev_notify == SIGEV_SIGNAL ||
		    sigev->sigev_notify == SIGEV_THREAD_ID) &&
		    !_SIG_VALID(sigev->sigev_signo))
			return (EINVAL);
	}
	p = td->td_proc;
	fdp = td->td_proc->p_fd;
	error = getmq(td, mqd, &fp, NULL, &mq);
	if (error)
		return (error);
again:
	FILEDESC_SLOCK(fdp);
	fp2 = fget_locked(fdp, mqd);
	if (fp2 == NULL) {
		FILEDESC_SUNLOCK(fdp);
		error = EBADF;
		goto out;
	}
#ifdef CAPABILITIES
	error = cap_check(cap_rights(fdp, mqd), &cap_event_rights);
	if (error) {
		FILEDESC_SUNLOCK(fdp);
		goto out;
	}
#endif
	if (fp2 != fp) {
		FILEDESC_SUNLOCK(fdp);
		error = EBADF;
		goto out;
	}
	mtx_lock(&mq->mq_mutex);
	FILEDESC_SUNLOCK(fdp);
	if (sigev != NULL) {
		if (mq->mq_notifier != NULL) {
			error = EBUSY;
		} else {
			PROC_LOCK(p);
			nt = notifier_search(p, mqd);
			if (nt == NULL) {
				if (newnt == NULL) {
					PROC_UNLOCK(p);
					mtx_unlock(&mq->mq_mutex);
					newnt = notifier_alloc();
					goto again;
				}
			}

			if (nt != NULL) {
				sigqueue_take(&nt->nt_ksi);
				if (newnt != NULL) {
					notifier_free(newnt);
					newnt = NULL;
				}
			} else {
				nt = newnt;
				newnt = NULL;
				ksiginfo_init(&nt->nt_ksi);
				nt->nt_ksi.ksi_flags |= KSI_INS | KSI_EXT;
				nt->nt_ksi.ksi_code = SI_MESGQ;
				nt->nt_proc = p;
				nt->nt_ksi.ksi_mqd = mqd;
				notifier_insert(p, nt);
			}
			nt->nt_sigev = *sigev;
			mq->mq_notifier = nt;
			PROC_UNLOCK(p);
			/*
			 * if there is no receivers and message queue
			 * is not empty, we should send notification
			 * as soon as possible.
			 */
			if (mq->mq_receivers == 0 &&
			    !TAILQ_EMPTY(&mq->mq_msgq))
				mqueue_send_notification(mq);
		}
	} else {
		notifier_remove(p, mq, mqd);
	}
	mtx_unlock(&mq->mq_mutex);

out:
	fdrop(fp, td);
	if (newnt != NULL)
		notifier_free(newnt);
	return (error);
}