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
struct TYPE_2__ {scalar_t__ tv_sec; scalar_t__ tv_nsec; } ;
struct stat {TYPE_1__ st_mtim; } ;
struct sigaction {scalar_t__ sa_flags; int /*<<< orphan*/  sa_mask; int /*<<< orphan*/  sa_handler; } ;
typedef  int /*<<< orphan*/  sigset_t ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  SIGCHLD ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGQUIT ; 
 int /*<<< orphan*/  SIG_BLOCK ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  SIG_SETMASK ; 
 scalar_t__ WEXITSTATUS (int) ; 
 scalar_t__ WIFEXITED (int) ; 
 scalar_t__ WIFSTOPPED (int) ; 
 int /*<<< orphan*/  WSTOPSIG (int) ; 
 int /*<<< orphan*/  WUNTRACED ; 
 char* _PATH_VI ; 
 int /*<<< orphan*/  _exit (scalar_t__) ; 
 int editpid ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  execlp (char const*,char const*,int /*<<< orphan*/ ,char*) ; 
 int fork () ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  getgid () ; 
 int /*<<< orphan*/  getuid () ; 
 int /*<<< orphan*/  raise (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setgid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigaction (int /*<<< orphan*/ ,struct sigaction*,struct sigaction*) ; 
 int /*<<< orphan*/  sigaddset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int stat (int /*<<< orphan*/ ,struct stat*) ; 
 int /*<<< orphan*/  tempname ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ ) ; 
 int waitpid (int,int*,int /*<<< orphan*/ ) ; 

int
pw_edit(int notsetuid)
{
	struct sigaction sa, sa_int, sa_quit;
	sigset_t oldsigset, nsigset;
	struct stat st1, st2;
	const char *editor;
	int pstat;

	if ((editor = getenv("EDITOR")) == NULL)
		editor = _PATH_VI;
	if (stat(tempname, &st1) == -1)
		return (-1);
	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, &sa_int);
	sigaction(SIGQUIT, &sa, &sa_quit);
	sigemptyset(&nsigset);
	sigaddset(&nsigset, SIGCHLD);
	sigprocmask(SIG_BLOCK, &nsigset, &oldsigset);
	switch ((editpid = fork())) {
	case -1:
		return (-1);
	case 0:
		sigaction(SIGINT, &sa_int, NULL);
		sigaction(SIGQUIT, &sa_quit, NULL);
		sigprocmask(SIG_SETMASK, &oldsigset, NULL);
		if (notsetuid) {
			(void)setgid(getgid());
			(void)setuid(getuid());
		}
		errno = 0;
		execlp(editor, editor, tempname, (char *)NULL);
		_exit(errno);
	default:
		/* parent */
		break;
	}
	for (;;) {
		if (waitpid(editpid, &pstat, WUNTRACED) == -1) {
			if (errno == EINTR)
				continue;
			unlink(tempname);
			editpid = -1;
			break;
		} else if (WIFSTOPPED(pstat)) {
			raise(WSTOPSIG(pstat));
		} else if (WIFEXITED(pstat) && WEXITSTATUS(pstat) == 0) {
			editpid = -1;
			break;
		} else {
			unlink(tempname);
			editpid = -1;
			break;
		}
	}
	sigaction(SIGINT, &sa_int, NULL);
	sigaction(SIGQUIT, &sa_quit, NULL);
	sigprocmask(SIG_SETMASK, &oldsigset, NULL);
	if (stat(tempname, &st2) == -1)
		return (-1);
	return (st1.st_mtim.tv_sec != st2.st_mtim.tv_sec ||
	    st1.st_mtim.tv_nsec != st2.st_mtim.tv_nsec);
}