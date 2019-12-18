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
struct ucred {int /*<<< orphan*/  cr_ruidinfo; } ;
struct thread {int* td_retval; struct ucred* td_ucred; TYPE_1__* td_proc; } ;
struct kqueue {int /*<<< orphan*/  kq_cred; struct filedesc* kq_fdp; } ;
struct filedesc {int /*<<< orphan*/  fd_kqlist; } ;
struct filecaps {int dummy; } ;
struct file {int dummy; } ;
struct TYPE_2__ {struct filedesc* p_fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  DTYPE_KQUEUE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FILEDESC_XLOCK (struct filedesc*) ; 
 int /*<<< orphan*/  FILEDESC_XUNLOCK (struct filedesc*) ; 
 int FREAD ; 
 int FWRITE ; 
 int /*<<< orphan*/  M_KQUEUE ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  RLIMIT_KQUEUES ; 
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (int /*<<< orphan*/ *,struct kqueue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chgkqcnt (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crhold (struct ucred*) ; 
 int falloc_caps (struct thread*,struct file**,int*,int,struct filecaps*) ; 
 int /*<<< orphan*/  fdrop (struct file*,struct thread*) ; 
 int /*<<< orphan*/  finit (struct file*,int,int /*<<< orphan*/ ,struct kqueue*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kq_list ; 
 int /*<<< orphan*/  kqueue_init (struct kqueue*) ; 
 int /*<<< orphan*/  kqueueops ; 
 int /*<<< orphan*/  lim_cur (struct thread*,int /*<<< orphan*/ ) ; 
 struct kqueue* malloc (int,int /*<<< orphan*/ ,int) ; 

int
kern_kqueue(struct thread *td, int flags, struct filecaps *fcaps)
{
	struct filedesc *fdp;
	struct kqueue *kq;
	struct file *fp;
	struct ucred *cred;
	int fd, error;

	fdp = td->td_proc->p_fd;
	cred = td->td_ucred;
	if (!chgkqcnt(cred->cr_ruidinfo, 1, lim_cur(td, RLIMIT_KQUEUES)))
		return (ENOMEM);

	error = falloc_caps(td, &fp, &fd, flags, fcaps);
	if (error != 0) {
		chgkqcnt(cred->cr_ruidinfo, -1, 0);
		return (error);
	}

	/* An extra reference on `fp' has been held for us by falloc(). */
	kq = malloc(sizeof *kq, M_KQUEUE, M_WAITOK | M_ZERO);
	kqueue_init(kq);
	kq->kq_fdp = fdp;
	kq->kq_cred = crhold(cred);

	FILEDESC_XLOCK(fdp);
	TAILQ_INSERT_HEAD(&fdp->fd_kqlist, kq, kq_list);
	FILEDESC_XUNLOCK(fdp);

	finit(fp, FREAD | FWRITE, DTYPE_KQUEUE, kq, &kqueueops);
	fdrop(fp, td);

	td->td_retval[0] = fd;
	return (0);
}