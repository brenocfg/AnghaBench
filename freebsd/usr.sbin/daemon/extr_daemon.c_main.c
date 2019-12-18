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
struct sigaction {int outfd; int dosyslog; int logpri; int noclose; int /*<<< orphan*/  sa_mask; int /*<<< orphan*/  sa_handler; } ;
struct pidfh {int dummy; } ;
struct log_params {int outfd; int dosyslog; int logpri; int noclose; int /*<<< orphan*/  sa_mask; int /*<<< orphan*/  sa_handler; } ;
typedef  int /*<<< orphan*/  sigset_t ;
typedef  int /*<<< orphan*/  logpar ;
typedef  int /*<<< orphan*/  act_term ;
typedef  int /*<<< orphan*/  act_chld ;

/* Variables and functions */
 int LOG_DAEMON ; 
 int LOG_NDELAY ; 
 int LOG_NOTICE ; 
 int LOG_PID ; 
 int /*<<< orphan*/  MADV_PROTECT ; 
 int O_APPEND ; 
 int O_CLOEXEC ; 
 int O_CREAT ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  SIGCHLD ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SIG_BLOCK ; 
 int /*<<< orphan*/  SIG_SETMASK ; 
 int /*<<< orphan*/  SIG_UNBLOCK ; 
 int STDERR_FILENO ; 
 int STDOUT_FILENO ; 
 scalar_t__ child_gone ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  closelog () ; 
 int daemon (int,int) ; 
 int /*<<< orphan*/  daemon_sleep (int,int /*<<< orphan*/ ) ; 
 int dup2 (int,int) ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  execvp (char*,char**) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  facilitynames ; 
 int fork () ; 
 int get_log_mapping (char*,int /*<<< orphan*/ ) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  handle_chld ; 
 int /*<<< orphan*/  handle_term ; 
 int /*<<< orphan*/  listen_child (int,struct sigaction*) ; 
 int /*<<< orphan*/  madvise (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct sigaction*,int /*<<< orphan*/ ,int) ; 
 int open (char const*,int,int) ; 
 int /*<<< orphan*/  open_pid_files (char const*,char const*,struct pidfh**,struct pidfh**) ; 
 int /*<<< orphan*/  openlog (char const*,int,int) ; 
 char* optarg ; 
 scalar_t__ optind ; 
 int pid ; 
 int /*<<< orphan*/  pidfile_remove (struct pidfh*) ; 
 int /*<<< orphan*/  pidfile_write (struct pidfh*) ; 
 scalar_t__ pipe (int*) ; 
 int /*<<< orphan*/  prioritynames ; 
 int /*<<< orphan*/  restrict_process (char const*) ; 
 int /*<<< orphan*/  setproctitle (char*,char const*,int) ; 
 int sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigaddset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 scalar_t__ sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigsuspend (int /*<<< orphan*/ *) ; 
 int strtol (char*,char**,int) ; 
 scalar_t__ terminate ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  warn (char*) ; 

int
main(int argc, char *argv[])
{
	const char *pidfile, *ppidfile, *title, *user, *outfn, *logtag;
	int ch, nochdir, noclose, restart, dosyslog, child_eof;
	sigset_t mask_susp, mask_orig, mask_read, mask_term;
	struct log_params logpar;
	int pfd[2] = { -1, -1 }, outfd = -1;
	int stdmask, logpri, logfac;
	struct pidfh *ppfh, *pfh;
	char *p;

	memset(&logpar, 0, sizeof(logpar));
	stdmask = STDOUT_FILENO | STDERR_FILENO;
	ppidfile = pidfile = user = NULL;
	nochdir = noclose = 1;
	logpri = LOG_NOTICE;
	logfac = LOG_DAEMON;
	logtag = "daemon";
	restart = 0;
	dosyslog = 0;
	outfn = NULL;
	title = NULL;
	while ((ch = getopt(argc, argv, "cfSp:P:ru:o:s:l:t:l:m:R:T:")) != -1) {
		switch (ch) {
		case 'c':
			nochdir = 0;
			break;
		case 'f':
			noclose = 0;
			break;
		case 'l':
			logfac = get_log_mapping(optarg, facilitynames);
			if (logfac == -1)
				errx(5, "unrecognized syslog facility");
			dosyslog = 1;
			break;
		case 'm':
			stdmask = strtol(optarg, &p, 10);
			if (p == optarg || stdmask < 0 || stdmask > 3)
				errx(6, "unrecognized listening mask");
			break;
		case 'o':
			outfn = optarg;
			break;
		case 'p':
			pidfile = optarg;
			break;
		case 'P':
			ppidfile = optarg;
			break;
		case 'r':
			restart = 1;
			break;
		case 'R':
			restart = strtol(optarg, &p, 0);
			if (p == optarg || restart < 1)
				errx(6, "invalid restart delay");
			break;
		case 's':
			logpri = get_log_mapping(optarg, prioritynames);
			if (logpri == -1)
				errx(4, "unrecognized syslog priority");
			dosyslog = 1;
			break;
		case 'S':
			dosyslog = 1;
			break;
		case 't':
			title = optarg;
			break;
		case 'T':
			logtag = optarg;
			dosyslog = 1;
			break;
		case 'u':
			user = optarg;
			break;
		default:
			usage();
		}
	}
	argc -= optind;
	argv += optind;

	if (argc == 0)
		usage();

	if (!title)
		title = argv[0];

	if (outfn) {
		outfd = open(outfn, O_CREAT | O_WRONLY | O_APPEND | O_CLOEXEC, 0600);
		if (outfd == -1)
			err(7, "open");
	}
	
	if (dosyslog)
		openlog(logtag, LOG_PID | LOG_NDELAY, logfac);

	ppfh = pfh = NULL;
	/*
	 * Try to open the pidfile before calling daemon(3),
	 * to be able to report the error intelligently
	 */
	open_pid_files(pidfile, ppidfile, &pfh, &ppfh);
	if (daemon(nochdir, noclose) == -1) {
		warn("daemon");
		goto exit;
	}
	/* Write out parent pidfile if needed. */
	pidfile_write(ppfh);
	/*
	 * If the pidfile or restart option is specified the daemon
	 * executes the command in a forked process and wait on child
	 * exit to remove the pidfile or restart the command. Normally
	 * we don't want the monitoring daemon to be terminated
	 * leaving the running process and the stale pidfile, so we
	 * catch SIGTERM and forward it to the children expecting to
	 * get SIGCHLD eventually. We also must fork() to obtain a
	 * readable pipe with the child for writing to a log file
	 * and syslog.
	 */
	pid = -1;
	if (pidfile || ppidfile || restart || outfd != -1 || dosyslog) {
		struct sigaction act_term, act_chld;

		/* Avoid PID racing with SIGCHLD and SIGTERM. */
		memset(&act_term, 0, sizeof(act_term));
		act_term.sa_handler = handle_term;
		sigemptyset(&act_term.sa_mask);
		sigaddset(&act_term.sa_mask, SIGCHLD);

		memset(&act_chld, 0, sizeof(act_chld));
		act_chld.sa_handler = handle_chld;
		sigemptyset(&act_chld.sa_mask);
		sigaddset(&act_chld.sa_mask, SIGTERM);

		/* Block these when avoiding racing before sigsuspend(). */
		sigemptyset(&mask_susp);
		sigaddset(&mask_susp, SIGTERM);
		sigaddset(&mask_susp, SIGCHLD);
		/* Block SIGTERM when we lack a valid child PID. */
		sigemptyset(&mask_term);
		sigaddset(&mask_term, SIGTERM);
		/*
		 * When reading, we wish to avoid SIGCHLD. SIGTERM
		 * has to be caught, otherwise we'll be stuck until
		 * the read() returns - if it returns.
		 */
		sigemptyset(&mask_read);
		sigaddset(&mask_read, SIGCHLD);
		/* Block SIGTERM to avoid racing until we have forked. */
		if (sigprocmask(SIG_BLOCK, &mask_term, &mask_orig)) {
			warn("sigprocmask");
			goto exit;
		}
		if (sigaction(SIGTERM, &act_term, NULL) == -1) {
			warn("sigaction");
			goto exit;
		}
		if (sigaction(SIGCHLD, &act_chld, NULL) == -1) {
			warn("sigaction");
			goto exit;
		}
		/*
		 * Try to protect against pageout kill. Ignore the
		 * error, madvise(2) will fail only if a process does
		 * not have superuser privileges.
		 */
		(void)madvise(NULL, 0, MADV_PROTECT);
		logpar.outfd = outfd;
		logpar.dosyslog = dosyslog;
		logpar.logpri = logpri;
		logpar.noclose = noclose;
restart:
		if (pipe(pfd))
			err(1, "pipe");
		/*
		 * Spawn a child to exec the command.
		 */
		child_gone = 0;
		pid = fork();
		if (pid == -1) {
			warn("fork");
			goto exit;
		} else if (pid > 0) {
			/*
			 * Unblock SIGTERM after we know we have a valid
			 * child PID to signal.
			 */
			if (sigprocmask(SIG_UNBLOCK, &mask_term, NULL)) {
				warn("sigprocmask");
				goto exit;
			}
			close(pfd[1]);
			pfd[1] = -1;
		}
	}
	if (pid <= 0) {
		/* Now that we are the child, write out the pid. */
		pidfile_write(pfh);

		if (user != NULL)
			restrict_process(user);
		/*
		 * When forking, the child gets the original sigmask,
		 * and dup'd pipes.
		 */
		if (pid == 0) {
			close(pfd[0]);
			if (sigprocmask(SIG_SETMASK, &mask_orig, NULL))
				err(1, "sigprogmask");
			if (stdmask & STDERR_FILENO) {
				if (dup2(pfd[1], STDERR_FILENO) == -1)
					err(1, "dup2");
			}
			if (stdmask & STDOUT_FILENO) {
				if (dup2(pfd[1], STDOUT_FILENO) == -1)
					err(1, "dup2");
			}
			if (pfd[1] != STDERR_FILENO &&
			    pfd[1] != STDOUT_FILENO)
				close(pfd[1]);
		}
		execvp(argv[0], argv);
		/*
		 * execvp() failed -- report the error. The child is
		 * now running, so the exit status doesn't matter.
		 */
		err(1, "%s", argv[0]);
	}
	setproctitle("%s[%d]", title, (int)pid);
	/*
	 * As we have closed the write end of pipe for parent process,
	 * we might detect the child's exit by reading EOF. The child
	 * might have closed its stdout and stderr, so we must wait for
	 * the SIGCHLD to ensure that the process is actually gone.
	 */
	child_eof = 0;
	for (;;) {
		/*
		 * We block SIGCHLD when listening, but SIGTERM we accept
		 * so the read() won't block if we wish to depart.
		 *
		 * Upon receiving SIGTERM, we have several options after
		 * sending the SIGTERM to our child:
		 * - read until EOF
		 * - read until EOF but only for a while
		 * - bail immediately
		 *
		 * We go for the third, as otherwise we have no guarantee
		 * that we won't block indefinitely if the child refuses
		 * to depart. To handle the second option, a different
		 * approach would be needed (procctl()?)
		 */
		if (child_gone && child_eof) {
			break;
		} else if (terminate) {
			goto exit;
		} else if (!child_eof) {
			if (sigprocmask(SIG_BLOCK, &mask_read, NULL)) {
				warn("sigprocmask");
				goto exit;
			}
			child_eof = !listen_child(pfd[0], &logpar);
			if (sigprocmask(SIG_UNBLOCK, &mask_read, NULL)) {
				warn("sigprocmask");
				goto exit;
			}
		} else {
			if (sigprocmask(SIG_BLOCK, &mask_susp, NULL)) {
				warn("sigprocmask");
	 			goto exit;
			}
			while (!terminate && !child_gone)
				sigsuspend(&mask_orig);
			if (sigprocmask(SIG_UNBLOCK, &mask_susp, NULL)) {
				warn("sigprocmask");
				goto exit;
			}
		}
	}
	if (restart && !terminate)
		daemon_sleep(restart, 0);
	if (sigprocmask(SIG_BLOCK, &mask_term, NULL)) {
		warn("sigprocmask");
		goto exit;
	}
	if (restart && !terminate) {
		close(pfd[0]);
		pfd[0] = -1;
		goto restart;
	}
exit:
	close(outfd);
	close(pfd[0]);
	close(pfd[1]);
	if (dosyslog)
		closelog();
	pidfile_remove(pfh);
	pidfile_remove(ppfh);
	exit(1); /* If daemon(3) succeeded exit status does not matter. */
}