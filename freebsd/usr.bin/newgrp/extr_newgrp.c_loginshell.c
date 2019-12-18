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
typedef  int /*<<< orphan*/  login_cap_t ;
struct TYPE_4__ {char* pw_shell; char* pw_dir; char* pw_name; int /*<<< orphan*/  pw_uid; } ;

/* Variables and functions */
 int LOGIN_SETENV ; 
 int LOGIN_SETPATH ; 
 int LOGIN_SETUMASK ; 
 char* _PATH_BSHELL ; 
 scalar_t__ asprintf (char**,char*,char const*) ; 
 char** calloc (int,int) ; 
 scalar_t__ chdir (char*) ; 
 char** environ ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 int /*<<< orphan*/  execv (char const*,char**) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  login_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * login_getpwclass (TYPE_1__*) ; 
 TYPE_1__* pwd ; 
 int /*<<< orphan*/  setenv (char*,char const*,int) ; 
 int /*<<< orphan*/  setusercontext (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  warn (char*,char*) ; 

__attribute__((used)) static void
loginshell(void)
{
	char *args[2], **cleanenv, *term, *ticket;
	const char *shell;
	login_cap_t *lc;

	shell = pwd->pw_shell;
	if (*shell == '\0')
		shell = _PATH_BSHELL;
	if (chdir(pwd->pw_dir) < 0) {
		warn("%s", pwd->pw_dir);
		chdir("/");
	}

	term = getenv("TERM");
	ticket = getenv("KRBTKFILE");

	if ((cleanenv = calloc(20, sizeof(char *))) == NULL)
		err(1, "calloc");
	*cleanenv = NULL;
	environ = cleanenv;

	lc = login_getpwclass(pwd);
	setusercontext(lc, pwd, pwd->pw_uid,
	    LOGIN_SETPATH|LOGIN_SETUMASK|LOGIN_SETENV);
	login_close(lc);
	setenv("USER", pwd->pw_name, 1);
	setenv("SHELL", shell, 1);
	setenv("HOME", pwd->pw_dir, 1);
	if (term != NULL)
		setenv("TERM", term, 1);
	if (ticket != NULL)
		setenv("KRBTKFILE", ticket, 1);

	if (asprintf(args, "-%s", shell) < 0)
		err(1, "asprintf");
	args[1] = NULL;

	execv(shell, args);
	err(1, "%s", shell);
}