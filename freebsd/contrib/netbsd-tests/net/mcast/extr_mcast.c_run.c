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
 int /*<<< orphan*/  AF_UNIX ; 
 int /*<<< orphan*/  ERRX (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ERRX0 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int WEXITSTATUS (int) ; 
 int /*<<< orphan*/  WIFEXITED (int) ; 
 int /*<<< orphan*/  WIFSIGNALED (int) ; 
 int /*<<< orphan*/  WNOHANG ; 
 int /*<<< orphan*/  WTERMSIG (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fork () ; 
 int kill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  receiver (int,char const*,char const*,size_t,int,int) ; 
 int sender (int,char const*,char const*,size_t,int,int) ; 
 int socketpair (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int strerror (int /*<<< orphan*/ ) ; 
 int strsignal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  waitpid (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
run(const char *host, const char *port, size_t n, bool conn, bool bug)
{
	pid_t pid;
	int status;
	int syncfds[2];
	int error;

	if (socketpair(AF_UNIX, SOCK_STREAM, 0, syncfds) == -1)
		ERRX(EXIT_FAILURE, "socketpair (%s)", strerror(errno));

	switch ((pid = fork())) {
	case 0:
		receiver(syncfds[0], host, port, n, conn, bug);
		return;
	case -1:
		ERRX(EXIT_FAILURE, "fork (%s)", strerror(errno));
	default:
		error = sender(syncfds[1], host, port, n, conn, bug);
	again:
		switch (waitpid(pid, &status, WNOHANG)) {
		case -1:
			ERRX(EXIT_FAILURE, "wait (%s)", strerror(errno));
		case 0:
			if (error == 0)
				/*
				 * Receiver is still alive, but we know
				 * it will exit soon.
				 */
				goto again;

			if (kill(pid, SIGTERM) == -1)
				ERRX(EXIT_FAILURE, "kill (%s)",
				    strerror(errno));
			goto again;
		default:
			if (WIFSIGNALED(status)) {
				if (WTERMSIG(status) == SIGTERM)
					ERRX0(EXIT_FAILURE,
					    "receiver failed and was killed" \
					    "by sender");
				else
					ERRX(EXIT_FAILURE,
					    "receiver got signaled (%s)",
					    strsignal(WTERMSIG(status)));
			} else if (WIFEXITED(status)) {
				if (WEXITSTATUS(status) != 0)
					ERRX(EXIT_FAILURE,
					    "receiver exited with status %d",
					    WEXITSTATUS(status));
			} else {
				ERRX(EXIT_FAILURE,
				    "receiver exited with unexpected status %d",
				    status);
			}
			break;
		}
		return;
	}
}