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
struct thread {int* td_retval; } ;
struct linux_getcwd_args {int bufsize; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int ERANGE ; 
 int /*<<< orphan*/  LINUX_PATH_MAX ; 
 int /*<<< orphan*/  M_LINUX ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int copyout (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 int kern___getcwd (struct thread*,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 char* malloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 

int
linux_getcwd(struct thread *td, struct linux_getcwd_args *args)
{
	char *path;
	int error, lenused;

	/*
	 * Linux returns ERANGE instead of EINVAL.
	 */
	if (args->bufsize < 2)
		return (ERANGE);

	path = malloc(LINUX_PATH_MAX, M_LINUX, M_WAITOK);

	error = kern___getcwd(td, path, UIO_SYSSPACE, args->bufsize,
	    LINUX_PATH_MAX);
	if (error == 0) {
		lenused = strlen(path) + 1;
		error = copyout(path, args->buf, lenused);
		if (error == 0)
			td->td_retval[0] = lenused;
	}

	free(path, M_LINUX);
	return (error);
}