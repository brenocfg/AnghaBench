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
struct linux_mkdirat_args {int dfd; int /*<<< orphan*/  mode; int /*<<< orphan*/  pathname; } ;

/* Variables and functions */
 int AT_FDCWD ; 
 int /*<<< orphan*/  LCONVPATHCREAT_AT (struct thread*,int /*<<< orphan*/ ,char**,int) ; 
 int /*<<< orphan*/  LFREEPATH (char*) ; 
 int LINUX_AT_FDCWD ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int kern_mkdirat (struct thread*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
linux_mkdirat(struct thread *td, struct linux_mkdirat_args *args)
{
	char *path;
	int error, dfd;

	dfd = (args->dfd == LINUX_AT_FDCWD) ? AT_FDCWD : args->dfd;
	LCONVPATHCREAT_AT(td, args->pathname, &path, dfd);

	error = kern_mkdirat(td, dfd, path, UIO_SYSSPACE, args->mode);
	LFREEPATH(path);
	return (error);
}