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
struct linux_execve_args {int /*<<< orphan*/  envp; int /*<<< orphan*/  argp; int /*<<< orphan*/  path; } ;
struct image_args {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LCONVPATHEXIST (struct thread*,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 int freebsd32_exec_copyin_args (struct image_args*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int linux_common_execve (struct thread*,struct image_args*) ; 

int
linux_execve(struct thread *td, struct linux_execve_args *args)
{
	struct image_args eargs;
	char *path;
	int error;

	LCONVPATHEXIST(td, args->path, &path);

	error = freebsd32_exec_copyin_args(&eargs, path, UIO_SYSSPACE,
	    args->argp, args->envp);
	free(path, M_TEMP);
	if (error == 0)
		error = linux_common_execve(td, &eargs);
	return (error);
}