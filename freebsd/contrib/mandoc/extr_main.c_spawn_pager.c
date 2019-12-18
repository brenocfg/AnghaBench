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
struct timespec {int member_1; int /*<<< orphan*/  member_0; } ;
struct tag_files {char* tfn; char* tagname; char* ofn; int tfd; int /*<<< orphan*/  ofd; int /*<<< orphan*/  pager_pid; } ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  MANDOCERR_DUP ; 
 int /*<<< orphan*/  MANDOCERR_EXEC ; 
 int /*<<< orphan*/  MANDOCERR_FORK ; 
 int /*<<< orphan*/  MANDOCERR_PLEDGE ; 
 int MAX_PAGER_ARGS ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 int /*<<< orphan*/  _exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int dup2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  execvp (char*,char**) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fork () ; 
 char* getenv (char*) ; 
 scalar_t__ getpid () ; 
 int /*<<< orphan*/  mandoc_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  mandoc_msg_getrc () ; 
 char* mandoc_strdup (char const*) ; 
 int /*<<< orphan*/  nanosleep (struct timespec const*,int /*<<< orphan*/ *) ; 
 int pledge (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setpgid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 size_t strlen (char*) ; 
 scalar_t__ tcgetpgrp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcsetpgrp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static pid_t
spawn_pager(struct tag_files *tag_files)
{
	const struct timespec timeout = { 0, 100000000 };  /* 0.1s */
#define MAX_PAGER_ARGS 16
	char		*argv[MAX_PAGER_ARGS];
	const char	*pager;
	char		*cp;
#if HAVE_LESS_T
	size_t		 cmdlen;
#endif
	int		 argc, use_ofn;
	pid_t		 pager_pid;

	pager = getenv("MANPAGER");
	if (pager == NULL || *pager == '\0')
		pager = getenv("PAGER");
	if (pager == NULL || *pager == '\0')
		pager = "less -s";
	cp = mandoc_strdup(pager);

	/*
	 * Parse the pager command into words.
	 * Intentionally do not do anything fancy here.
	 */

	argc = 0;
	while (argc + 5 < MAX_PAGER_ARGS) {
		argv[argc++] = cp;
		cp = strchr(cp, ' ');
		if (cp == NULL)
			break;
		*cp++ = '\0';
		while (*cp == ' ')
			cp++;
		if (*cp == '\0')
			break;
	}

	/* For less(1), use the tag file. */

	use_ofn = 1;
#if HAVE_LESS_T
	if (*tag_files->tfn != '\0' && (cmdlen = strlen(argv[0])) >= 4) {
		cp = argv[0] + cmdlen - 4;
		if (strcmp(cp, "less") == 0) {
			argv[argc++] = mandoc_strdup("-T");
			argv[argc++] = tag_files->tfn;
			if (tag_files->tagname != NULL) {
				argv[argc++] = mandoc_strdup("-t");
				argv[argc++] = tag_files->tagname;
				use_ofn = 0;
			}
		}
	}
#endif
	if (use_ofn)
		argv[argc++] = tag_files->ofn;
	argv[argc] = NULL;

	switch (pager_pid = fork()) {
	case -1:
		mandoc_msg(MANDOCERR_FORK, 0, 0, "%s", strerror(errno));
		exit(mandoc_msg_getrc());
	case 0:
		break;
	default:
		(void)setpgid(pager_pid, 0);
		(void)tcsetpgrp(tag_files->ofd, pager_pid);
#if HAVE_PLEDGE
		if (pledge("stdio rpath tmppath tty proc", NULL) == -1) {
			mandoc_msg(MANDOCERR_PLEDGE, 0, 0,
			    "%s", strerror(errno));
			exit(mandoc_msg_getrc());
		}
#endif
		tag_files->pager_pid = pager_pid;
		return pager_pid;
	}

	/* The child process becomes the pager. */

	if (dup2(tag_files->ofd, STDOUT_FILENO) == -1) {
		mandoc_msg(MANDOCERR_DUP, 0, 0, "%s", strerror(errno));
		_exit(mandoc_msg_getrc());
	}
	close(tag_files->ofd);
	assert(tag_files->tfd == -1);

	/* Do not start the pager before controlling the terminal. */

	while (tcgetpgrp(STDOUT_FILENO) != getpid())
		nanosleep(&timeout, NULL);

	execvp(argv[0], argv);
	mandoc_msg(MANDOCERR_EXEC, 0, 0, "%s: %s", argv[0], strerror(errno));
	_exit(mandoc_msg_getrc());
}