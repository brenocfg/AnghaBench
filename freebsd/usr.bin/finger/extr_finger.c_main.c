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
struct passwd {scalar_t__ pw_uid; scalar_t__ pw_gid; } ;

/* Variables and functions */
 int /*<<< orphan*/  LC_ALL ; 
 int /*<<< orphan*/  UNPRIV_NAME ; 
 scalar_t__ UNPRIV_UGID ; 
 scalar_t__ entries ; 
 int /*<<< orphan*/  err (int,char*) ; 
 char* getenv (char*) ; 
 scalar_t__ geteuid () ; 
 struct passwd* getpwnam (int /*<<< orphan*/ ) ; 
 scalar_t__ getuid () ; 
 int invoker_root ; 
 int lflag ; 
 int /*<<< orphan*/  lflag_print () ; 
 int /*<<< orphan*/  loginlist () ; 
 int /*<<< orphan*/  now ; 
 int oflag ; 
 int option (int,char**) ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ setgid (scalar_t__) ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  setpassent (int) ; 
 scalar_t__ setuid (scalar_t__) ; 
 int sflag ; 
 int /*<<< orphan*/  sflag_print () ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  userlist (int,char**) ; 

int
main(int argc, char **argv)
{
	int envargc, argcnt;
	char *envargv[3];
	struct passwd *pw;
	static char myname[] = "finger";

	if (getuid() == 0 || geteuid() == 0) {
		invoker_root = 1;
		if ((pw = getpwnam(UNPRIV_NAME)) && pw->pw_uid > 0) {
			if (setgid(pw->pw_gid) != 0)
				err(1, "setgid()");
			if (setuid(pw->pw_uid) != 0)
				err(1, "setuid()");
		} else {
			if (setgid(UNPRIV_UGID) != 0)
				err(1, "setgid()");
			if (setuid(UNPRIV_UGID) != 0)
				err(1, "setuid()");
		}
	}

	(void) setlocale(LC_ALL, "");

				/* remove this line to get remote host */
	oflag = 1;		/* default to old "office" behavior */

	/*
	 * Process environment variables followed by command line arguments.
	 */
	if ((envargv[1] = getenv("FINGER"))) {
		envargc = 2;
		envargv[0] = myname;
		envargv[2] = NULL;
		(void) option(envargc, envargv);
	}

	argcnt = option(argc, argv);
	argc -= argcnt;
	argv += argcnt;

	(void)time(&now);
	setpassent(1);
	if (!*argv) {
		/*
		 * Assign explicit "small" format if no names given and -l
		 * not selected.  Force the -s BEFORE we get names so proper
		 * screening will be done.
		 */
		if (!lflag)
			sflag = 1;	/* if -l not explicit, force -s */
		loginlist();
		if (entries == 0)
			(void)printf("No one logged on.\n");
	} else {
		userlist(argc, argv);
		/*
		 * Assign explicit "large" format if names given and -s not
		 * explicitly stated.  Force the -l AFTER we get names so any
		 * remote finger attempts specified won't be mishandled.
		 */
		if (!sflag)
			lflag = 1;	/* if -s not explicit, force -l */
	}
	if (entries) {
		if (lflag)
			lflag_print();
		else
			sflag_print();
	}
	return (0);
}