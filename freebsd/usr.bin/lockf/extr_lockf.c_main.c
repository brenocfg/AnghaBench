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
struct sigaction {scalar_t__ sa_flags; int /*<<< orphan*/  sa_mask; int /*<<< orphan*/  sa_handler; } ;
typedef  int pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  EX_OSERR ; 
 int EX_SOFTWARE ; 
 int /*<<< orphan*/  EX_TEMPFAIL ; 
 int /*<<< orphan*/  EX_USAGE ; 
 int O_CREAT ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  SIGALRM ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGQUIT ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int WEXITSTATUS (int) ; 
 scalar_t__ WIFEXITED (int) ; 
 int /*<<< orphan*/  _exit (int) ; 
 int acquire_lock (char*,int) ; 
 int /*<<< orphan*/  alarm (int) ; 
 int atexit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleanup ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  execvp (char*,char**) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int fork () ; 
 int getopt (int,char**,char*) ; 
 int keep ; 
 int /*<<< orphan*/  killed ; 
 int lockfd ; 
 char* lockname ; 
 char* optarg ; 
 int optind ; 
 int /*<<< orphan*/  sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strtol (char*,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timed_out ; 
 int /*<<< orphan*/  timeout ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  wait_for_lock (char*) ; 
 int waitpid (int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*,char*) ; 

int
main(int argc, char **argv)
{
	int ch, flags, silent, status, waitsec;
	pid_t child;

	silent = keep = 0;
	flags = O_CREAT;
	waitsec = -1;	/* Infinite. */
	while ((ch = getopt(argc, argv, "sknt:")) != -1) {
		switch (ch) {
		case 'k':
			keep = 1;
			break;
		case 'n':
			flags &= ~O_CREAT;
			break;
		case 's':
			silent = 1;
			break;
		case 't':
		{
			char *endptr;
			waitsec = strtol(optarg, &endptr, 0);
			if (*optarg == '\0' || *endptr != '\0' || waitsec < 0)
				errx(EX_USAGE,
				    "invalid timeout \"%s\"", optarg);
		}
			break;
		default:
			usage();
		}
	}
	if (argc - optind < 2)
		usage();
	lockname = argv[optind++];
	argc -= optind;
	argv += optind;
	if (waitsec > 0) {		/* Set up a timeout. */
		struct sigaction act;

		act.sa_handler = timeout;
		sigemptyset(&act.sa_mask);
		act.sa_flags = 0;	/* Note that we do not set SA_RESTART. */
		sigaction(SIGALRM, &act, NULL);
		alarm(waitsec);
	}
	/*
	 * If the "-k" option is not given, then we must not block when
	 * acquiring the lock.  If we did, then the lock holder would
	 * unlink the file upon releasing the lock, and we would acquire
	 * a lock on a file with no directory entry.  Then another
	 * process could come along and acquire the same lock.  To avoid
	 * this problem, we separate out the actions of waiting for the
	 * lock to be available and of actually acquiring the lock.
	 *
	 * That approach produces behavior that is technically correct;
	 * however, it causes some performance & ordering problems for
	 * locks that have a lot of contention.  First, it is unfair in
	 * the sense that a released lock isn't necessarily granted to
	 * the process that has been waiting the longest.  A waiter may
	 * be starved out indefinitely.  Second, it creates a thundering
	 * herd situation each time the lock is released.
	 *
	 * When the "-k" option is used, the unlink race no longer
	 * exists.  In that case we can block while acquiring the lock,
	 * avoiding the separate step of waiting for the lock.  This
	 * yields fairness and improved performance.
	 */
	lockfd = acquire_lock(lockname, flags | O_NONBLOCK);
	while (lockfd == -1 && !timed_out && waitsec != 0) {
		if (keep)
			lockfd = acquire_lock(lockname, flags);
		else {
			wait_for_lock(lockname);
			lockfd = acquire_lock(lockname, flags | O_NONBLOCK);
		}
	}
	if (waitsec > 0)
		alarm(0);
	if (lockfd == -1) {		/* We failed to acquire the lock. */
		if (silent)
			exit(EX_TEMPFAIL);
		errx(EX_TEMPFAIL, "%s: already locked", lockname);
	}
	/* At this point, we own the lock. */
	if (atexit(cleanup) == -1)
		err(EX_OSERR, "atexit failed");
	if ((child = fork()) == -1)
		err(EX_OSERR, "cannot fork");
	if (child == 0) {	/* The child process. */
		close(lockfd);
		execvp(argv[0], argv);
		warn("%s", argv[0]);
		_exit(1);
	}
	/* This is the parent process. */
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, killed);
	if (waitpid(child, &status, 0) == -1)
		err(EX_OSERR, "waitpid failed");
	return (WIFEXITED(status) ? WEXITSTATUS(status) : EX_SOFTWARE);
}