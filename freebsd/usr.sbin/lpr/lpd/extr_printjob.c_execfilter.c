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
struct printer {int /*<<< orphan*/  printer; } ;
typedef  scalar_t__ pid_t ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int BUFSIZ ; 
 int /*<<< orphan*/  DORETURN ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  STDERR_FILENO ; 
 int /*<<< orphan*/  STDIN_FILENO ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 int WEXITSTATUS (int) ; 
 int /*<<< orphan*/  closeallfds (int) ; 
 int /*<<< orphan*/  closelog () ; 
 scalar_t__ dofork (struct printer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dup2 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  execv (char*,char**) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int open (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stderr ; 
 char* strrchr (char*,char) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tempstderr ; 
 scalar_t__ wait (int*) ; 

__attribute__((used)) static int
execfilter(struct printer *pp, char *f_cmd, char *f_av[], int infd, int outfd)
{
	pid_t fpid, wpid;
	int errfd, retcode, wstatus;
	FILE *errfp;
	char buf[BUFSIZ], *slash;

	fpid = dofork(pp, DORETURN);
	if (fpid != 0) {
		/*
		 * This is the parent process, which just waits for the child
		 * to complete and then returns the result.  Note that it is
		 * the child process which reads the input stream.
		 */
		if (fpid < 0)
			retcode = 100;
		else {
			while ((wpid = wait(&wstatus)) > 0 &&
			    wpid != fpid)
				;
			if (wpid < 0) {
				retcode = 100;
				syslog(LOG_WARNING,
				    "%s: after execv(%s), wait() returned: %m",
				    pp->printer, f_cmd);
			} else
				retcode = WEXITSTATUS(wstatus);
		}

		/*
		 * Copy everything the filter wrote to stderr from our
		 * temporary errors file to the "lf=" logfile.
		 */
		errfp = fopen(tempstderr, "r");
		if (errfp) {
			while (fgets(buf, sizeof(buf), errfp))
				fputs(buf, stderr);
			fclose(errfp);
		}

		return (retcode);
	}

	/*
	 * This is the child process, which is the one that executes the
	 * given filter.
	 */
	/*
	 * If the first parameter has any slashes in it, then change it
	 * to point to the first character after the last slash.
	 */
	slash = strrchr(f_av[0], '/');
	if (slash != NULL)
		f_av[0] = slash + 1;
	/*
	 * XXX - in the future, this should setup an explicit list of
	 *       environment variables and use execve()!
	 */

	/*
	 * Setup stdin, stdout, and stderr as we want them when the filter
	 * is running.  Stderr is setup so it points to a temporary errors
	 * file, and the parent process will copy that temporary file to
	 * the real logfile after the filter completes.
	 */
	dup2(infd, STDIN_FILENO);
	dup2(outfd, STDOUT_FILENO);
	errfd = open(tempstderr, O_WRONLY|O_TRUNC, 0664);
	if (errfd >= 0)
		dup2(errfd, STDERR_FILENO);
	closelog();
	closeallfds(3);
	execv(f_cmd, f_av);
	syslog(LOG_ERR, "%s: cannot execv(%s): %m", pp->printer, f_cmd);
	exit(2);
	/* NOTREACHED */
}