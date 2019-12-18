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
struct sigaction {int /*<<< orphan*/  sa_mask; int /*<<< orphan*/  sa_handler; } ;
typedef  int /*<<< orphan*/  sa ;

/* Variables and functions */
 scalar_t__ EACCES ; 
 int /*<<< orphan*/  RESOURCE_RC ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGTSTP ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  SIG_SETMASK ; 
 int /*<<< orphan*/  X_OK ; 
 int access (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (struct sigaction*,int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  execv (char const*,char**) ; 
 char* get_shell () ; 
 int /*<<< orphan*/  open_console () ; 
 int /*<<< orphan*/  setprocresources (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stall (char*,char const*,char const*) ; 
 int /*<<< orphan*/  warning (char*,char const*) ; 

__attribute__((used)) static void
execute_script(char *argv[])
{
	struct sigaction sa;
	const char *shell, *script;
	int error;

	bzero(&sa, sizeof(sa));
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGTSTP, &sa, NULL);
	sigaction(SIGHUP, &sa, NULL);

	open_console();

	sigprocmask(SIG_SETMASK, &sa.sa_mask, NULL);
#ifdef LOGIN_CAP
	setprocresources(RESOURCE_RC);
#endif

	/*
	 * Try to directly execute the script first.  If it
	 * fails, try the old method of passing the script path
	 * to sh(1).  Don't complain if it fails because of
	 * the missing execute bit.
	 */
	script = argv[1];
	error = access(script, X_OK);
	if (error == 0) {
		execv(script, argv + 1);
		warning("can't directly exec %s: %m", script);
	} else if (errno != EACCES) {
		warning("can't access %s: %m", script);
	}

	shell = get_shell();
	execv(shell, argv);
	stall("can't exec %s for %s: %m", shell, script);
}