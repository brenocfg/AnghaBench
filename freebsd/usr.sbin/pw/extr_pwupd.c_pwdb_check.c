#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int pid_t ;
struct TYPE_2__ {char* etcpath; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ WEXITSTATUS (int) ; 
 int /*<<< orphan*/  _MASTERPASSWD ; 
 int /*<<< orphan*/  _PATH_PWD ; 
 char* _PATH_PWD_MKDB ; 
 int /*<<< orphan*/  _exit (int) ; 
 TYPE_1__ conf ; 
 int errno ; 
 int /*<<< orphan*/  execv (char*,char**) ; 
 int fork () ; 
 char* getpwpath (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  waitpid (int,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pwdb_check(void)
{
	int             i = 0;
	pid_t           pid;
	char           *args[10];

	args[i++] = _PATH_PWD_MKDB;
	args[i++] = "-C";

	if (strcmp(conf.etcpath, _PATH_PWD) != 0) {
		args[i++] = "-d";
		args[i++] = conf.etcpath;
	}
	args[i++] = getpwpath(_MASTERPASSWD);
	args[i] = NULL;

	if ((pid = fork()) == -1)	/* Error (errno set) */
		i = errno;
	else if (pid == 0) {	/* Child */
		execv(args[0], args);
		_exit(1);
	} else {		/* Parent */
		waitpid(pid, &i, 0);
		if (WEXITSTATUS(i))
			i = EIO;
	}

	return (i);
}