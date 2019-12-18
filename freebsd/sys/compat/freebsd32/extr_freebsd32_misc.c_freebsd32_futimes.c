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
struct timeval32 {int dummy; } ;
struct timeval {int dummy; } ;
struct thread {int dummy; } ;
struct freebsd32_futimes_args {int /*<<< orphan*/  fd; int /*<<< orphan*/ * tptr; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  CP (struct timeval32,struct timeval,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int copyin (int /*<<< orphan*/ *,struct timeval32*,int) ; 
 int kern_futimes (struct thread*,int /*<<< orphan*/ ,struct timeval*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tv_sec ; 
 int /*<<< orphan*/  tv_usec ; 

int
freebsd32_futimes(struct thread *td, struct freebsd32_futimes_args *uap)
{
	struct timeval32 s32[2];
	struct timeval s[2], *sp;
	int error;

	if (uap->tptr != NULL) {
		error = copyin(uap->tptr, s32, sizeof(s32));
		if (error)
			return (error);
		CP(s32[0], s[0], tv_sec);
		CP(s32[0], s[0], tv_usec);
		CP(s32[1], s[1], tv_sec);
		CP(s32[1], s[1], tv_usec);
		sp = s;
	} else
		sp = NULL;
	return (kern_futimes(td, uap->fd, sp, UIO_SYSSPACE));
}