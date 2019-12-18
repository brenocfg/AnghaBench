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
union semun {int val; struct semid_ds* buf; } ;
struct sigaction {scalar_t__ sa_flags; int /*<<< orphan*/  sa_mask; int /*<<< orphan*/  sa_handler; } ;
struct TYPE_2__ {int mode; } ;
struct semid_ds {TYPE_1__ sem_perm; } ;
typedef  int /*<<< orphan*/  sigset_t ;
typedef  int /*<<< orphan*/  s_ds ;

/* Variables and functions */
 scalar_t__ EEXIST ; 
 int /*<<< orphan*/  GETNCNT ; 
 int IPC_CREAT ; 
 int IPC_EXCL ; 
 int /*<<< orphan*/  IPC_SET ; 
 int /*<<< orphan*/  IPC_STAT ; 
 int /*<<< orphan*/  SETVAL ; 
 int /*<<< orphan*/  SIGCHLD ; 
 int /*<<< orphan*/  SIGSYS ; 
 int atexit (int /*<<< orphan*/ ) ; 
 int child_count ; 
 int /*<<< orphan*/  child_pid ; 
 int /*<<< orphan*/  cleanup ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  fork () ; 
 int /*<<< orphan*/  ftok (char*,int) ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  memset (struct semid_ds*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  print_semid_ds (struct semid_ds*,int) ; 
 int semctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int semget (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  semkey ; 
 int sender_semid ; 
 int sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigchld_handler ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 scalar_t__ signal_was_sigchld ; 
 int /*<<< orphan*/  sigsuspend (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigsys_handler ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  waiter () ; 

int
main(int argc, char *argv[])
{
	struct sigaction sa;
	union semun sun;
	struct semid_ds s_ds;
	sigset_t sigmask;
	int i;

	if (argc != 2)
		usage();

	/*
	 * Install a SIGSYS handler so that we can exit gracefully if
	 * System V Semaphore support isn't in the kernel.
	 */
	sa.sa_handler = sigsys_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGSYS, &sa, NULL) == -1)
		err(1, "sigaction SIGSYS");

	/*
	 * Install and SIGCHLD handler to deal with all possible exit
	 * conditions of the receiver.
	 */
	sa.sa_handler = sigchld_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGCHLD, &sa, NULL) == -1)
		err(1, "sigaction SIGCHLD");

	semkey = ftok(argv[1], 4160);

	/*
	 * Initialize child_pid to ourselves to that the cleanup function
	 * works before we create the receiver.
	 */
	child_pid = getpid();

	/*
	 * Make sure that when the sender exits, the message queue is
	 * removed.
	 */
	if (atexit(cleanup) == -1)
		err(1, "atexit");

	if ((sender_semid = semget(semkey, 1, IPC_CREAT | 0640)) == -1)
		err(1, "semget");

	
	sun.buf = &s_ds;
	if (semctl(sender_semid, 0, IPC_STAT, sun) == -1)
		err(1, "semctl IPC_STAT");

	print_semid_ds(&s_ds, 0640);

	s_ds.sem_perm.mode = (s_ds.sem_perm.mode & ~0777) | 0600;

	sun.buf = &s_ds;
	if (semctl(sender_semid, 0, IPC_SET, sun) == -1)
		err(1, "semctl IPC_SET");

	memset(&s_ds, 0, sizeof(s_ds));

	sun.buf = &s_ds;
	if (semctl(sender_semid, 0, IPC_STAT, sun) == -1)
		err(1, "semctl IPC_STAT");

	if ((s_ds.sem_perm.mode & 0777) != 0600)
		err(1, "IPC_SET of mode didn't hold");

	print_semid_ds(&s_ds, 0600);

	errno = 0;
	if (semget(semkey, 1, IPC_CREAT | IPC_EXCL | 0600) != -1 ||
	    errno != EEXIST)
		err(1, "semget IPC_EXCL 1 did not fail with [EEXIST]");
	errno = 0;
	if (semget(semkey, 2, IPC_CREAT | IPC_EXCL | 0600) != -1 ||
	    errno != EEXIST)
		err(1, "semget IPC_EXCL 2 did not fail with [EEXIST]");

	for (child_count = 0; child_count < 5; child_count++) {
		switch ((child_pid = fork())) {
		case -1:
			err(1, "fork");
			/* NOTREACHED */

		case 0:
			waiter();
			break;

		default:
			break;
		}
	}

	/*
	 * Wait for all of the waiters to be attempting to acquire the
	 * semaphore.
	 */
	for (;;) {
		i = semctl(sender_semid, 0, GETNCNT);
		if (i == -1)
			err(1, "semctl GETNCNT");
		if (i == 5)
			break;
	}

	/*
	 * Now set the thundering herd in motion by initializing the
	 * semaphore to the value 1.
	 */
	sun.val = 1;
	if (semctl(sender_semid, 0, SETVAL, sun) == -1)
		err(1, "sender: semctl SETVAL to 1");

	/*
	 * Suspend forever; when we get SIGCHLD, the handler will exit.
	 */
	sigemptyset(&sigmask);
	for (;;) {
		(void) sigsuspend(&sigmask);
		if (signal_was_sigchld)
			signal_was_sigchld = 0;
		else
			break;
	}

	/*
	 * ...and any other signal is an unexpected error.
	 */
	errx(1, "sender: received unexpected signal");
}