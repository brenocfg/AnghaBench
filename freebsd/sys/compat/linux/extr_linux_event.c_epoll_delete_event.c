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
struct kevent_copyops {int /*<<< orphan*/  member_2; int /*<<< orphan*/ * member_1; struct epoll_copyin_args* member_0; } ;
struct kevent {int dummy; } ;
struct file {int dummy; } ;
struct epoll_copyin_args {struct kevent* changelist; } ;

/* Variables and functions */
 int EV_DELETE ; 
 int EV_DISABLE ; 
 int /*<<< orphan*/  EV_SET (struct kevent*,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  epoll_kev_copyin ; 
 int kern_kevent_fp (struct thread*,struct file*,int,int /*<<< orphan*/ ,struct kevent_copyops*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
epoll_delete_event(struct thread *td, struct file *epfp, int fd, int filter)
{
	struct epoll_copyin_args ciargs;
	struct kevent kev;
	struct kevent_copyops k_ops = { &ciargs,
					NULL,
					epoll_kev_copyin};

	ciargs.changelist = &kev;
	EV_SET(&kev, fd, filter, EV_DELETE | EV_DISABLE, 0, 0, 0);

	return (kern_kevent_fp(td, epfp, 1, 0, &k_ops, NULL));
}