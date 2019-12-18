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
struct pollfd {int fd; int events; int /*<<< orphan*/  revents; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIFONAME ; 
 scalar_t__ FT_FIFO ; 
 int O_NONBLOCK ; 
 int O_RDONLY ; 
 int POLLHUP ; 
 int POLLIN ; 
 int /*<<< orphan*/  SIGUSR1 ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ filetype ; 
 int /*<<< orphan*/  kill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int open (int /*<<< orphan*/ ,int) ; 
 int poll (struct pollfd*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppid ; 
 int read (int,char*,int) ; 
 int /*<<< orphan*/  report (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int,int) ; 
 int state ; 
 int /*<<< orphan*/  usleep (int) ; 

__attribute__((used)) static void
child(int fd, int num)
{
	struct pollfd pfd;
	int fd2, res;
	char buf[256];

	if (filetype == FT_FIFO) {
		fd = open(FIFONAME, O_RDONLY | O_NONBLOCK);
		if (fd < 0)
			err(1, "open for read");
	}
	pfd.fd = fd;
	pfd.events = POLLIN;

	if (filetype == FT_FIFO) {
		if ((res = poll(&pfd, 1, 0)) < 0)
			err(1, "poll");
		report(num++, "0", 0, pfd.revents, res, 0);
	}
	kill(ppid, SIGUSR1);

	usleep(1);
	while (state != 1)
		;
	if (filetype != FT_FIFO) {
		/*
		 * The connection cannot be reestablished.  Use the code that
		 * delays the read until after the writer disconnects since
		 * that case is more interesting.
		 */
		state = 4;
		goto state4;
	}
	if ((res = poll(&pfd, 1, 0)) < 0)
		err(1, "poll");
	report(num++, "1", 0, pfd.revents, res, 0);
	kill(ppid, SIGUSR1);

	usleep(1);
	while (state != 2)
		;
	if ((res = poll(&pfd, 1, 0)) < 0)
		err(1, "poll");
	report(num++, "2", POLLIN, pfd.revents, res, 1);
	if (read(fd, buf, sizeof buf) != 1)
		err(1, "read");
	if ((res = poll(&pfd, 1, 0)) < 0)
		err(1, "poll");
	report(num++, "2a", 0, pfd.revents, res, 0);
	kill(ppid, SIGUSR1);

	usleep(1);
	while (state != 3)
		;
	if ((res = poll(&pfd, 1, 0)) < 0)
		err(1, "poll");
	report(num++, "3", POLLHUP, pfd.revents, res, 1);
	kill(ppid, SIGUSR1);

	/*
	 * Now we expect a new writer, and a new connection too since
	 * we read all the data.  The only new point is that we didn't
	 * start quite from scratch since the read fd is not new.  Check
	 * startup state as above, but don't do the read as above.
	 */
	usleep(1);
	while (state != 4)
		;
state4:
	if ((res = poll(&pfd, 1, 0)) < 0)
		err(1, "poll");
	report(num++, "4", 0, pfd.revents, res, 0);
	kill(ppid, SIGUSR1);

	usleep(1);
	while (state != 5)
		;
	if ((res = poll(&pfd, 1, 0)) < 0)
		err(1, "poll");
	report(num++, "5", POLLIN, pfd.revents, res, 1);
	kill(ppid, SIGUSR1);

	usleep(1);
	while (state != 6)
		;
	/*
	 * Now we have no writer, but should still have data from the old
	 * writer.  Check that we have both a data-readable condition and a
	 * hangup condition, and that the data can be read in the usual way.
	 * Since Linux does this, programs must not quit reading when they
	 * see POLLHUP; they must see POLLHUP without POLLIN (or another
	 * input condition) before they decide that there is EOF.  gdb-6.1.1
	 * is an example of a broken program that quits on POLLHUP only --
	 * see its event-loop.c.
	 */
	if ((res = poll(&pfd, 1, 0)) < 0)
		err(1, "poll");
	report(num++, "6", POLLIN | POLLHUP, pfd.revents, res, 1);
	if (read(fd, buf, sizeof buf) != 1)
		err(1, "read");
	if ((res = poll(&pfd, 1, 0)) < 0)
		err(1, "poll");
	report(num++, "6a", POLLHUP, pfd.revents, res, 1);
	if (filetype == FT_FIFO) {
		/*
		 * Check that POLLHUP is sticky for a new reader and for
		 * the old reader.
		 */
		fd2 = open(FIFONAME, O_RDONLY | O_NONBLOCK);
		if (fd2 < 0)
			err(1, "open for read");
		pfd.fd = fd2;
		if ((res = poll(&pfd, 1, 0)) < 0)
			err(1, "poll");
		report(num++, "6b", POLLHUP, pfd.revents, res, 1);
		pfd.fd = fd;
		if ((res = poll(&pfd, 1, 0)) < 0)
			err(1, "poll");
		report(num++, "6c", POLLHUP, pfd.revents, res, 1);
		close(fd2);
		if ((res = poll(&pfd, 1, 0)) < 0)
			err(1, "poll");
		report(num++, "6d", POLLHUP, pfd.revents, res, 1);
	}
	close(fd);
	kill(ppid, SIGUSR1);

	exit(0);
}