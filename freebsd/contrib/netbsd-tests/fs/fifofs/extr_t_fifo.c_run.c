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
struct timespec {int member_1; int /*<<< orphan*/  member_0; } ;
struct sigaction {int /*<<< orphan*/  sa_mask; int /*<<< orphan*/  sa_handler; } ;
typedef  int ssize_t ;
typedef  int pid_t ;
typedef  int /*<<< orphan*/  action ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  FIFO_FILE_PATH ; 
 int MSG_SIZE ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  O_WRONLY ; 
 int /*<<< orphan*/  SIGCHLD ; 
 int S_IRUSR ; 
 int S_IWUSR ; 
 int /*<<< orphan*/  child_writer () ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int fork () ; 
 int /*<<< orphan*/  memset (struct sigaction*,int /*<<< orphan*/ ,int) ; 
 int mkfifo (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nanosleep (struct timespec const*,int /*<<< orphan*/ *) ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int read (int,char*,size_t) ; 
 int sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigchild_handler ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ ) ; 
 scalar_t__ verbose ; 
 int waitpid (int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*) ; 

__attribute__((used)) static int
run(void)
{
	pid_t pid;
	ssize_t rv;
	int fd, status;
	size_t buf_size = MSG_SIZE;
	char buf[MSG_SIZE];
	struct sigaction action;
	static const struct timespec ts = { 0, 500000000 };

	/* Catch sigchild Signal */
	memset(&action, 0, sizeof(action));
	action.sa_handler = sigchild_handler;
	sigemptyset(&action.sa_mask);

	if (sigaction(SIGCHLD, &action, NULL) == -1)
		err(1, "sigaction");

	(void)unlink(FIFO_FILE_PATH);
	/* First create a fifo */
	if (mkfifo(FIFO_FILE_PATH, S_IRUSR | S_IWUSR) == -1)
		err(1, "mkfifo");

	switch ((pid = fork())) {
	case -1:
		err(1, "fork");
	case 0:
		/* Open the file in write mode so that subsequent read 
		 * from parent side does not block the parent..
		 */
		if ((fd = open(FIFO_FILE_PATH, O_WRONLY, 0)) == -1)
			err(1, "failed to open fifo");

		/* In child */
		child_writer();
		return 0;

	default:
		break;
	}

	if (verbose) {
		printf("Child pid is %d\n", pid );
		fflush(stdout);
	}

	/* In parent */
	for (;;) {
		if ((fd = open(FIFO_FILE_PATH, O_RDONLY, 0)) == -1) {
			if (errno == EINTR)
				continue;
			else
				err(1, "Failed to open the fifo in read mode");
		}
		/* Read mode is opened */
		break;

	}

	nanosleep(&ts, NULL);
	if (verbose) {
		printf("Was sleeping...\n");
		fflush(stdout);
	}

	for (;;) {
		rv = read(fd, buf, buf_size);

		if (rv == -1) {
			warn("Failed to read");
			if (errno == EINTR) {
				if (verbose) {
					printf("Parent interrupted, "
					    "continuing...\n");
					fflush(stdout);
				}
				continue;
			}

			break;
		}

		if (rv == 0) {
			if (verbose) {
				printf("Writers have closed, looks like we "
				    "are done\n");
				fflush(stdout);
			}
			break;
		}

		if (verbose) {
			printf("Received %zd bytes message '%s'\n", rv, buf);
			fflush(stdout);
		}
	}

	close(fd);

	if (verbose) {
		printf("We are done.. now reap the child");
		fflush(stdout);
	}

	// Read the child...
	while (waitpid(pid, &status, 0) == -1)
		if (errno != EINTR) {
			warn("Failed to reap the child");
			return 1;
		}

	if (verbose) {
		printf("We are done completely\n");
		fflush(stdout);
	}
	return 0;
}