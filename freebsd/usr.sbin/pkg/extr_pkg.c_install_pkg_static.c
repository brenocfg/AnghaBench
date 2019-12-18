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
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int WEXITSTATUS (int) ; 
 scalar_t__ WIFSIGNALED (int) ; 
 int WTERMSIG (int) ; 
 int /*<<< orphan*/  _exit (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  execl (char const*,char*,char*,char const*,char const*,...) ; 
 int /*<<< orphan*/  fork () ; 
 int waitpid (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
install_pkg_static(const char *path, const char *pkgpath, bool force)
{
	int pstat;
	pid_t pid;

	switch ((pid = fork())) {
	case -1:
		return (-1);
	case 0:
		if (force)
			execl(path, "pkg-static", "add", "-f", pkgpath,
			    (char *)NULL);
		else
			execl(path, "pkg-static", "add", pkgpath,
			    (char *)NULL);
		_exit(1);
	default:
		break;
	}

	while (waitpid(pid, &pstat, 0) == -1)
		if (errno != EINTR)
			return (-1);

	if (WEXITSTATUS(pstat))
		return (WEXITSTATUS(pstat));
	else if (WIFSIGNALED(pstat))
		return (128 & (WTERMSIG(pstat)));
	return (pstat);
}