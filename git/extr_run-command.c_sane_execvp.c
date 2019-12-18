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

/* Variables and functions */
 int EACCES ; 
 int ENOENT ; 
 int ENOTDIR ; 
 int errno ; 
 int /*<<< orphan*/  execvp (char const*,char* const*) ; 
 scalar_t__ exists_in_PATH (char const*) ; 
 int /*<<< orphan*/  strchr (char const*,char) ; 
 int trace2_exec (char const*,char const**) ; 
 int /*<<< orphan*/  trace2_exec_result (int,int) ; 

int sane_execvp(const char *file, char * const argv[])
{
#ifndef GIT_WINDOWS_NATIVE
	/*
	 * execvp() doesn't return, so we all we can do is tell trace2
	 * what we are about to do and let it leave a hint in the log
	 * (unless of course the execvp() fails).
	 *
	 * we skip this for Windows because the compat layer already
	 * has to emulate the execvp() call anyway.
	 */
	int exec_id = trace2_exec(file, (const char **)argv);
#endif

	if (!execvp(file, argv))
		return 0; /* cannot happen ;-) */

#ifndef GIT_WINDOWS_NATIVE
	{
		int ec = errno;
		trace2_exec_result(exec_id, ec);
		errno = ec;
	}
#endif

	/*
	 * When a command can't be found because one of the directories
	 * listed in $PATH is unsearchable, execvp reports EACCES, but
	 * careful usability testing (read: analysis of occasional bug
	 * reports) reveals that "No such file or directory" is more
	 * intuitive.
	 *
	 * We avoid commands with "/", because execvp will not do $PATH
	 * lookups in that case.
	 *
	 * The reassignment of EACCES to errno looks like a no-op below,
	 * but we need to protect against exists_in_PATH overwriting errno.
	 */
	if (errno == EACCES && !strchr(file, '/'))
		errno = exists_in_PATH(file) ? EACCES : ENOENT;
	else if (errno == ENOTDIR && !strchr(file, '/'))
		errno = ENOENT;
	return -1;
}