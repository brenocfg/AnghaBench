#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ time_t ;
typedef  int /*<<< orphan*/  term ;
typedef  int /*<<< orphan*/  sigset_t ;
struct TYPE_4__ {scalar_t__ se_started; scalar_t__ se_nspace; int /*<<< orphan*/  se_device; int /*<<< orphan*/ * se_getty_argv; int /*<<< orphan*/  se_type; scalar_t__ se_window; } ;
typedef  TYPE_1__ session_t ;
typedef  int pid_t ;

/* Variables and functions */
 scalar_t__ GETTY_NSPACE ; 
 scalar_t__ GETTY_SLEEP ; 
 scalar_t__ GETTY_SPACING ; 
 int /*<<< orphan*/  RESOURCE_GETTY ; 
 int /*<<< orphan*/  SIG_SETMASK ; 
 unsigned int WINDOW_WAIT ; 
 int /*<<< orphan*/  _exit (int) ; 
 int /*<<< orphan*/  emergency (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  execve (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char**) ; 
 int fork () ; 
 int /*<<< orphan*/  setprocresources (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sleep (unsigned int) ; 
 int /*<<< orphan*/  stall (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  start_window_system (TYPE_1__*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  strlcat (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ time (scalar_t__*) ; 
 int /*<<< orphan*/  warning (char*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static pid_t
start_getty(session_t *sp)
{
	pid_t pid;
	sigset_t mask;
	time_t current_time = time((time_t *) 0);
	int too_quick = 0;
	char term[64], *env[2];

	if (current_time >= sp->se_started &&
	    current_time - sp->se_started < GETTY_SPACING) {
		if (++sp->se_nspace > GETTY_NSPACE) {
			sp->se_nspace = 0;
			too_quick = 1;
		}
	} else
		sp->se_nspace = 0;

	/*
	 * fork(), not vfork() -- we can't afford to block.
	 */
	if ((pid = fork()) == -1) {
		emergency("can't fork for getty on port %s: %m", sp->se_device);
		return -1;
	}

	if (pid)
		return pid;

	if (too_quick) {
		warning("getty repeating too quickly on port %s, sleeping %d secs",
		    sp->se_device, GETTY_SLEEP);
		sleep((unsigned) GETTY_SLEEP);
	}

	if (sp->se_window) {
		start_window_system(sp);
		sleep(WINDOW_WAIT);
	}

	sigemptyset(&mask);
	sigprocmask(SIG_SETMASK, &mask, NULL);

#ifdef LOGIN_CAP
	setprocresources(RESOURCE_GETTY);
#endif
	if (sp->se_type) {
		/* Don't use malloc after fork */
		strcpy(term, "TERM=");
		strlcat(term, sp->se_type, sizeof(term));
		env[0] = term;
		env[1] = NULL;
	} else
		env[0] = NULL;
	execve(sp->se_getty_argv[0], sp->se_getty_argv, env);
	stall("can't exec getty '%s' for port %s: %m",
		sp->se_getty_argv[0], sp->se_device);
	_exit(1);
}