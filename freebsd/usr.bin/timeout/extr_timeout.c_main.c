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
struct sigaction {int /*<<< orphan*/  sa_mask; int /*<<< orphan*/  sa_flags; int /*<<< orphan*/  sa_handler; } ;
struct procctl_reaper_status {scalar_t__ rs_children; int rk_sig; scalar_t__ rk_flags; } ;
struct procctl_reaper_kill {scalar_t__ rs_children; int rk_sig; scalar_t__ rk_flags; } ;
struct option {char* member_0; int* member_2; int member_3; int /*<<< orphan*/  member_1; } ;
typedef  int /*<<< orphan*/  signums ;
typedef  int /*<<< orphan*/  signals ;
typedef  int pid_t ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 scalar_t__ ENOENT ; 
 int EXIT_TIMEOUT ; 
 int /*<<< orphan*/  EX_OSERR ; 
 int /*<<< orphan*/  PROC_REAP_ACQUIRE ; 
 int /*<<< orphan*/  PROC_REAP_KILL ; 
 int /*<<< orphan*/  PROC_REAP_RELEASE ; 
 int /*<<< orphan*/  PROC_REAP_STATUS ; 
 int /*<<< orphan*/  P_PID ; 
 int /*<<< orphan*/  SA_RESTART ; 
 int SIGALRM ; 
 int SIGCHLD ; 
 int SIGHUP ; 
 int SIGINT ; 
 int SIGKILL ; 
 int SIGQUIT ; 
 int SIGSTOP ; 
 int SIGTERM ; 
 int /*<<< orphan*/  SIGTTIN ; 
 int /*<<< orphan*/  SIGTTOU ; 
 int /*<<< orphan*/  SIG_BLOCK ; 
 int /*<<< orphan*/  SIG_DFL ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int WEXITSTATUS (int) ; 
 scalar_t__ WIFSIGNALED (int) ; 
 int /*<<< orphan*/  WNOHANG ; 
 int WTERMSIG (int) ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 scalar_t__ errno ; 
 int execvp (char*,char**) ; 
 int fork () ; 
 int getopt_long (int,char**,char*,struct option const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  kill (int,int) ; 
 int /*<<< orphan*/  memset (struct sigaction*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  no_argument ; 
 char* optarg ; 
 scalar_t__ optind ; 
 double parse_duration (char*) ; 
 int parse_signal (char*) ; 
 int procctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct procctl_reaper_status*) ; 
 int /*<<< orphan*/  required_argument ; 
 int /*<<< orphan*/  set_interval (double) ; 
 scalar_t__ sig_alrm ; 
 scalar_t__ sig_chld ; 
 int /*<<< orphan*/  sig_handler ; 
 int sig_ign ; 
 int sig_term ; 
 int sigaction (int,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigaddset (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigsuspend (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usage () ; 
 int wait (int*) ; 
 int waitpid (int,int*,int /*<<< orphan*/ ) ; 

int
main(int argc, char **argv)
{
	int ch;
	unsigned long i;
	int foreground, preserve;
	int error, pstat, status;
	int killsig = SIGTERM;
	pid_t pid, cpid;
	double first_kill;
	double second_kill;
	bool timedout = false;
	bool do_second_kill = false;
	bool child_done = false;
	struct sigaction signals;
	struct procctl_reaper_status info;
	struct procctl_reaper_kill killemall;
	int signums[] = {
		-1,
		SIGTERM,
		SIGINT,
		SIGHUP,
		SIGCHLD,
		SIGALRM,
		SIGQUIT,
	};

	foreground = preserve = 0;
	second_kill = 0;

	const struct option longopts[] = {
		{ "preserve-status", no_argument,       &preserve,    1 },
		{ "foreground",      no_argument,       &foreground,  1 },
		{ "kill-after",      required_argument, NULL,        'k'},
		{ "signal",          required_argument, NULL,        's'},
		{ "help",            no_argument,       NULL,        'h'},
		{ NULL,              0,                 NULL,         0 }
	};

	while ((ch = getopt_long(argc, argv, "+k:s:h", longopts, NULL)) != -1) {
		switch (ch) {
			case 'k':
				do_second_kill = true;
				second_kill = parse_duration(optarg);
				break;
			case 's':
				killsig = parse_signal(optarg);
				break;
			case 0:
				break;
			case 'h':
			default:
				usage();
				break;
		}
	}

	argc -= optind;
	argv += optind;

	if (argc < 2)
		usage();

	first_kill = parse_duration(argv[0]);
	argc--;
	argv++;

	if (!foreground) {
		/* Acquire a reaper */
		if (procctl(P_PID, getpid(), PROC_REAP_ACQUIRE, NULL) == -1)
			err(EX_OSERR, "Fail to acquire the reaper");
	}

	memset(&signals, 0, sizeof(signals));
	sigemptyset(&signals.sa_mask);

	if (killsig != SIGKILL && killsig != SIGSTOP)
		signums[0] = killsig;

	for (i = 0; i < sizeof(signums) / sizeof(signums[0]); i ++)
		sigaddset(&signals.sa_mask, signums[i]);

	signals.sa_handler = sig_handler;
	signals.sa_flags = SA_RESTART;

	for (i = 0; i < sizeof(signums) / sizeof(signums[0]); i ++)
		if (signums[i] != -1 && signums[i] != 0 &&
		    sigaction(signums[i], &signals, NULL) == -1)
			err(EX_OSERR, "sigaction()");

	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);

	pid = fork();
	if (pid == -1)
		err(EX_OSERR, "fork()");
	else if (pid == 0) {
		/* child process */
		signal(SIGTTIN, SIG_DFL);
		signal(SIGTTOU, SIG_DFL);

		error = execvp(argv[0], argv);
		if (error == -1) {
			if (errno == ENOENT)
				err(127, "exec(%s)", argv[0]);
			else
				err(126, "exec(%s)", argv[0]);
		}
	}

	if (sigprocmask(SIG_BLOCK, &signals.sa_mask, NULL) == -1)
		err(EX_OSERR, "sigprocmask()");

	/* parent continues here */
	set_interval(first_kill);

	for (;;) {
		sigemptyset(&signals.sa_mask);
		sigsuspend(&signals.sa_mask);

		if (sig_chld) {
			sig_chld = 0;

			while ((cpid = waitpid(-1, &status, WNOHANG)) != 0) {
				if (cpid < 0) {
					if (errno == EINTR)
						continue;
					else
						break;
				} else if (cpid == pid) {
					pstat = status;
					child_done = true;
				}
			}
			if (child_done) {
				if (foreground) {
					break;
				} else {
					procctl(P_PID, getpid(),
					    PROC_REAP_STATUS, &info);
					if (info.rs_children == 0)
						break;
				}
			}
		} else if (sig_alrm) {
			sig_alrm = 0;

			timedout = true;
			if (!foreground) {
				killemall.rk_sig = killsig;
				killemall.rk_flags = 0;
				procctl(P_PID, getpid(), PROC_REAP_KILL,
				    &killemall);
			} else
				kill(pid, killsig);

			if (do_second_kill) {
				set_interval(second_kill);
				second_kill = 0;
				sig_ign = killsig;
				killsig = SIGKILL;
			} else
				break;

		} else if (sig_term) {
			if (!foreground) {
				killemall.rk_sig = sig_term;
				killemall.rk_flags = 0;
				procctl(P_PID, getpid(), PROC_REAP_KILL,
				    &killemall);
			} else
				kill(pid, sig_term);

			if (do_second_kill) {
				set_interval(second_kill);
				second_kill = 0;
				sig_ign = killsig;
				killsig = SIGKILL;
			} else
				break;
		}
	}

	while (!child_done && wait(&pstat) == -1) {
		if (errno != EINTR)
			err(EX_OSERR, "waitpid()");
	}

	if (!foreground)
		procctl(P_PID, getpid(), PROC_REAP_RELEASE, NULL);

	if (WEXITSTATUS(pstat))
		pstat = WEXITSTATUS(pstat);
	else if(WIFSIGNALED(pstat))
		pstat = 128 + WTERMSIG(pstat);

	if (timedout && !preserve)
		pstat = EXIT_TIMEOUT;

	return (pstat);
}