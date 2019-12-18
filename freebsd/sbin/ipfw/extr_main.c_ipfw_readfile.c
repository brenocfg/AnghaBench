#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int pid_t ;
typedef  int /*<<< orphan*/  linename ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {int do_compact; int do_force; int do_resolv; int test_only; int do_quiet; int show_sets; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* EX_OK ; 
 int /*<<< orphan*/  EX_OSERR ; 
 int /*<<< orphan*/  EX_UNAVAILABLE ; 
 int /*<<< orphan*/  EX_USAGE ; 
 int /*<<< orphan*/  SIGTERM ; 
 char* WEXITSTATUS (int) ; 
 scalar_t__ WIFEXITED (int) ; 
 scalar_t__ WIFSIGNALED (int) ; 
 char* WTERMSIG (int) ; 
 int /*<<< orphan*/  close (int) ; 
 TYPE_1__ co ; 
 int dup2 (int,int) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,...) ; 
 int errno ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  execvp (char const*,char**) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fdopen (int,char*) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int fork () ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  ipfw_main (int,char**) ; 
 int /*<<< orphan*/  kill (int,int /*<<< orphan*/ ) ; 
 char* optarg ; 
 int optind ; 
 int pipe (int*) ; 
 int /*<<< orphan*/  setprogname (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int waitpid (int,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ipfw_readfile(int ac, char *av[])
{
#define MAX_ARGS	32
	char buf[4096];
	char *progname = av[0];		/* original program name */
	const char *cmd = NULL;		/* preprocessor name, if any */
	const char *filename = av[ac-1]; /* file to read */
	int	c, lineno=0;
	FILE	*f = NULL;
	pid_t	preproc = 0;

	while ((c = getopt(ac, av, "cfNnp:qS")) != -1) {
		switch(c) {
		case 'c':
			co.do_compact = 1;
			break;

		case 'f':
			co.do_force = 1;
			break;

		case 'N':
			co.do_resolv = 1;
			break;

		case 'n':
			co.test_only = 1;
			break;

		case 'p':
			/*
			 * ipfw -p cmd [args] filename
			 *
			 * We are done with getopt(). All arguments
			 * except the filename go to the preprocessor,
			 * so we need to do the following:
			 * - check that a filename is actually present;
			 * - advance av by optind-1 to skip arguments
			 *   already processed;
			 * - decrease ac by optind, to remove the args
			 *   already processed and the final filename;
			 * - set the last entry in av[] to NULL so
			 *   popen() can detect the end of the array;
			 * - set optind=ac to let getopt() terminate.
			 */
			if (optind == ac)
				errx(EX_USAGE, "no filename argument");
			cmd = optarg;
			av[ac-1] = NULL;
			av += optind - 1;
			ac -= optind;
			optind = ac;
			break;

		case 'q':
			co.do_quiet = 1;
			break;

		case 'S':
			co.show_sets = 1;
			break;

		default:
			errx(EX_USAGE, "bad arguments, for usage"
			     " summary ``ipfw''");
		}

	}

	if (cmd == NULL && ac != optind + 1)
		errx(EX_USAGE, "extraneous filename arguments %s", av[ac-1]);

	if ((f = fopen(filename, "r")) == NULL)
		err(EX_UNAVAILABLE, "fopen: %s", filename);

	if (cmd != NULL) {			/* pipe through preprocessor */
		int pipedes[2];

		if (pipe(pipedes) == -1)
			err(EX_OSERR, "cannot create pipe");

		preproc = fork();
		if (preproc == -1)
			err(EX_OSERR, "cannot fork");

		if (preproc == 0) {
			/*
			 * Child, will run the preprocessor with the
			 * file on stdin and the pipe on stdout.
			 */
			if (dup2(fileno(f), 0) == -1
			    || dup2(pipedes[1], 1) == -1)
				err(EX_OSERR, "dup2()");
			fclose(f);
			close(pipedes[1]);
			close(pipedes[0]);
			execvp(cmd, av);
			err(EX_OSERR, "execvp(%s) failed", cmd);
		} else { /* parent, will reopen f as the pipe */
			fclose(f);
			close(pipedes[1]);
			if ((f = fdopen(pipedes[0], "r")) == NULL) {
				int savederrno = errno;

				(void)kill(preproc, SIGTERM);
				errno = savederrno;
				err(EX_OSERR, "fdopen()");
			}
		}
	}

	while (fgets(buf, sizeof(buf), f)) {		/* read commands */
		char linename[20];
		char *args[2];

		lineno++;
		snprintf(linename, sizeof(linename), "Line %d", lineno);
		setprogname(linename); /* XXX */
		args[0] = progname;
		args[1] = buf;
		ipfw_main(2, args);
	}
	fclose(f);
	if (cmd != NULL) {
		int status;

		if (waitpid(preproc, &status, 0) == -1)
			errx(EX_OSERR, "waitpid()");
		if (WIFEXITED(status) && WEXITSTATUS(status) != EX_OK)
			errx(EX_UNAVAILABLE,
			    "preprocessor exited with status %d",
			    WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
			errx(EX_UNAVAILABLE,
			    "preprocessor exited with signal %d",
			    WTERMSIG(status));
	}
}