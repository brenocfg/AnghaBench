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
struct freebsd32_fcntl_args {int cmd; long arg; int /*<<< orphan*/  fd; } ;

/* Variables and functions */
#define  F_GETLK 136 
#define  F_OGETLK 135 
#define  F_OSETLK 134 
#define  F_OSETLKW 133 
#define  F_SETFD 132 
#define  F_SETFL 131 
#define  F_SETLK 130 
#define  F_SETLKW 129 
#define  F_SETLK_REMOTE 128 
 int kern_fcntl_freebsd (struct thread*,int /*<<< orphan*/ ,int,long) ; 

int
freebsd32_fcntl(struct thread *td, struct freebsd32_fcntl_args *uap)
{
	long tmp;

	switch (uap->cmd) {
	/*
	 * Do unsigned conversion for arg when operation
	 * interprets it as flags or pointer.
	 */
	case F_SETLK_REMOTE:
	case F_SETLKW:
	case F_SETLK:
	case F_GETLK:
	case F_SETFD:
	case F_SETFL:
	case F_OGETLK:
	case F_OSETLK:
	case F_OSETLKW:
		tmp = (unsigned int)(uap->arg);
		break;
	default:
		tmp = uap->arg;
		break;
	}
	return (kern_fcntl_freebsd(td, uap->fd, uap->cmd, tmp));
}