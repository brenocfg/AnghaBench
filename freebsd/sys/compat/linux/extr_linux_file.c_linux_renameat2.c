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
struct linux_renameat2_args {int flags; int olddfd; int newdfd; int /*<<< orphan*/  newname; int /*<<< orphan*/  oldname; } ;

/* Variables and functions */
 int AT_FDCWD ; 
 int EINVAL ; 
 int /*<<< orphan*/  LCONVPATHEXIST_AT (struct thread*,int /*<<< orphan*/ ,char**,int) ; 
 int /*<<< orphan*/  LFREEPATH (char*) ; 
 int LINUX_AT_FDCWD ; 
 int LINUX_RENAME_EXCHANGE ; 
 int LINUX_RENAME_NOREPLACE ; 
 int LINUX_RENAME_WHITEOUT ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int /*<<< orphan*/  UIO_USERSPACE ; 
 int kern_renameat (struct thread*,int,char*,int,char*,int /*<<< orphan*/ ) ; 
 int linux_emul_convpath (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**,int,int) ; 
 int /*<<< orphan*/  linux_msg (struct thread*,char*,int) ; 

int
linux_renameat2(struct thread *td, struct linux_renameat2_args *args)
{
	char *from, *to;
	int error, olddfd, newdfd;

	if (args->flags != 0) {
		if (args->flags & ~(LINUX_RENAME_EXCHANGE |
		    LINUX_RENAME_NOREPLACE | LINUX_RENAME_WHITEOUT))
			return (EINVAL);
		if (args->flags & LINUX_RENAME_EXCHANGE &&
		    args->flags & (LINUX_RENAME_NOREPLACE |
		    LINUX_RENAME_WHITEOUT))
			return (EINVAL);
		linux_msg(td, "renameat2 unsupported flags 0x%x",
		    args->flags);
		return (EINVAL);
	}

	olddfd = (args->olddfd == LINUX_AT_FDCWD) ? AT_FDCWD : args->olddfd;
	newdfd = (args->newdfd == LINUX_AT_FDCWD) ? AT_FDCWD : args->newdfd;
	LCONVPATHEXIST_AT(td, args->oldname, &from, olddfd);
	/* Expand LCONVPATHCREATE so that `from' can be freed on errors */
	error = linux_emul_convpath(td, args->newname, UIO_USERSPACE, &to, 1, newdfd);
	if (to == NULL) {
		LFREEPATH(from);
		return (error);
	}

	error = kern_renameat(td, olddfd, from, newdfd, to, UIO_SYSSPACE);
	LFREEPATH(from);
	LFREEPATH(to);
	return (error);
}