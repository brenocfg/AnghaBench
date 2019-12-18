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
typedef  int /*<<< orphan*/  sigfunc_t ;
typedef  int /*<<< orphan*/  ARGV_T ;

/* Variables and functions */
 scalar_t__ DaemonPid ; 
 scalar_t__ EX_OK ; 
 int /*<<< orphan*/  EX_OSERR ; 
 int /*<<< orphan*/  EX_OSFILE ; 
 scalar_t__ ExternalEnviron ; 
 int /*<<< orphan*/  LOG_ALERT ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int LogLevel ; 
 int /*<<< orphan*/  NOQID ; 
 scalar_t__ PendingSignal ; 
 scalar_t__ RealUid ; 
 char* RestartRequest ; 
 scalar_t__ RunAsUid ; 
 int /*<<< orphan*/  SIGALRM ; 
 int /*<<< orphan*/  SIGCHLD ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SIGUSR1 ; 
 int /*<<< orphan*/  SM_NOOP_SIGNAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ STDERR_FILENO ; 
 char** SaveArgv ; 
 scalar_t__ UseMSP ; 
 int /*<<< orphan*/  cleanup_shm (int) ; 
 int /*<<< orphan*/  close_sendmail_pid () ; 
 int /*<<< orphan*/  closecontrolsocket (int) ; 
 scalar_t__ drop_privileges (int) ; 
 int errno ; 
 int /*<<< orphan*/  execve (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  finis (int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ getpid () ; 
 int /*<<< orphan*/  sm_allsignals (int) ; 
 int /*<<< orphan*/  sm_clear_events () ; 
 int /*<<< orphan*/  sm_close_on_exec (scalar_t__,int) ; 
 char* sm_errstring (int) ; 
 int /*<<< orphan*/  sm_signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sm_syslog (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 

void
restart_daemon()
{
	bool drop;
	int save_errno;
	char *reason;
	sigfunc_t ignore, oalrm, ousr1;
	extern int DtableSize;

	/* clear the events to turn off SIGALRMs */
	sm_clear_events();
	sm_allsignals(true);

	reason = RestartRequest;
	RestartRequest = NULL;
	PendingSignal = 0;

	if (SaveArgv[0][0] != '/')
	{
		if (LogLevel > 3)
			sm_syslog(LOG_INFO, NOQID,
				  "could not restart: need full path");
		finis(false, true, EX_OSFILE);
		/* NOTREACHED */
	}
	if (LogLevel > 3)
		sm_syslog(LOG_INFO, NOQID, "restarting %s due to %s",
			  SaveArgv[0],
			  reason == NULL ? "implicit call" : reason);

	closecontrolsocket(true);
#if SM_CONF_SHM
	cleanup_shm(DaemonPid == getpid());
#endif /* SM_CONF_SHM */

	/* close locked pid file */
	close_sendmail_pid();

	/*
	**  Want to drop to the user who started the process in all cases
	**  *but* when running as "smmsp" for the clientmqueue queue run
	**  daemon.  In that case, UseMSP will be true, RunAsUid should not
	**  be root, and RealUid should be either 0 or RunAsUid.
	*/

	drop = !(UseMSP && RunAsUid != 0 &&
		 (RealUid == 0 || RealUid == RunAsUid));

	if (drop_privileges(drop) != EX_OK)
	{
		if (LogLevel > 0)
			sm_syslog(LOG_ALERT, NOQID,
				  "could not drop privileges: %s",
				  sm_errstring(errno));
		finis(false, true, EX_OSERR);
		/* NOTREACHED */
	}

	sm_close_on_exec(STDERR_FILENO + 1, DtableSize);

	/*
	**  Need to allow signals before execve() to make them "harmless".
	**  However, the default action can be "terminate", so it isn't
	**  really harmless.  Setting signals to IGN will cause them to be
	**  ignored in the new process to, so that isn't a good alternative.
	*/

	SM_NOOP_SIGNAL(SIGALRM, oalrm);
	SM_NOOP_SIGNAL(SIGCHLD, ignore);
	SM_NOOP_SIGNAL(SIGHUP, ignore);
	SM_NOOP_SIGNAL(SIGINT, ignore);
	SM_NOOP_SIGNAL(SIGPIPE, ignore);
	SM_NOOP_SIGNAL(SIGTERM, ignore);
#ifdef SIGUSR1
	SM_NOOP_SIGNAL(SIGUSR1, ousr1);
#endif /* SIGUSR1 */

	/* Turn back on signals */
	sm_allsignals(false);

	(void) execve(SaveArgv[0], (ARGV_T) SaveArgv, (ARGV_T) ExternalEnviron);
	save_errno = errno;

	/* block signals again and restore needed signals */
	sm_allsignals(true);

	/* For finis() events */
	(void) sm_signal(SIGALRM, oalrm);

#ifdef SIGUSR1
	/* For debugging finis() */
	(void) sm_signal(SIGUSR1, ousr1);
#endif /* SIGUSR1 */

	errno = save_errno;
	if (LogLevel > 0)
		sm_syslog(LOG_ALERT, NOQID, "could not exec %s: %s",
			  SaveArgv[0], sm_errstring(errno));
	finis(false, true, EX_OSFILE);
	/* NOTREACHED */
}