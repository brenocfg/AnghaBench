#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int gl_matchc; scalar_t__ gl_pathc; char** gl_pathv; } ;
typedef  TYPE_1__ glob_t ;
typedef  int /*<<< orphan*/  gl ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int GLOB_BRACE ; 
 int GLOB_LIMIT ; 
 int GLOB_NOCHECK ; 
 int GLOB_TILDE ; 
 int MAXGLOBARGS ; 
 int MAXUSRARGS ; 
 int STDERR_FILENO ; 
 int STDIN_FILENO ; 
 int STDOUT_FILENO ; 
 int /*<<< orphan*/  _PATH_LS ; 
 int /*<<< orphan*/  _exit (int) ; 
 int* calloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  closelog () ; 
 int /*<<< orphan*/  dup2 (int,int) ; 
 int /*<<< orphan*/  execv (char*,char**) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fdopen (int,char*) ; 
 int /*<<< orphan*/  fds ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 size_t fileno (int /*<<< orphan*/ *) ; 
 int fork () ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  getdtablesize () ; 
 int /*<<< orphan*/ * getenv (char*) ; 
 int /*<<< orphan*/  geteuid () ; 
 int /*<<< orphan*/  getuid () ; 
 scalar_t__ glob (char*,int,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  globfree (TYPE_1__*) ; 
 int /*<<< orphan*/  ls_main (int,char**) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int optind ; 
 int optopt ; 
 int optreset ; 
 int* pids ; 
 scalar_t__ pipe (int*) ; 
 int /*<<< orphan*/  setenv (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setuid (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 char* strdup (char*) ; 
 char* strtok (char*,char*) ; 
 int /*<<< orphan*/  tzset () ; 
 int /*<<< orphan*/  unsetenv (char*) ; 
 int vfork () ; 

FILE *
ftpd_popen(char *program, char *type)
{
	char *cp;
	FILE *iop;
	int argc, gargc, pdes[2], pid;
	char **pop, *argv[MAXUSRARGS], *gargv[MAXGLOBARGS];

	if (((*type != 'r') && (*type != 'w')) || type[1])
		return (NULL);

	if (!pids) {
		if ((fds = getdtablesize()) <= 0)
			return (NULL);
		if ((pids = calloc(fds, sizeof(int))) == NULL)
			return (NULL);
	}
	if (pipe(pdes) < 0)
		return (NULL);

	/* break up string into pieces */
	for (argc = 0, cp = program; argc < MAXUSRARGS; cp = NULL) {
		if (!(argv[argc++] = strtok(cp, " \t\n")))
			break;
	}
	argv[argc - 1] = NULL;

	/* glob each piece */
	gargv[0] = argv[0];
	for (gargc = argc = 1; argv[argc] && gargc < (MAXGLOBARGS-1); argc++) {
		glob_t gl;
		int flags = GLOB_BRACE|GLOB_NOCHECK|GLOB_TILDE;

		memset(&gl, 0, sizeof(gl));
		gl.gl_matchc = MAXGLOBARGS;
		flags |= GLOB_LIMIT;
		if (glob(argv[argc], flags, NULL, &gl))
			gargv[gargc++] = strdup(argv[argc]);
		else if (gl.gl_pathc > 0) {
			for (pop = gl.gl_pathv; *pop && gargc < (MAXGLOBARGS-1);
			     pop++)
				gargv[gargc++] = strdup(*pop);
		}
		globfree(&gl);
	}
	gargv[gargc] = NULL;

	iop = NULL;
	fflush(NULL);
	pid = (strcmp(gargv[0], _PATH_LS) == 0) ? fork() : vfork();
	switch(pid) {
	case -1:			/* error */
		(void)close(pdes[0]);
		(void)close(pdes[1]);
		goto pfree;
		/* NOTREACHED */
	case 0:				/* child */
		if (*type == 'r') {
			if (pdes[1] != STDOUT_FILENO) {
				dup2(pdes[1], STDOUT_FILENO);
				(void)close(pdes[1]);
			}
			dup2(STDOUT_FILENO, STDERR_FILENO); /* stderr too! */
			(void)close(pdes[0]);
		} else {
			if (pdes[0] != STDIN_FILENO) {
				dup2(pdes[0], STDIN_FILENO);
				(void)close(pdes[0]);
			}
			(void)close(pdes[1]);
		}
		/* Drop privileges before proceeding */
		if (getuid() != geteuid() && setuid(geteuid()) < 0)
			_exit(1);
		if (strcmp(gargv[0], _PATH_LS) == 0) {
			/* Reset getopt for ls_main() */
			optreset = optind = optopt = 1;
			/* Close syslogging to remove pwd.db missing msgs */
			closelog();
			/* Trigger to sense new /etc/localtime after chroot */
			if (getenv("TZ") == NULL) {
				setenv("TZ", "", 0);
				tzset();
				unsetenv("TZ");
				tzset();
			}
			exit(ls_main(gargc, gargv));
		}
		execv(gargv[0], gargv);
		_exit(1);
	}
	/* parent; assume fdopen can't fail...  */
	if (*type == 'r') {
		iop = fdopen(pdes[0], type);
		(void)close(pdes[1]);
	} else {
		iop = fdopen(pdes[1], type);
		(void)close(pdes[0]);
	}
	pids[fileno(iop)] = pid;

pfree:	for (argc = 1; gargv[argc] != NULL; argc++)
		free(gargv[argc]);

	return (iop);
}