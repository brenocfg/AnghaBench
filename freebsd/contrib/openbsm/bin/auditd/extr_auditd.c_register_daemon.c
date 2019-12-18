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
struct sigaction {int /*<<< orphan*/  sa_mask; scalar_t__ sa_flags; int /*<<< orphan*/  sa_handler; } ;
typedef  int pid_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  AUDITD_PIDFILE ; 
 int LOCK_EX ; 
 int LOCK_NB ; 
 int /*<<< orphan*/  SIGALRM ; 
 int /*<<< orphan*/  SIGCHLD ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  audit_warn_ebusy () ; 
 int /*<<< orphan*/  audit_warn_tmpfile () ; 
 int /*<<< orphan*/  auditd_log_err (char*) ; 
 int /*<<< orphan*/  auditd_relay_signal ; 
 int /*<<< orphan*/  fail_exit () ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 int fileno (int /*<<< orphan*/ *) ; 
 scalar_t__ flock (int,int) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ fprintf (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  ftruncate (int,int /*<<< orphan*/ ) ; 
 int getpid () ; 
 scalar_t__ sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
register_daemon(void)
{
	struct sigaction action;
	FILE * pidfile;
	int fd;
	pid_t pid;

	/* Set up the signal hander. */
	action.sa_handler = auditd_relay_signal;
	/*
	 * sa_flags must not include SA_RESTART, so that read(2) will be
	 * interruptible in auditd_wait_for_events
	 */
	action.sa_flags = 0;
	sigemptyset(&action.sa_mask);
	if (sigaction(SIGTERM, &action, NULL) != 0) {
		auditd_log_err(
		    "Could not set signal handler for SIGTERM");
		fail_exit();
	}
	if (sigaction(SIGCHLD, &action, NULL) != 0) {
		auditd_log_err(
		    "Could not set signal handler for SIGCHLD");
		fail_exit();
	}
	if (sigaction(SIGHUP, &action, NULL) != 0) {
		auditd_log_err(
		    "Could not set signal handler for SIGHUP");
		fail_exit();
	}
	if (sigaction(SIGALRM, &action, NULL) != 0) {
		auditd_log_err(
		    "Could not set signal handler for SIGALRM");
		fail_exit();
	}

	if ((pidfile = fopen(AUDITD_PIDFILE, "a")) == NULL) {
		auditd_log_err("Could not open PID file");
		audit_warn_tmpfile();
		return (-1);
	}

	/* Attempt to lock the pid file; if a lock is present, exit. */
	fd = fileno(pidfile);
	if (flock(fd, LOCK_EX | LOCK_NB) < 0) {
		auditd_log_err(
		    "PID file is locked (is another auditd running?).");
		audit_warn_ebusy();
		return (-1);
	}

	pid = getpid();
	ftruncate(fd, 0);
	if (fprintf(pidfile, "%u\n", pid) < 0) {
		/* Should not start the daemon. */
		fail_exit();
	}

	fflush(pidfile);
	return (0);
}