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
struct thread {int dummy; } ;
struct kevent_copyops {int kevent_size; int /*<<< orphan*/  k_copyin; int /*<<< orphan*/  k_copyout; struct kevent_args* arg; } ;
struct kevent_args {int /*<<< orphan*/  timeout; int /*<<< orphan*/  nevents; int /*<<< orphan*/  eventlist; int /*<<< orphan*/  nchanges; int /*<<< orphan*/  changelist; int /*<<< orphan*/  fd; } ;
struct kevent {int dummy; } ;
struct g_kevent_args {int /*<<< orphan*/  timeout; int /*<<< orphan*/  nevents; int /*<<< orphan*/  eventlist; int /*<<< orphan*/  nchanges; int /*<<< orphan*/  changelist; int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int kern_kevent_generic (struct thread*,struct g_kevent_args*,struct kevent_copyops*,char*) ; 
 int /*<<< orphan*/  kevent_copyin ; 
 int /*<<< orphan*/  kevent_copyout ; 

int
sys_kevent(struct thread *td, struct kevent_args *uap)
{
	struct kevent_copyops k_ops = {
		.arg = uap,
		.k_copyout = kevent_copyout,
		.k_copyin = kevent_copyin,
		.kevent_size = sizeof(struct kevent),
	};
	struct g_kevent_args gk_args = {
		.fd = uap->fd,
		.changelist = uap->changelist,
		.nchanges = uap->nchanges,
		.eventlist = uap->eventlist,
		.nevents = uap->nevents,
		.timeout = uap->timeout,
	};

	return (kern_kevent_generic(td, &gk_args, &k_ops, "kevent"));
}