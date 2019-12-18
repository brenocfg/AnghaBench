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
struct pr {int kq; int /*<<< orphan*/  e; int /*<<< orphan*/  ostdout; } ;
struct kevent {int dummy; } ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  EVFILT_PROCDESC ; 
 int /*<<< orphan*/  EV_ADD ; 
 int /*<<< orphan*/  EV_SET (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NOTE_EXIT ; 
 int /*<<< orphan*/  PD_CLOEXEC ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int STDIN_FILENO ; 
 int STDOUT_FILENO ; 
 int /*<<< orphan*/  _PATH_PR ; 
 int /*<<< orphan*/  _exit (int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  diffargs ; 
 int /*<<< orphan*/  dup (int) ; 
 int /*<<< orphan*/  dup2 (int,int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  execl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int kevent (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int kqueue () ; 
 int /*<<< orphan*/  pdfork (int*,int /*<<< orphan*/ ) ; 
 int pipe (int*) ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int status ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  xasprintf (char**,char*,int /*<<< orphan*/ ,char*,char*) ; 
 struct pr* xcalloc (int,int) ; 
 int /*<<< orphan*/  xmalloc (int) ; 

struct pr *
start_pr(char *file1, char *file2)
{
	int pfd[2];
	int pr_pd;
	pid_t pid;
	char *header;
	struct pr *pr;

	pr = xcalloc(1, sizeof(*pr));

	xasprintf(&header, "%s %s %s", diffargs, file1, file2);
	signal(SIGPIPE, SIG_IGN);
	fflush(stdout);
	rewind(stdout);
	if (pipe(pfd) == -1)
		err(2, "pipe");
	switch ((pid = pdfork(&pr_pd, PD_CLOEXEC))) {
	case -1:
		status |= 2;
		free(header);
		err(2, "No more processes");
	case 0:
		/* child */
		if (pfd[0] != STDIN_FILENO) {
			dup2(pfd[0], STDIN_FILENO);
			close(pfd[0]);
		}
		close(pfd[1]);
		execl(_PATH_PR, _PATH_PR, "-h", header, (char *)0);
		_exit(127);
	default:

		/* parent */
		if (pfd[1] != STDOUT_FILENO) {
			pr->ostdout = dup(STDOUT_FILENO);
			dup2(pfd[1], STDOUT_FILENO);
			close(pfd[1]);
			close(pfd[1]);
			}
			close(pfd[0]);
			rewind(stdout);
			free(header);
			pr->kq = kqueue();
			if (pr->kq == -1)
				err(2, "kqueue");
			pr->e = xmalloc(sizeof(struct kevent));
			EV_SET(pr->e, pr_pd, EVFILT_PROCDESC, EV_ADD, NOTE_EXIT, 0,
			    NULL);
			if (kevent(pr->kq, pr->e, 1, NULL, 0, NULL) == -1)
				err(2, "kevent");
	}
	return (pr);
}