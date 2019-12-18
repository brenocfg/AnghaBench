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
 int /*<<< orphan*/  O_RDONLY ; 
 int STDIN_FILENO ; 
 int /*<<< orphan*/  _PATH_DEVNULL ; 
 int /*<<< orphan*/  _PATH_TTY ; 
 int /*<<< orphan*/  _exit (int) ; 
 scalar_t__ childerr ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  dup2 (int,int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  execvp (char*,char**) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  oflag ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pflag ; 
 int /*<<< orphan*/  pids_add (int /*<<< orphan*/ ) ; 
 int prompt () ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ tflag ; 
 int /*<<< orphan*/  vfork () ; 
 int /*<<< orphan*/  waitchildren (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*) ; 
 int /*<<< orphan*/  xexit (char*,int) ; 

__attribute__((used)) static void
run(char **argv)
{
	pid_t pid;
	int fd;
	char **avec;

	/*
	 * If the user wants to be notified of each command before it is
	 * executed, notify them.  If they want the notification to be
	 * followed by a prompt, then prompt them.
	 */
	if (tflag || pflag) {
		(void)fprintf(stderr, "%s", *argv);
		for (avec = argv + 1; *avec != NULL; ++avec)
			(void)fprintf(stderr, " %s", *avec);
		/*
		 * If the user has asked to be prompted, do so.
		 */
		if (pflag)
			/*
			 * If they asked not to exec, return without execution
			 * but if they asked to, go to the execution.  If we
			 * could not open their tty, break the switch and drop
			 * back to -t behaviour.
			 */
			switch (prompt()) {
			case 0:
				return;
			case 1:
				goto exec;
			case 2:
				break;
			}
		(void)fprintf(stderr, "\n");
		(void)fflush(stderr);
	}
exec:
	childerr = 0;
	switch (pid = vfork()) {
	case -1:
		warn("vfork");
		xexit(*argv, 1);
	case 0:
		if (oflag) {
			if ((fd = open(_PATH_TTY, O_RDONLY)) == -1)
				err(1, "can't open /dev/tty");
		} else {
			fd = open(_PATH_DEVNULL, O_RDONLY);
		}
		if (fd > STDIN_FILENO) {
			if (dup2(fd, STDIN_FILENO) != 0)
				err(1, "can't dup2 to stdin");
			close(fd);
		}
		execvp(argv[0], argv);
		childerr = errno;
		_exit(1);
	}
	pids_add(pid);
	waitchildren(*argv, 0);
}