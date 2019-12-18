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
typedef  int /*<<< orphan*/  ts32 ;
struct timespec32 {int dummy; } ;
struct timespec {int dummy; } ;
struct thread {int /*<<< orphan*/ * td_retval; } ;
struct kevent_copyops {int /*<<< orphan*/  k_copyin; int /*<<< orphan*/  k_copyout; struct freebsd32_kevent_args* arg; } ;
struct kevent32 {int dummy; } ;
struct freebsd32_kevent_args {int /*<<< orphan*/  nevents; int /*<<< orphan*/  nchanges; int /*<<< orphan*/  fd; struct kevent32* changelist; scalar_t__ timeout; struct kevent32* eventlist; } ;

/* Variables and functions */
 int /*<<< orphan*/  CP (struct timespec32,struct timespec,int /*<<< orphan*/ ) ; 
 scalar_t__ KTRPOINT (struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KTR_STRUCT_ARRAY ; 
 int /*<<< orphan*/  UIO_USERSPACE ; 
 int copyin (scalar_t__,struct timespec32*,int) ; 
 int /*<<< orphan*/  freebsd32_kevent_copyin ; 
 int /*<<< orphan*/  freebsd32_kevent_copyout ; 
 int kern_kevent (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct kevent_copyops*,struct timespec*) ; 
 int /*<<< orphan*/  ktrstructarray (char*,int /*<<< orphan*/ ,struct kevent32*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tv_nsec ; 
 int /*<<< orphan*/  tv_sec ; 

int
freebsd32_kevent(struct thread *td, struct freebsd32_kevent_args *uap)
{
	struct timespec32 ts32;
	struct timespec ts, *tsp;
	struct kevent_copyops k_ops = {
		.arg = uap,
		.k_copyout = freebsd32_kevent_copyout,
		.k_copyin = freebsd32_kevent_copyin,
	};
#ifdef KTRACE
	struct kevent32 *eventlist = uap->eventlist;
#endif
	int error;

	if (uap->timeout) {
		error = copyin(uap->timeout, &ts32, sizeof(ts32));
		if (error)
			return (error);
		CP(ts32, ts, tv_sec);
		CP(ts32, ts, tv_nsec);
		tsp = &ts;
	} else
		tsp = NULL;
#ifdef KTRACE
	if (KTRPOINT(td, KTR_STRUCT_ARRAY))
		ktrstructarray("kevent32", UIO_USERSPACE, uap->changelist,
		    uap->nchanges, sizeof(struct kevent32));
#endif
	error = kern_kevent(td, uap->fd, uap->nchanges, uap->nevents,
	    &k_ops, tsp);
#ifdef KTRACE
	if (error == 0 && KTRPOINT(td, KTR_STRUCT_ARRAY))
		ktrstructarray("kevent32", UIO_USERSPACE, eventlist,
		    td->td_retval[0], sizeof(struct kevent32));
#endif
	return (error);
}