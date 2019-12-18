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
typedef  char sftp_conn ;
struct complete_ctx {char* conn; char** remote_pathp; } ;
typedef  int /*<<< orphan*/  cmd ;
typedef  int /*<<< orphan*/  History ;
typedef  int /*<<< orphan*/  HistEvent ;
typedef  int /*<<< orphan*/  EditLine ;

/* Variables and functions */
 int /*<<< orphan*/  EL_ADDFN ; 
 int /*<<< orphan*/  EL_BIND ; 
 int /*<<< orphan*/  EL_CLIENTDATA ; 
 int /*<<< orphan*/  EL_EDITOR ; 
 int /*<<< orphan*/  EL_HIST ; 
 int /*<<< orphan*/  EL_PROMPT ; 
 int /*<<< orphan*/  EL_SIGNAL ; 
 int /*<<< orphan*/  EL_TERMINAL ; 
 int /*<<< orphan*/  H_ENTER ; 
 int /*<<< orphan*/  H_SETSIZE ; 
 int /*<<< orphan*/  SIGCHLD ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIG_DFL ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  STDIN_FILENO ; 
 int /*<<< orphan*/  _IOLBF ; 
 int batchmode ; 
 int /*<<< orphan*/  cmd_interrupt ; 
 int /*<<< orphan*/ * complete ; 
 char* do_realpath (char*,char*) ; 
 int /*<<< orphan*/  el_end (int /*<<< orphan*/ *) ; 
 char* el_gets (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/ * el_init (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  el_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  el_source (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fatal (char*) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ global_aflag ; 
 int /*<<< orphan*/  history (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/ * history_init () ; 
 int /*<<< orphan*/  infile ; 
 scalar_t__ interrupted ; 
 scalar_t__ isatty (int /*<<< orphan*/ ) ; 
 char* make_absolute (char*,char*) ; 
 int /*<<< orphan*/  mprintf (char*,char*) ; 
 scalar_t__ parse_dispatch_command (char*,char*,char**,char*,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  prompt ; 
 int /*<<< orphan*/  quiet ; 
 scalar_t__ remote_is_dir (char*,char*) ; 
 int /*<<< orphan*/  setvbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 
 int strlcpy (char*,char const*,int) ; 
 int strlen (char*) ; 
 char* strrchr (char*,char) ; 
 char* xstrdup (char*) ; 

__attribute__((used)) static int
interactive_loop(struct sftp_conn *conn, char *file1, char *file2)
{
	char *remote_path;
	char *dir = NULL, *startdir = NULL;
	char cmd[2048];
	int err, interactive;
	EditLine *el = NULL;
#ifdef USE_LIBEDIT
	History *hl = NULL;
	HistEvent hev;
	extern char *__progname;
	struct complete_ctx complete_ctx;

	if (!batchmode && isatty(STDIN_FILENO)) {
		if ((el = el_init(__progname, stdin, stdout, stderr)) == NULL)
			fatal("Couldn't initialise editline");
		if ((hl = history_init()) == NULL)
			fatal("Couldn't initialise editline history");
		history(hl, &hev, H_SETSIZE, 100);
		el_set(el, EL_HIST, history, hl);

		el_set(el, EL_PROMPT, prompt);
		el_set(el, EL_EDITOR, "emacs");
		el_set(el, EL_TERMINAL, NULL);
		el_set(el, EL_SIGNAL, 1);
		el_source(el, NULL);

		/* Tab Completion */
		el_set(el, EL_ADDFN, "ftp-complete",
		    "Context sensitive argument completion", complete);
		complete_ctx.conn = conn;
		complete_ctx.remote_pathp = &remote_path;
		el_set(el, EL_CLIENTDATA, (void*)&complete_ctx);
		el_set(el, EL_BIND, "^I", "ftp-complete", NULL);
		/* enable ctrl-left-arrow and ctrl-right-arrow */
		el_set(el, EL_BIND, "\\e[1;5C", "em-next-word", NULL);
		el_set(el, EL_BIND, "\\e[5C", "em-next-word", NULL);
		el_set(el, EL_BIND, "\\e[1;5D", "ed-prev-word", NULL);
		el_set(el, EL_BIND, "\\e\\e[D", "ed-prev-word", NULL);
		/* make ^w match ksh behaviour */
		el_set(el, EL_BIND, "^w", "ed-delete-prev-word", NULL);
	}
#endif /* USE_LIBEDIT */

	remote_path = do_realpath(conn, ".");
	if (remote_path == NULL)
		fatal("Need cwd");
	startdir = xstrdup(remote_path);

	if (file1 != NULL) {
		dir = xstrdup(file1);
		dir = make_absolute(dir, remote_path);

		if (remote_is_dir(conn, dir) && file2 == NULL) {
			if (!quiet)
				mprintf("Changing to: %s\n", dir);
			snprintf(cmd, sizeof cmd, "cd \"%s\"", dir);
			if (parse_dispatch_command(conn, cmd,
			    &remote_path, startdir, 1) != 0) {
				free(dir);
				free(startdir);
				free(remote_path);
				free(conn);
				return (-1);
			}
		} else {
			/* XXX this is wrong wrt quoting */
			snprintf(cmd, sizeof cmd, "get%s %s%s%s",
			    global_aflag ? " -a" : "", dir,
			    file2 == NULL ? "" : " ",
			    file2 == NULL ? "" : file2);
			err = parse_dispatch_command(conn, cmd,
			    &remote_path, startdir, 1);
			free(dir);
			free(startdir);
			free(remote_path);
			free(conn);
			return (err);
		}
		free(dir);
	}

	setvbuf(stdout, NULL, _IOLBF, 0);
	setvbuf(infile, NULL, _IOLBF, 0);

	interactive = !batchmode && isatty(STDIN_FILENO);
	err = 0;
	for (;;) {
		char *cp;

		signal(SIGINT, SIG_IGN);

		if (el == NULL) {
			if (interactive)
				printf("sftp> ");
			if (fgets(cmd, sizeof(cmd), infile) == NULL) {
				if (interactive)
					printf("\n");
				break;
			}
			if (!interactive) { /* Echo command */
				mprintf("sftp> %s", cmd);
				if (strlen(cmd) > 0 &&
				    cmd[strlen(cmd) - 1] != '\n')
					printf("\n");
			}
		} else {
#ifdef USE_LIBEDIT
			const char *line;
			int count = 0;

			if ((line = el_gets(el, &count)) == NULL ||
			    count <= 0) {
				printf("\n");
 				break;
			}
			history(hl, &hev, H_ENTER, line);
			if (strlcpy(cmd, line, sizeof(cmd)) >= sizeof(cmd)) {
				fprintf(stderr, "Error: input line too long\n");
				continue;
			}
#endif /* USE_LIBEDIT */
		}

		cp = strrchr(cmd, '\n');
		if (cp)
			*cp = '\0';

		/* Handle user interrupts gracefully during commands */
		interrupted = 0;
		signal(SIGINT, cmd_interrupt);

		err = parse_dispatch_command(conn, cmd, &remote_path,
		    startdir, batchmode);
		if (err != 0)
			break;
	}
	signal(SIGCHLD, SIG_DFL);
	free(remote_path);
	free(startdir);
	free(conn);

#ifdef USE_LIBEDIT
	if (el != NULL)
		el_end(el);
#endif /* USE_LIBEDIT */

	/* err == 1 signifies normal "quit" exit */
	return (err >= 0 ? 0 : -1);
}