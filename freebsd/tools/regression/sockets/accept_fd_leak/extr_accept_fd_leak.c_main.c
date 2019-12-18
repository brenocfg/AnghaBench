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
struct TYPE_2__ {void* s_addr; } ;
struct sockaddr_in {int sin_len; void* sin_port; TYPE_1__ sin_addr; void* sin_family; } ;
struct sockaddr {int dummy; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  sin ;
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 void* AF_INET ; 
 int BIND_ATTEMPTS ; 
 scalar_t__ EAGAIN ; 
 scalar_t__ EFAULT ; 
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFL ; 
 int /*<<< orphan*/  INADDR_LOOPBACK ; 
 int LOOPS ; 
 int MAX (int,int) ; 
 int NUM_ATTEMPTS ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  SIGCHLD ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  STDIN_FILENO ; 
 scalar_t__ WEXITSTATUS (int) ; 
 int /*<<< orphan*/  WIFEXITED (int) ; 
 int /*<<< orphan*/  _exit (int /*<<< orphan*/ ) ; 
 int accept (int,struct sockaddr*,int*) ; 
 scalar_t__ bind (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  bzero (struct sockaddr_in*,int) ; 
 int /*<<< orphan*/  child_died ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ connect (int,struct sockaddr*,int) ; 
 int dup (int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ fcntl (int,int /*<<< orphan*/ ,...) ; 
 scalar_t__ fork () ; 
 void* htonl (int /*<<< orphan*/ ) ; 
 void* htons (int) ; 
 scalar_t__ listen (int,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  quit ; 
 scalar_t__ random () ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  srandomdev () ; 
 int strerror (scalar_t__) ; 
 int /*<<< orphan*/  usleep (int) ; 
 scalar_t__ waitpid (scalar_t__,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*,int) ; 
 int /*<<< orphan*/  warnx (char*) ; 

int
main(void)
{
	struct sockaddr_in sin;
	socklen_t size;
	pid_t child;
	int fd1, fd2, fd3, i, listen_port, s, status;

	printf("1..2\n");

	/*
	 * Check for sequential fd allocation, and give up early if not.
	 */
	fd1 = dup(STDIN_FILENO);
	fd2 = dup(STDIN_FILENO);
	if (fd2 != fd1 + 1)
		errx(-1, "Non-sequential fd allocation\n");

	s = socket(PF_INET, SOCK_STREAM, 0);
	if (s == -1)
		errx(-1, "socket: %s", strerror(errno));

	bzero(&sin, sizeof(sin));
	sin.sin_len = sizeof(sin);
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

	srandomdev();

	for (i = 0; i < BIND_ATTEMPTS; i++) {
		/* Pick a random unprivileged port 1025-65535 */
		listen_port = MAX((int)random() % 65535, 1025);
		sin.sin_port = htons(listen_port);
		if (bind(s, (struct sockaddr *)&sin, sizeof(sin)) == 0)
			break;
		warn("bind with %d failed", listen_port);
		usleep(1000);
	}
	if (i >= BIND_ATTEMPTS) {
		printf("Bail out!\n");
		exit(1);
	}

	if (listen(s, -1) != 0)
		errx(-1, "listen: %s", strerror(errno));

	i = fcntl(s, F_GETFL);
	if (i == -1)
		errx(-1, "ioctl(F_GETFL): %s", strerror(errno));
	i |= O_NONBLOCK;
	if (fcntl(s, F_SETFL, i) != 0)
		errx(-1, "ioctl(F_SETFL): %s", strerror(errno));
	i = fcntl(s, F_GETFL);
	if (i == -1)
		errx(-1, "ioctl(F_GETFL): %s", strerror(errno));
	if ((i & O_NONBLOCK) != O_NONBLOCK)
		errx(-1, "Failed to set O_NONBLOCK (i=0x%x)\n", i);

	for (i = 0; i < LOOPS; i++) {
		size = sizeof(sin);
		if (accept(s, (struct sockaddr *)&sin, &size) != -1)
			errx(-1, "accept succeeded\n");
		if (errno != EAGAIN)
			errx(-1, "accept: %s", strerror(errno));
	}

	/*
	 * Allocate a file descriptor and make sure it's fd2+2.  2 because
	 * we allocate an fd for the socket.
	 */
	fd3 = dup(STDIN_FILENO);
	if (fd3 != fd2 + 2)
		printf("not ok 1 - (%d, %d, %d)\n", fd1, fd2, fd3);
	else
		printf("ok 1\n");

	/*
	 * Try failing accept's w/o non-blocking where the destination
	 * address pointer is invalid.
	 */
	close(fd3);
	signal(SIGCHLD, child_died);
	child = fork();
	if (child < 0)
		errx(-1, "fork: %s", strerror(errno));

	/*
	 * Child process does `NUM_ATTEMPTS` connects.
	 */
	if (child == 0) {
		close(fd1);
		close(fd2);
		close(s);

		bzero(&sin, sizeof(sin));
		sin.sin_len = sizeof(sin);
		sin.sin_family = AF_INET;
		sin.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
		sin.sin_port = htons(listen_port);

		for (i = 0; i < NUM_ATTEMPTS; i++) {
			s = socket(PF_INET, SOCK_STREAM, 0);
			if (s == -1)
				errx(-1, "socket: %s", strerror(errno));
			if (connect(s, (struct sockaddr *)&sin,
			    sizeof(sin)) < 0)
				errx(-1, "connect: %s", strerror(errno));
			close(s);
		}
		_exit(0);
	}

	/* Reset back to a blocking socket. */
	i = fcntl(s, F_GETFL);
	if (i == -1)
		errx(-1, "ioctl(F_GETFL): %s", strerror(errno));
	i &= ~O_NONBLOCK;
	if (fcntl(s, F_SETFL, i) != 0)
		errx(-1, "ioctl(F_SETFL): %s", strerror(errno));
	i = fcntl(s, F_GETFL);
	if (i == -1)
		errx(-1, "ioctl(F_GETFL): %s", strerror(errno));
	if (i & O_NONBLOCK)
		errx(-1, "Failed to clear O_NONBLOCK (i=0x%x)\n", i);

	/* Do `NUM_ATTEMPTS` accepts with an invalid pointer. */
	for (i = 0; !quit && i < NUM_ATTEMPTS; i++) {
		size = sizeof(sin);
		if (accept(s, (struct sockaddr *)(uintptr_t)(0x100),
		    &size) != -1)
			errx(-1, "accept succeeded\n");
		if (errno != EFAULT)
			errx(-1, "accept: %s", strerror(errno));
	}

	if (waitpid(child, &status, 0) < 0)
		errx(-1, "waitpid: %s", strerror(errno));
	if (!WIFEXITED(status) || WEXITSTATUS(status) != 0)
		warnx("child process died");

	/*
	 * Allocate a file descriptor and make sure it's fd2+2.  2 because
	 * we allocate an fd for the socket.
	 */
	fd3 = dup(STDIN_FILENO);
	if (fd3 != fd2 + 2)
		printf("not ok 2 - (%d, %d, %d)\n", fd1, fd2, fd3);
	else
		printf("ok 2\n");

	return (0);
}