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
struct printer {int printer; int /*<<< orphan*/  daemon_user; } ;
struct passwd {int /*<<< orphan*/  pw_gid; int /*<<< orphan*/  pw_name; } ;
typedef  int pid_t ;

/* Variables and functions */
#define  DOABORT 129 
#define  DORETURN 128 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  daemon_defgid ; 
 int /*<<< orphan*/ * daemon_uname ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int fork () ; 
 struct passwd* getpwuid (int /*<<< orphan*/ ) ; 
 int initgroups (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int setgid (int /*<<< orphan*/ ) ; 
 int setuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/ * strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int,...) ; 

__attribute__((used)) static int
dofork(const struct printer *pp, int action)
{
	pid_t forkpid;
	int i, fail;
	struct passwd *pwd;

	forkpid = -1;
	if (daemon_uname == NULL) {
		pwd = getpwuid(pp->daemon_user);
		if (pwd == NULL) {
			syslog(LOG_ERR, "%s: Can't lookup default daemon uid (%ld) in password file",
			    pp->printer, pp->daemon_user);
			goto error_ret;
		}
		daemon_uname = strdup(pwd->pw_name);
		daemon_defgid = pwd->pw_gid;
	}

	for (i = 0; i < 20; i++) {
		forkpid = fork();
		if (forkpid < 0) {
			sleep((unsigned)(i*i));
			continue;
		}
		/*
		 * Child should run as daemon instead of root
		 */
		if (forkpid == 0) {
			errno = 0;
			fail = initgroups(daemon_uname, daemon_defgid);
			if (fail) {
				syslog(LOG_ERR, "%s: initgroups(%s,%u): %m",
				    pp->printer, daemon_uname, daemon_defgid);
				break;
			}
			fail = setgid(daemon_defgid);
			if (fail) {
				syslog(LOG_ERR, "%s: setgid(%u): %m",
				    pp->printer, daemon_defgid);
				break;
			}
			fail = setuid(pp->daemon_user);
			if (fail) {
				syslog(LOG_ERR, "%s: setuid(%ld): %m",
				    pp->printer, pp->daemon_user);
				break;
			}
		}
		return (forkpid);
	}

	/*
	 * An error occurred.  If the error is in the child process, then
	 * this routine MUST always exit().  DORETURN only effects how
	 * errors should be handled in the parent process.
	 */
error_ret:
	if (forkpid == 0) {
		syslog(LOG_ERR, "%s: dofork(): aborting child process...",
		    pp->printer);
		exit(1);
	}
	syslog(LOG_ERR, "%s: dofork(): failure in fork", pp->printer);

	sleep(1);		/* throttle errors, as a safety measure */
	switch (action) {
	case DORETURN:
		return (-1);
	default:
		syslog(LOG_ERR, "bad action (%d) to dofork", action);
		/* FALLTHROUGH */
	case DOABORT:
		exit(1);
	}
	/*NOTREACHED*/
}