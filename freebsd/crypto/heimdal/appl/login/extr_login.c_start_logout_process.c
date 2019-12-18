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
typedef  int pid_t ;

/* Variables and functions */
 scalar_t__ WIFEXITED (int) ; 
 scalar_t__ WIFSIGNALED (int) ; 
 int /*<<< orphan*/  env ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 int /*<<< orphan*/  execle (char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int fork () ; 
 int /*<<< orphan*/  getpid () ; 
 char* login_conf_get_string (char*) ; 
 int /*<<< orphan*/  setpgid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setproctitle (char*,int) ; 
 char* strrchr (char*,char) ; 
 int waitpid (int,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
start_logout_process(void)
{
    char *prog, *argv0;
    pid_t pid;

    prog = login_conf_get_string("logout_program");
    if(prog == NULL)
	return 0;
    argv0 = strrchr(prog, '/');

    if(argv0)
	argv0++;
    else
	argv0 = prog;

    pid = fork();
    if(pid == 0) {
	/* avoid getting signals sent to the shell */
	setpgid(0, getpid());
	return 0;
    }
    if(pid == -1)
	err(1, "fork");
    /* wait for the real login process to exit */
#ifdef HAVE_SETPROCTITLE
    setproctitle("waitpid %d", pid);
#endif
    while(1) {
	int status;
	int ret;
	ret = waitpid(pid, &status, 0);
	if(ret > 0) {
	    if(WIFEXITED(status) || WIFSIGNALED(status)) {
		execle(prog, argv0, NULL, env);
		err(1, "exec %s", prog);
	    }
	} else if(ret < 0)
	    err(1, "waitpid");
    }
}