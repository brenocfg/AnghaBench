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
struct kqop {int dummy; } ;
struct kevent {int ident; void* flags; int /*<<< orphan*/  filter; } ;
struct event {int ev_flags; int ev_events; int ev_fd; } ;
typedef  int /*<<< orphan*/  kev ;

/* Variables and functions */
 int EVENT_SIGNAL (struct event*) ; 
 int /*<<< orphan*/  EVFILT_READ ; 
 int /*<<< orphan*/  EVFILT_SIGNAL ; 
 int /*<<< orphan*/  EVFILT_WRITE ; 
 int EVLIST_X_KQINKERNEL ; 
 void* EV_DELETE ; 
 int EV_READ ; 
 int EV_SIGNAL ; 
 int EV_WRITE ; 
 int /*<<< orphan*/  SIG_DFL ; 
 scalar_t__ SIG_ERR ; 
 int kq_insert (struct kqop*,struct kevent*) ; 
 int /*<<< orphan*/  memset (struct kevent*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ signal (int,int /*<<< orphan*/ ) ; 

int
kq_del(void *arg, struct event *ev)
{
	struct kqop *kqop = arg;
	struct kevent kev;

	if (!(ev->ev_flags & EVLIST_X_KQINKERNEL))
		return (0);

	if (ev->ev_events & EV_SIGNAL) {
		int nsignal = EVENT_SIGNAL(ev);

 		memset(&kev, 0, sizeof(kev));
		kev.ident = nsignal;
		kev.filter = EVFILT_SIGNAL;
		kev.flags = EV_DELETE;
		
		if (kq_insert(kqop, &kev) == -1)
			return (-1);

		if (signal(nsignal, SIG_DFL) == SIG_ERR)
			return (-1);

		ev->ev_flags &= ~EVLIST_X_KQINKERNEL;
		return (0);
	}

	if (ev->ev_events & EV_READ) {
 		memset(&kev, 0, sizeof(kev));
		kev.ident = ev->ev_fd;
		kev.filter = EVFILT_READ;
		kev.flags = EV_DELETE;
		
		if (kq_insert(kqop, &kev) == -1)
			return (-1);

		ev->ev_flags &= ~EVLIST_X_KQINKERNEL;
	}

	if (ev->ev_events & EV_WRITE) {
 		memset(&kev, 0, sizeof(kev));
		kev.ident = ev->ev_fd;
		kev.filter = EVFILT_WRITE;
		kev.flags = EV_DELETE;
		
		if (kq_insert(kqop, &kev) == -1)
			return (-1);

		ev->ev_flags &= ~EVLIST_X_KQINKERNEL;
	}

	return (0);
}