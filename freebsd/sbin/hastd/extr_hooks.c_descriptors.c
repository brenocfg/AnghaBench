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

/* Variables and functions */
 int /*<<< orphan*/  LOG_WARNING ; 
 int MAX (int,int) ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  O_WRONLY ; 
 scalar_t__ PJDLOG_MODE_STD ; 
 int STDERR_FILENO ; 
 int STDIN_FILENO ; 
 int STDOUT_FILENO ; 
 int /*<<< orphan*/  _PATH_DEVNULL ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  closefrom (int) ; 
 int dup2 (int,int) ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pjdlog_errno (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ pjdlog_mode_get () ; 

__attribute__((used)) static void
descriptors(void)
{
	int fd;

	/*
	 * Close all (or almost all) descriptors.
	 */
	if (pjdlog_mode_get() == PJDLOG_MODE_STD) {
		closefrom(MAX(MAX(STDIN_FILENO, STDOUT_FILENO),
		    STDERR_FILENO) + 1);
		return;
	}

	closefrom(0);

	/*
	 * Redirect stdin, stdout and stderr to /dev/null.
	 */
	fd = open(_PATH_DEVNULL, O_RDONLY);
	if (fd == -1) {
		pjdlog_errno(LOG_WARNING, "Unable to open %s for reading",
		    _PATH_DEVNULL);
	} else if (fd != STDIN_FILENO) {
		if (dup2(fd, STDIN_FILENO) == -1) {
			pjdlog_errno(LOG_WARNING,
			    "Unable to duplicate descriptor for stdin");
		}
		close(fd);
	}
	fd = open(_PATH_DEVNULL, O_WRONLY);
	if (fd == -1) {
		pjdlog_errno(LOG_WARNING, "Unable to open %s for writing",
		    _PATH_DEVNULL);
	} else {
		if (fd != STDOUT_FILENO && dup2(fd, STDOUT_FILENO) == -1) {
			pjdlog_errno(LOG_WARNING,
			    "Unable to duplicate descriptor for stdout");
		}
		if (fd != STDERR_FILENO && dup2(fd, STDERR_FILENO) == -1) {
			pjdlog_errno(LOG_WARNING,
			    "Unable to duplicate descriptor for stderr");
		}
		if (fd != STDOUT_FILENO && fd != STDERR_FILENO)
			close(fd);
	}
}