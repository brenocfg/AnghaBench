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
struct timespec {scalar_t__ tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct thread {int dummy; } ;
struct linux_utimensat_args {int dfd; int flags; int /*<<< orphan*/ * pathname; int /*<<< orphan*/ * times; } ;
struct l_timespec {int tv_nsec; int /*<<< orphan*/  tv_sec; } ;
typedef  int /*<<< orphan*/  l_times ;

/* Variables and functions */
 int AT_FDCWD ; 
 int AT_SYMLINK_NOFOLLOW ; 
 int EINVAL ; 
 int /*<<< orphan*/  LCONVPATHEXIST_AT (struct thread*,int /*<<< orphan*/ *,char**,int) ; 
 int /*<<< orphan*/  LFREEPATH (char*) ; 
 int LINUX_AT_FDCWD ; 
 int LINUX_AT_SYMLINK_NOFOLLOW ; 
#define  LINUX_UTIME_NOW 129 
#define  LINUX_UTIME_OMIT 128 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 void* UTIME_NOW ; 
 scalar_t__ UTIME_OMIT ; 
 int copyin (int /*<<< orphan*/ *,struct l_timespec*,int) ; 
 int kern_futimens (struct thread*,int,struct timespec*,int /*<<< orphan*/ ) ; 
 int kern_utimensat (struct thread*,int,char*,int /*<<< orphan*/ ,struct timespec*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ linux_utimensat_nsec_valid (int) ; 

int
linux_utimensat(struct thread *td, struct linux_utimensat_args *args)
{
	struct l_timespec l_times[2];
	struct timespec times[2], *timesp = NULL;
	char *path = NULL;
	int error, dfd, flags = 0;

	dfd = (args->dfd == LINUX_AT_FDCWD) ? AT_FDCWD : args->dfd;

	if (args->flags & ~LINUX_AT_SYMLINK_NOFOLLOW)
		return (EINVAL);

	if (args->times != NULL) {
		error = copyin(args->times, l_times, sizeof(l_times));
		if (error != 0)
			return (error);

		if (linux_utimensat_nsec_valid(l_times[0].tv_nsec) != 0 ||
		    linux_utimensat_nsec_valid(l_times[1].tv_nsec) != 0)
			return (EINVAL);

		times[0].tv_sec = l_times[0].tv_sec;
		switch (l_times[0].tv_nsec)
		{
		case LINUX_UTIME_OMIT:
			times[0].tv_nsec = UTIME_OMIT;
			break;
		case LINUX_UTIME_NOW:
			times[0].tv_nsec = UTIME_NOW;
			break;
		default:
			times[0].tv_nsec = l_times[0].tv_nsec;
		}

		times[1].tv_sec = l_times[1].tv_sec;
		switch (l_times[1].tv_nsec)
		{
		case LINUX_UTIME_OMIT:
			times[1].tv_nsec = UTIME_OMIT;
			break;
		case LINUX_UTIME_NOW:
			times[1].tv_nsec = UTIME_NOW;
			break;
		default:
			times[1].tv_nsec = l_times[1].tv_nsec;
			break;
		}
		timesp = times;

		/* This breaks POSIX, but is what the Linux kernel does
		 * _on purpose_ (documented in the man page for utimensat(2)),
		 * so we must follow that behaviour. */
		if (times[0].tv_nsec == UTIME_OMIT &&
		    times[1].tv_nsec == UTIME_OMIT)
			return (0);
	}

	if (args->pathname != NULL)
		LCONVPATHEXIST_AT(td, args->pathname, &path, dfd);
	else if (args->flags != 0)
		return (EINVAL);

	if (args->flags & LINUX_AT_SYMLINK_NOFOLLOW)
		flags |= AT_SYMLINK_NOFOLLOW;

	if (path == NULL)
		error = kern_futimens(td, dfd, timesp, UIO_SYSSPACE);
	else {
		error = kern_utimensat(td, dfd, path, UIO_SYSSPACE, timesp,
			UIO_SYSSPACE, flags);
		LFREEPATH(path);
	}

	return (error);
}