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
struct linux_faccessat_args {int amode; int dfd; int /*<<< orphan*/  filename; } ;

/* Variables and functions */
 int AT_FDCWD ; 
 int EINVAL ; 
 int F_OK ; 
 int /*<<< orphan*/  LCONVPATHEXIST_AT (struct thread*,int /*<<< orphan*/ ,char**,int) ; 
 int /*<<< orphan*/  LFREEPATH (char*) ; 
 int LINUX_AT_FDCWD ; 
 int R_OK ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int W_OK ; 
 int X_OK ; 
 int kern_accessat (struct thread*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int
linux_faccessat(struct thread *td, struct linux_faccessat_args *args)
{
	char *path;
	int error, dfd;

	/* Linux convention. */
	if (args->amode & ~(F_OK | X_OK | W_OK | R_OK))
		return (EINVAL);

	dfd = (args->dfd == LINUX_AT_FDCWD) ? AT_FDCWD : args->dfd;
	LCONVPATHEXIST_AT(td, args->filename, &path, dfd);

	error = kern_accessat(td, dfd, path, UIO_SYSSPACE, 0, args->amode);
	LFREEPATH(path);

	return (error);
}