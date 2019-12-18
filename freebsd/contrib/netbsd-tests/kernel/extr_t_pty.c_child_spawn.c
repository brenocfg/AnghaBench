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
struct pollfd {int fd; int events; int revents; } ;
typedef  int ssize_t ;
typedef  int pid_t ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 int POLLERR ; 
 int POLLIN ; 
 size_t buffer_size ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  dbuf ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,size_t,size_t) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fd_nonblock (int) ; 
 int fork () ; 
 size_t packets ; 
 int poll (struct pollfd*,int,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int qsize ; 
 int read (int,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  setsid () ; 
 int tty_open (char const*) ; 
 scalar_t__ verbose ; 

__attribute__((used)) static pid_t
child_spawn(const char *ttydev)
{
	pid_t		pid;
	int		tty;
	struct pollfd	pfd;
	size_t		total = 0;

	if ((pid = fork()) == -1)
		err(EXIT_FAILURE, "fork()");
	(void)setsid();
	if (pid != 0)
		return pid;

	if (verbose)
		(void)printf("child: started; open \"%s\"\n", ttydev);
	tty = tty_open(ttydev);
	fd_nonblock(tty);

	if (verbose)
		(void)printf("child: TTY open, starting read loop\n");
	pfd.fd = tty;
	pfd.events = POLLIN;
	pfd.revents = 0;
	for (;;) {
		int	ret;
		ssize_t	size;

		if (verbose)
			(void)printf("child: polling\n");
		if ((ret = poll(&pfd, 1, 2000)) == -1)
			err(EXIT_FAILURE, "child: poll()");
		if (ret == 0)
			break;
		if ((pfd.revents & POLLERR) != 0)
			break;
		if ((pfd.revents & POLLIN) != 0) {
			for (;;) {
				if (verbose)
					(void)printf(
					    "child: attempting to read %zu"
					    " bytes\n", buffer_size);
				if ((size = read(tty, dbuf, buffer_size))
				    == -1) {
					if (errno == EAGAIN)
						break;
					err(EXIT_FAILURE, "child: read()");
				}
				if (qsize && size < qsize &&
				    (size_t)size < buffer_size)
					errx(EXIT_FAILURE, "read returned %zd "
					    "less than the queue size %d",
					    size, qsize);
				if (verbose)
					(void)printf(
					    "child: read %zd bytes from TTY\n",
					    size);
				if (size == 0)
					goto end;
				total += size;
			}
		}
	}
end:
	if (verbose)
		(void)printf("child: closing TTY %zu\n", total);
	(void)close(tty);
	if (verbose)
		(void)printf("child: exiting\n");
	if (total != buffer_size * packets)
		errx(EXIT_FAILURE,
		    "Lost data %zu != %zu\n", total, buffer_size * packets);

	exit(EXIT_SUCCESS);
}