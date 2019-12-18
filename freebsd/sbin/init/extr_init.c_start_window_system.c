#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  term ;
typedef  int /*<<< orphan*/  sigset_t ;
struct TYPE_3__ {int /*<<< orphan*/  se_device; int /*<<< orphan*/ * se_window_argv; int /*<<< orphan*/  se_type; } ;
typedef  TYPE_1__ session_t ;
typedef  int pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  RESOURCE_WINDOW ; 
 int /*<<< orphan*/  SIG_SETMASK ; 
 int /*<<< orphan*/  _exit (int) ; 
 int /*<<< orphan*/  emergency (char*,...) ; 
 int /*<<< orphan*/  execve (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char**) ; 
 int fork () ; 
 int /*<<< orphan*/  setprocresources (int /*<<< orphan*/ ) ; 
 scalar_t__ setsid () ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stall (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  strlcat (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  waitpid (int,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
start_window_system(session_t *sp)
{
	pid_t pid;
	sigset_t mask;
	char term[64], *env[2];
	int status;

	if ((pid = fork()) == -1) {
		emergency("can't fork for window system on port %s: %m",
		    sp->se_device);
		/* hope that getty fails and we can try again */
		return;
	}
	if (pid) {
		waitpid(-1, &status, 0);
		return;
	}

	/* reparent window process to the init to not make a zombie on exit */
	if ((pid = fork()) == -1) {
		emergency("can't fork for window system on port %s: %m",
		    sp->se_device);
		_exit(1);
	}
	if (pid)
		_exit(0);

	sigemptyset(&mask);
	sigprocmask(SIG_SETMASK, &mask, NULL);

	if (setsid() < 0)
		emergency("setsid failed (window) %m");

#ifdef LOGIN_CAP
	setprocresources(RESOURCE_WINDOW);
#endif
	if (sp->se_type) {
		/* Don't use malloc after fork */
		strcpy(term, "TERM=");
		strlcat(term, sp->se_type, sizeof(term));
		env[0] = term;
		env[1] = NULL;
	}
	else
		env[0] = NULL;
	execve(sp->se_window_argv[0], sp->se_window_argv, env);
	stall("can't exec window system '%s' for port %s: %m",
		sp->se_window_argv[0], sp->se_device);
	_exit(1);
}