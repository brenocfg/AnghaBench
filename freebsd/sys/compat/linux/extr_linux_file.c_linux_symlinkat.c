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
struct linux_symlinkat_args {int newdfd; int /*<<< orphan*/  newname; int /*<<< orphan*/  oldname; } ;

/* Variables and functions */
 int AT_FDCWD ; 
 int /*<<< orphan*/  LCONVPATHEXIST (struct thread*,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  LFREEPATH (char*) ; 
 int LINUX_AT_FDCWD ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int /*<<< orphan*/  UIO_USERSPACE ; 
 int kern_symlinkat (struct thread*,char*,int,char*,int /*<<< orphan*/ ) ; 
 int linux_emul_convpath (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**,int,int) ; 

int
linux_symlinkat(struct thread *td, struct linux_symlinkat_args *args)
{
	char *path, *to;
	int error, dfd;

	dfd = (args->newdfd == LINUX_AT_FDCWD) ? AT_FDCWD : args->newdfd;
	LCONVPATHEXIST(td, args->oldname, &path);
	/* Expand LCONVPATHCREATE so that `path' can be freed on errors */
	error = linux_emul_convpath(td, args->newname, UIO_USERSPACE, &to, 1, dfd);
	if (to == NULL) {
		LFREEPATH(path);
		return (error);
	}

	error = kern_symlinkat(td, path, dfd, to, UIO_SYSSPACE);
	LFREEPATH(path);
	LFREEPATH(to);
	return (error);
}