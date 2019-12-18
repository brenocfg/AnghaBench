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
struct linux_linkat_args {int flag; int olddfd; int newdfd; int /*<<< orphan*/  newname; int /*<<< orphan*/  oldname; } ;

/* Variables and functions */
 int AT_FDCWD ; 
 int EINVAL ; 
 int FOLLOW ; 
 int /*<<< orphan*/  LCONVPATHEXIST_AT (struct thread*,int /*<<< orphan*/ ,char**,int) ; 
 int /*<<< orphan*/  LFREEPATH (char*) ; 
 int LINUX_AT_FDCWD ; 
 int LINUX_AT_SYMLINK_FOLLOW ; 
 int NOFOLLOW ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int /*<<< orphan*/  UIO_USERSPACE ; 
 int kern_linkat (struct thread*,int,int,char*,char*,int /*<<< orphan*/ ,int) ; 
 int linux_emul_convpath (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**,int,int) ; 

int
linux_linkat(struct thread *td, struct linux_linkat_args *args)
{
	char *path, *to;
	int error, olddfd, newdfd, follow;

	if (args->flag & ~LINUX_AT_SYMLINK_FOLLOW)
		return (EINVAL);

	olddfd = (args->olddfd == LINUX_AT_FDCWD) ? AT_FDCWD : args->olddfd;
	newdfd = (args->newdfd == LINUX_AT_FDCWD) ? AT_FDCWD : args->newdfd;
	LCONVPATHEXIST_AT(td, args->oldname, &path, olddfd);
	/* Expand LCONVPATHCREATE so that `path' can be freed on errors */
	error = linux_emul_convpath(td, args->newname, UIO_USERSPACE, &to, 1, newdfd);
	if (to == NULL) {
		LFREEPATH(path);
		return (error);
	}

	follow = (args->flag & LINUX_AT_SYMLINK_FOLLOW) == 0 ? NOFOLLOW :
	    FOLLOW;
	error = kern_linkat(td, olddfd, newdfd, path, to, UIO_SYSSPACE, follow);
	LFREEPATH(path);
	LFREEPATH(to);
	return (error);
}