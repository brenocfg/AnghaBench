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
struct sbuf {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  E2BIG ; 
 int /*<<< orphan*/  ENOMEM ; 
 scalar_t__ ISMAGICNO (char*) ; 
 int /*<<< orphan*/  SBUF_AUTOEXTEND ; 
 char* _PATH_BSHELL ; 
 int /*<<< orphan*/  _SC_ARG_MAX ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errc (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 scalar_t__ exec_shell (char*,char*,char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getenv (char*) ; 
 int getopt (int,char**,char*) ; 
 char* malloc (size_t) ; 
 char* optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  optopt ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int sbuf_cat (struct sbuf*,char*) ; 
 int /*<<< orphan*/  sbuf_clear (struct sbuf*) ; 
 char* sbuf_data (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_delete (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_finish (struct sbuf*) ; 
 long sbuf_len (struct sbuf*) ; 
 struct sbuf* sbuf_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int sbuf_putc (struct sbuf*,char) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int) ; 
 char* strdup (char*) ; 
 int /*<<< orphan*/  strlcat (char*,char*,size_t) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,size_t) ; 
 int strlen (char*) ; 
 char* strrchr (char*,char) ; 
 long sysconf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char *argv[])
{
	struct sbuf *cmdbuf;
	long arg_max;
	int ch, debug, i, magic, n, nargs, rval;
	size_t cmdsize;
	char buf[4];
	char *cmd, *name, *p, *shell, *slashp, *tmpshell;

	debug = 0;
	magic = '%';		/* Default magic char is `%'. */
	nargs = -1;
	while ((ch = getopt(argc, argv, "a:d0123456789")) != -1)
		switch (ch) {
		case 'a':
			if (optarg[0] == '\0' || optarg[1] != '\0')
				errx(1,
				    "illegal magic character specification");
			magic = optarg[0];
			break;
		case 'd':
			debug = 1;
			break;
		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
			if (nargs != -1)
				errx(1,
				    "only one -# argument may be specified");
			nargs = optopt - '0';
			break;
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

	if (argc < 2)
		usage();

	/*
	 * The command to run is argv[0], and the args are argv[1..].
	 * Look for %digit references in the command, remembering the
	 * largest one.
	 */
	for (n = 0, p = argv[0]; *p != '\0'; ++p)
		if (ISMAGICNO(p)) {
			++p;
			if (p[0] - '0' > n)
				n = p[0] - '0';
		}

	/*
	 * Figure out the shell and name arguments to pass to execl()
	 * in exec_shell().  Always malloc() shell and just set name
	 * to point at the last part of shell if there are any backslashes,
	 * otherwise just set it to point at the space malloc()'d.  If
	 * SHELL environment variable exists, replace contents of
	 * shell with it.
	 */
	shell = name = NULL;
	tmpshell = getenv("SHELL");
	shell = (tmpshell != NULL) ? strdup(tmpshell) : strdup(_PATH_BSHELL);
	if (shell == NULL)
		err(1, "strdup() failed");
	slashp = strrchr(shell, '/');
	name = (slashp != NULL) ? slashp + 1 : shell;

	/*
	 * If there were any %digit references, then use those, otherwise
	 * build a new command string with sufficient %digit references at
	 * the end to consume (nargs) arguments each time round the loop.
	 * Allocate enough space to hold the maximum command.  Save the
	 * size to pass to snprintf().
	 */
	if (n == 0) {
		cmdsize = strlen(argv[0]) + 9 * (sizeof(" %1") - 1) + 1;
		if ((cmd = malloc(cmdsize)) == NULL)
			err(1, NULL);
		strlcpy(cmd, argv[0], cmdsize);

		/* If nargs not set, default to a single argument. */
		if (nargs == -1)
			nargs = 1;

		for (i = 1; i <= nargs; i++) {
			snprintf(buf, sizeof(buf), " %c%d", magic, i);
			strlcat(cmd, buf, cmdsize);
		}

		/*
		 * If nargs set to the special value 0, eat a single
		 * argument for each command execution.
		 */
		if (nargs == 0)
			nargs = 1;
	} else {
		if ((cmd = strdup(argv[0])) == NULL)
			err(1, NULL);
		nargs = n;
	}

	cmdbuf = sbuf_new(NULL, NULL, 1024, SBUF_AUTOEXTEND);
	if (cmdbuf == NULL)
		err(1, NULL);

	arg_max = sysconf(_SC_ARG_MAX);

	/*
	 * (argc) and (argv) are still offset by one to make it simpler to
	 * expand %digit references.  At the end of the loop check for (argc)
	 * equals 1 means that all the (argv) has been consumed.
	 */
	for (rval = 0; argc > nargs; argc -= nargs, argv += nargs) {
		sbuf_clear(cmdbuf);
		sbuf_cat(cmdbuf, "exec ");
		/* Expand command argv references. */
		for (p = cmd; *p != '\0'; ++p) {
			if (ISMAGICNO(p)) {
				if (sbuf_cat(cmdbuf, argv[(++p)[0] - '0'])
				    == -1)
					errc(1, ENOMEM, "sbuf");
			} else {
				if (sbuf_putc(cmdbuf, *p) == -1)
					errc(1, ENOMEM, "sbuf");
			}
			if (sbuf_len(cmdbuf) > arg_max)
				errc(1, E2BIG, NULL);
		}

		/* Terminate the command string. */
		sbuf_finish(cmdbuf);

		/* Run the command. */
		if (debug)
			(void)printf("%s\n", sbuf_data(cmdbuf));
		else
			if (exec_shell(sbuf_data(cmdbuf), shell, name))
				rval = 1;
	}

	if (argc != 1)
		errx(1, "expecting additional argument%s after \"%s\"",
		    (nargs - argc) ? "s" : "", argv[argc - 1]);
	free(cmd);
	sbuf_delete(cmdbuf);
	free(shell);
	exit(rval);
}