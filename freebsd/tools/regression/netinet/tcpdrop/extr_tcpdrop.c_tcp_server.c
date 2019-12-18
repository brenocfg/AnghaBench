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
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  pid_t ;
typedef  int /*<<< orphan*/  ch ;

/* Variables and functions */
 int EPIPE ; 
 int /*<<< orphan*/  MSG_NOSIGNAL ; 
 int /*<<< orphan*/  SIGTERM ; 
 int accept (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int errno ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  kill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int send (int,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sleep (int) ; 

__attribute__((used)) static void
tcp_server(pid_t partner, int listen_fd)
{
	int error, accept_fd;
	ssize_t len;
	char ch;

	accept_fd = accept(listen_fd, NULL, NULL);
	if (accept_fd < 0) {
		error = errno;
		(void)kill(partner, SIGTERM);
		errno = error;
		err(-1, "tcp_server: accept");
	}

	/*
	 * Send one byte, make sure that worked, wait for the drop, and try
	 * sending another.  By sending small amounts, we avoid blocking
	 * waiting on the remote buffer to be drained.
	 */
	ch = 'A';
	len = send(accept_fd, &ch, sizeof(ch), MSG_NOSIGNAL);
	if (len < 0) {
		error = errno;
		(void)kill(partner, SIGTERM);
		errno = error;
		err(-1, "tcp_server: send (1)");
	}
	if (len != sizeof(ch)) {
		(void)kill(partner, SIGTERM);
		errx(-1, "tcp_server: send (1) len");
	}

	sleep (10);

	ch = 'A';
	len = send(accept_fd, &ch, sizeof(ch), MSG_NOSIGNAL);
	if (len >= 0) {
		(void)kill(partner, SIGTERM);
		errx(-1, "tcp_server: send (2): success");
	} else if (errno != EPIPE) {
		error = errno;
		(void)kill(partner, SIGTERM);
		errno = error;
		err(-1, "tcp_server: send (2)");
	}

	close(accept_fd);
	close(listen_fd);
}