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
struct stat {int /*<<< orphan*/  st_mode; } ;
struct linux_unlinkat_args {int flag; int dfd; int /*<<< orphan*/  pathname; } ;

/* Variables and functions */
 int AT_FDCWD ; 
 int /*<<< orphan*/  AT_SYMLINK_NOFOLLOW ; 
 int EINVAL ; 
 int EISDIR ; 
 int EPERM ; 
 int /*<<< orphan*/  FD_NONE ; 
 int /*<<< orphan*/  LCONVPATHEXIST_AT (struct thread*,int /*<<< orphan*/ ,char**,int) ; 
 int /*<<< orphan*/  LFREEPATH (char*) ; 
 int LINUX_AT_FDCWD ; 
 int LINUX_AT_REMOVEDIR ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int kern_frmdirat (struct thread*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int kern_funlinkat (struct thread*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ kern_statat (struct thread*,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ,struct stat*,int /*<<< orphan*/ *) ; 

int
linux_unlinkat(struct thread *td, struct linux_unlinkat_args *args)
{
	char *path;
	int error, dfd;
	struct stat st;

	if (args->flag & ~LINUX_AT_REMOVEDIR)
		return (EINVAL);

	dfd = (args->dfd == LINUX_AT_FDCWD) ? AT_FDCWD : args->dfd;
	LCONVPATHEXIST_AT(td, args->pathname, &path, dfd);

	if (args->flag & LINUX_AT_REMOVEDIR)
		error = kern_frmdirat(td, dfd, path, FD_NONE, UIO_SYSSPACE, 0);
	else
		error = kern_funlinkat(td, dfd, path, FD_NONE, UIO_SYSSPACE, 0,
		    0);
	if (error == EPERM && !(args->flag & LINUX_AT_REMOVEDIR)) {
		/* Introduce POSIX noncompliant behaviour of Linux */
		if (kern_statat(td, AT_SYMLINK_NOFOLLOW, dfd, path,
		    UIO_SYSSPACE, &st, NULL) == 0 && S_ISDIR(st.st_mode))
			error = EISDIR;
	}
	LFREEPATH(path);
	return (error);
}