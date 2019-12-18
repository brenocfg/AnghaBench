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
struct thread {int dummy; } ;
struct kqueue {TYPE_1__* kq_cred; struct filedesc* kq_fdp; } ;
struct filedesc {int /*<<< orphan*/  fd_kqlist; } ;
struct file {struct kqueue* f_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  cr_ruidinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  FILEDESC_LOCK (struct filedesc*) ; 
 int /*<<< orphan*/  FILEDESC_XLOCK (struct filedesc*) ; 
 int /*<<< orphan*/  FILEDESC_XUNLOCK (struct filedesc*) ; 
 int /*<<< orphan*/  M_KQUEUE ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct kqueue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chgkqcnt (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crfree (TYPE_1__*) ; 
 int /*<<< orphan*/  free (struct kqueue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kq_list ; 
 int kqueue_acquire (struct file*,struct kqueue**) ; 
 int /*<<< orphan*/  kqueue_destroy (struct kqueue*) ; 
 int /*<<< orphan*/  kqueue_drain (struct kqueue*,struct thread*) ; 
 int /*<<< orphan*/  sx_xlocked (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
kqueue_close(struct file *fp, struct thread *td)
{
	struct kqueue *kq = fp->f_data;
	struct filedesc *fdp;
	int error;
	int filedesc_unlock;

	if ((error = kqueue_acquire(fp, &kq)))
		return error;
	kqueue_drain(kq, td);

	/*
	 * We could be called due to the knote_drop() doing fdrop(),
	 * called from kqueue_register().  In this case the global
	 * lock is owned, and filedesc sx is locked before, to not
	 * take the sleepable lock after non-sleepable.
	 */
	fdp = kq->kq_fdp;
	kq->kq_fdp = NULL;
	if (!sx_xlocked(FILEDESC_LOCK(fdp))) {
		FILEDESC_XLOCK(fdp);
		filedesc_unlock = 1;
	} else
		filedesc_unlock = 0;
	TAILQ_REMOVE(&fdp->fd_kqlist, kq, kq_list);
	if (filedesc_unlock)
		FILEDESC_XUNLOCK(fdp);

	kqueue_destroy(kq);
	chgkqcnt(kq->kq_cred->cr_ruidinfo, -1, 0);
	crfree(kq->kq_cred);
	free(kq, M_KQUEUE);
	fp->f_data = NULL;

	return (0);
}