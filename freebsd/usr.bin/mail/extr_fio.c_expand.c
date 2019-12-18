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
typedef  int /*<<< orphan*/  xname ;
struct stat {int dummy; } ;
typedef  int /*<<< orphan*/  cmdbuf ;

/* Variables and functions */
 int BUFSIZ ; 
 int PATHSIZE ; 
 scalar_t__ SIGPIPE ; 
 scalar_t__ WIFSIGNALED (int /*<<< orphan*/ ) ; 
 scalar_t__ WTERMSIG (int /*<<< orphan*/ ) ; 
 char* _PATH_CSHELL ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  findmail (char*,char*,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ getfold (char*,int) ; 
 char* homedir ; 
 char* myname ; 
 scalar_t__ pipe (int*) ; 
 char* prevfile ; 
 int /*<<< orphan*/  printf (char*) ; 
 int read (int,char*,int) ; 
 char* savestr (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,...) ; 
 int start_command (char*,int /*<<< orphan*/ ,int,int,char*,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strchr (char*,char) ; 
 int /*<<< orphan*/  strpbrk (char*,char*) ; 
 char* value (char*) ; 
 scalar_t__ wait_child (int) ; 
 int /*<<< orphan*/  wait_status ; 
 int /*<<< orphan*/  warn (char*) ; 

char *
expand(char *name)
{
	char xname[PATHSIZE];
	char cmdbuf[PATHSIZE];		/* also used for file names */
	int pid, l;
	char *cp, *sh;
	int pivec[2];
	struct stat sbuf;

	/*
	 * The order of evaluation is "%" and "#" expand into constants.
	 * "&" can expand into "+".  "+" can expand into shell meta characters.
	 * Shell meta characters expand into constants.
	 * This way, we make no recursive expansion.
	 */
	switch (*name) {
	case '%':
		findmail(name[1] ? name + 1 : myname, xname, sizeof(xname));
		return (savestr(xname));
	case '#':
		if (name[1] != 0)
			break;
		if (prevfile[0] == 0) {
			printf("No previous file\n");
			return (NULL);
		}
		return (savestr(prevfile));
	case '&':
		if (name[1] == 0 && (name = value("MBOX")) == NULL)
			name = "~/mbox";
		/* fall through */
	}
	if (name[0] == '+' && getfold(cmdbuf, sizeof(cmdbuf)) >= 0) {
		(void)snprintf(xname, sizeof(xname), "%s/%s", cmdbuf, name + 1);
		name = savestr(xname);
	}
	/* catch the most common shell meta character */
	if (name[0] == '~' && homedir != NULL &&
	    (name[1] == '/' || name[1] == '\0')) {
		(void)snprintf(xname, sizeof(xname), "%s%s", homedir, name + 1);
		name = savestr(xname);
	}
	if (!strpbrk(name, "~{[*?$`'\"\\"))
		return (savestr(name));
	if (pipe(pivec) < 0) {
		warn("pipe");
		return (NULL);
	}
	(void)snprintf(cmdbuf, sizeof(cmdbuf), "echo %s", name);
	if ((sh = value("SHELL")) == NULL)
		sh = _PATH_CSHELL;
	pid = start_command(sh, 0, -1, pivec[1], "-c", cmdbuf, NULL);
	if (pid < 0) {
		(void)close(pivec[0]);
		(void)close(pivec[1]);
		return (NULL);
	}
	(void)close(pivec[1]);
	l = read(pivec[0], xname, BUFSIZ);
	(void)close(pivec[0]);
	if (wait_child(pid) < 0 && WIFSIGNALED(wait_status) &&
	    WTERMSIG(wait_status) != SIGPIPE) {
		fprintf(stderr, "\"%s\": Expansion failed.\n", name);
		return (NULL);
	}
	if (l < 0) {
		warn("read");
		return (NULL);
	}
	if (l == 0) {
		fprintf(stderr, "\"%s\": No match.\n", name);
		return (NULL);
	}
	if (l == BUFSIZ) {
		fprintf(stderr, "\"%s\": Expansion buffer overflow.\n", name);
		return (NULL);
	}
	xname[l] = '\0';
	for (cp = &xname[l-1]; *cp == '\n' && cp > xname; cp--)
		;
	cp[1] = '\0';
	if (strchr(xname, ' ') && stat(xname, &sbuf) < 0) {
		fprintf(stderr, "\"%s\": Ambiguous.\n", name);
		return (NULL);
	}
	return (savestr(xname));
}