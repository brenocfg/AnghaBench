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
struct timespec {int dummy; } ;
struct thread {int* td_retval; } ;
struct kqueue {int dummy; } ;
struct kevent_copyops {int (* k_copyin ) (int /*<<< orphan*/ ,struct kevent*,int) ;int /*<<< orphan*/  arg; int /*<<< orphan*/  (* k_copyout ) (int /*<<< orphan*/ ,struct kevent*,int) ;} ;
struct kevent {int flags; int data; int /*<<< orphan*/  filter; } ;

/* Variables and functions */
 int EV_ERROR ; 
 int EV_RECEIPT ; 
 int EV_SYSFLAGS ; 
 int KQ_NEVENTS ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int kqueue_register (struct kqueue*,struct kevent*,struct thread*,int /*<<< orphan*/ ) ; 
 int kqueue_scan (struct kqueue*,int,struct kevent_copyops*,struct timespec const*,struct kevent*,struct thread*) ; 
 int stub1 (int /*<<< orphan*/ ,struct kevent*,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,struct kevent*,int) ; 

__attribute__((used)) static int
kqueue_kevent(struct kqueue *kq, struct thread *td, int nchanges, int nevents,
    struct kevent_copyops *k_ops, const struct timespec *timeout)
{
	struct kevent keva[KQ_NEVENTS];
	struct kevent *kevp, *changes;
	int i, n, nerrors, error;

	nerrors = 0;
	while (nchanges > 0) {
		n = nchanges > KQ_NEVENTS ? KQ_NEVENTS : nchanges;
		error = k_ops->k_copyin(k_ops->arg, keva, n);
		if (error)
			return (error);
		changes = keva;
		for (i = 0; i < n; i++) {
			kevp = &changes[i];
			if (!kevp->filter)
				continue;
			kevp->flags &= ~EV_SYSFLAGS;
			error = kqueue_register(kq, kevp, td, M_WAITOK);
			if (error || (kevp->flags & EV_RECEIPT)) {
				if (nevents == 0)
					return (error);
				kevp->flags = EV_ERROR;
				kevp->data = error;
				(void)k_ops->k_copyout(k_ops->arg, kevp, 1);
				nevents--;
				nerrors++;
			}
		}
		nchanges -= n;
	}
	if (nerrors) {
		td->td_retval[0] = nerrors;
		return (0);
	}

	return (kqueue_scan(kq, nevents, k_ops, timeout, keva, td));
}