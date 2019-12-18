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
struct thread {int dummy; } ;
struct freebsd32_utimensat_args {int /*<<< orphan*/  flag; int /*<<< orphan*/  path; int /*<<< orphan*/  fd; int /*<<< orphan*/ * times; } ;

/* Variables and functions */
 int /*<<< orphan*/  CP (struct timespec32,struct timespec,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int /*<<< orphan*/  UIO_USERSPACE ; 
 int copyin (int /*<<< orphan*/ *,struct timespec32*,int) ; 
 int kern_utimensat (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct timespec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tv_nsec ; 
 int /*<<< orphan*/  tv_sec ; 

int
freebsd32_utimensat(struct thread *td, struct freebsd32_utimensat_args *uap)
{
	struct timespec32 ts32[2];
	struct timespec ts[2], *tsp;
	int error;

	if (uap->times != NULL) {
		error = copyin(uap->times, ts32, sizeof(ts32));
		if (error)
			return (error);
		CP(ts32[0], ts[0], tv_sec);
		CP(ts32[0], ts[0], tv_nsec);
		CP(ts32[1], ts[1], tv_sec);
		CP(ts32[1], ts[1], tv_nsec);
		tsp = ts;
	} else
		tsp = NULL;
	return (kern_utimensat(td, uap->fd, uap->path, UIO_USERSPACE,
	    tsp, UIO_SYSSPACE, uap->flag));
}