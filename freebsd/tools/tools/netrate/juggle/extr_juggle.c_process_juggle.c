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
struct timespec {int dummy; } ;
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_REALTIME ; 
 int NUMCYCLES ; 
 int /*<<< orphan*/  SIGTERM ; 
 scalar_t__ clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int errno ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ fork () ; 
 scalar_t__ getpid () ; 
 int /*<<< orphan*/  kill (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ message_recv (int) ; 
 scalar_t__ message_send (int) ; 
 int /*<<< orphan*/  timespecsub (struct timespec*,struct timespec*,struct timespec*) ; 
 scalar_t__ waitpid (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct timespec
process_juggle(int fd1, int fd2, int pipeline)
{
	struct timespec tstart, tfinish;
	pid_t pid, ppid, wpid;
	int error, i, j;

	ppid = getpid();

	pid = fork();
	if (pid < 0)
		err(-1, "process_juggle: fork");

	if (pid == 0) {
		if (message_send(fd2) < 0) {
			error = errno;
			kill(ppid, SIGTERM);
			errno = error;
			err(-1, "process_juggle: child: message_send");
		}

		for (i = 0; i < NUMCYCLES; i++) {
			for (j = 0; j < pipeline; j++) {
				if (message_send(fd2) < 0)
					err(-1, "message_send fd2");

				if (message_recv(fd2) < 0)
					err(-1, "message_recv fd2");
			}
		}

		exit(0);
	} else {
		if (message_recv(fd1) < 0) {
			error = errno;
			kill(pid, SIGTERM);
			errno = error;
			err(-1, "process_juggle: parent: message_recv");
		}

		if (clock_gettime(CLOCK_REALTIME, &tstart) < 0)
			err(-1, "process_juggle: clock_gettime");

		for (i = 0; i < NUMCYCLES; i++) {
			for (j = 0; j < pipeline; j++) {
				if (message_send(fd1) < 0) {
					error = errno;
					kill(pid, SIGTERM);
					errno = error;
					err(-1, "message_send fd1");
				}
			}

			for (j = 0; j < pipeline; j++) {
				if (message_recv(fd1) < 0) {
					error = errno;
					kill(pid, SIGTERM);
					errno = error;
					err(-1, "message_recv fd1");
				}
			}
		}

		if (clock_gettime(CLOCK_REALTIME, &tfinish) < 0)
			err(-1, "process_juggle: clock_gettime");
	}

	wpid = waitpid(pid, NULL, 0);
	if (wpid < 0)
		err(-1, "process_juggle: waitpid");
	if (wpid != pid)
		errx(-1, "process_juggle: waitpid: pid != wpid");

	timespecsub(&tfinish, &tstart, &tfinish);

	return (tfinish);
}