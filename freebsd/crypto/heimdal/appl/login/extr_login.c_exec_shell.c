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
 char const* _PATH_BSHELL ; 
 int asprintf (char**,char*,char const*) ; 
 int /*<<< orphan*/  env ; 
 int /*<<< orphan*/  err (int,char*,char const*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  execle (char const*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  extend_env (int /*<<< orphan*/ *) ; 
 scalar_t__ start_login_process () ; 
 int /*<<< orphan*/  start_logout_process () ; 
 char* strrchr (char const*,char) ; 
 int /*<<< orphan*/  warn (char*) ; 
 int /*<<< orphan*/  warnx (char*,char const*,char const*) ; 

__attribute__((used)) static void
exec_shell(const char *shell, int fallback)
{
    char *sh;
    const char *p;

    extend_env(NULL);
    if(start_login_process() < 0)
	warn("login process");
    start_logout_process();

    p = strrchr(shell, '/');
    if(p)
	p++;
    else
	p = shell;
    if (asprintf(&sh, "-%s", p) == -1)
	errx(1, "Out of memory");
    execle(shell, sh, NULL, env);
    if(fallback){
	warnx("Can't exec %s, trying %s",
	      shell, _PATH_BSHELL);
	execle(_PATH_BSHELL, "-sh", NULL, env);
	err(1, "%s", _PATH_BSHELL);
    }
    err(1, "%s", shell);
}