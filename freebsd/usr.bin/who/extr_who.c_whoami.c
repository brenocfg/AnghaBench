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
typedef  int /*<<< orphan*/  ut ;
struct utmpx {scalar_t__ ut_type; int /*<<< orphan*/  ut_tv; int /*<<< orphan*/  ut_user; int /*<<< orphan*/  ut_line; } ;
struct passwd {char* pw_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  STDIN_FILENO ; 
 scalar_t__ USER_PROCESS ; 
 int /*<<< orphan*/  _PATH_DEV ; 
 struct passwd* getpwuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gettimeofday (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getuid () ; 
 struct utmpx* getutxline (struct utmpx*) ; 
 int /*<<< orphan*/  memset (struct utmpx*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  row (struct utmpx*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 
 scalar_t__ strncmp (char const*,int /*<<< orphan*/ ,int) ; 
 char* ttyname (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
whoami(void)
{
	struct utmpx ut, *utx;
	struct passwd *pwd;
	const char *name, *tty;

	if ((tty = ttyname(STDIN_FILENO)) == NULL)
		tty = "tty??";
	else if (strncmp(tty, _PATH_DEV, sizeof _PATH_DEV - 1) == 0)
		tty += sizeof _PATH_DEV - 1;
	strlcpy(ut.ut_line, tty, sizeof ut.ut_line);

	/* Search utmp for our tty, dump first matching record. */
	if ((utx = getutxline(&ut)) != NULL && utx->ut_type == USER_PROCESS) {
		row(utx);
		return;
	}

	/* Not found; fill the utmp structure with the information we have. */
	memset(&ut, 0, sizeof(ut));
	if ((pwd = getpwuid(getuid())) != NULL)
		name = pwd->pw_name;
	else
		name = "?";
	strlcpy(ut.ut_user, name, sizeof ut.ut_user);
	gettimeofday(&ut.ut_tv, NULL);
	row(&ut);
}