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
struct tm {int tm_mon; int tm_mday; int tm_hour; int tm_min; int tm_sec; } ;
typedef  int /*<<< orphan*/  TIME_T ;
typedef  int PID_T ;

/* Variables and functions */
 scalar_t__ DebugFlags ; 
 int /*<<< orphan*/  F_SETFD ; 
 int /*<<< orphan*/  LOG_CRON ; 
 int /*<<< orphan*/  LOG_FILE ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  LOG_PID ; 
 scalar_t__ LogFD ; 
 scalar_t__ MAX_TEMPSTR ; 
 scalar_t__ OK ; 
 int O_APPEND ; 
 int O_CREAT ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  ProgramName ; 
 scalar_t__ STDERR ; 
 int TRUE ; 
 int /*<<< orphan*/  fcntl (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,int,char*,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 struct tm* localtime (int /*<<< orphan*/ *) ; 
 char* malloc (scalar_t__) ; 
 scalar_t__ open (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  openlog (int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,int,int,int,int,int,int,char*,char const*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,char*,char*,char const*) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*) ; 
 scalar_t__ write (scalar_t__,char*,scalar_t__) ; 

void
log_it(char *username, int xpid, char *event, const char *detail)
{
#if defined(LOG_FILE) || DEBUGGING
	PID_T			pid = xpid;
#endif
#if defined(LOG_FILE)
	char			*msg;
	TIME_T			now = time((TIME_T) 0);
	register struct tm	*t = localtime(&now);
#endif /*LOG_FILE*/

#if defined(SYSLOG)
	static int		syslog_open = 0;
#endif

#if defined(LOG_FILE)
	/* we assume that MAX_TEMPSTR will hold the date, time, &punctuation.
	 */
	msg = malloc(strlen(username)
		     + strlen(event)
		     + strlen(detail)
		     + MAX_TEMPSTR);

	if (msg == NULL)
		warnx("failed to allocate memory for log message");
	else {
		if (LogFD < OK) {
			LogFD = open(LOG_FILE, O_WRONLY|O_APPEND|O_CREAT, 0600);
			if (LogFD < OK) {
				warn("can't open log file %s", LOG_FILE);
			} else {
				(void) fcntl(LogFD, F_SETFD, 1);
			}
		}

		/* we have to sprintf() it because fprintf() doesn't always
		 * write everything out in one chunk and this has to be
		 * atomically appended to the log file.
		 */
		sprintf(msg, "%s (%02d/%02d-%02d:%02d:%02d-%d) %s (%s)\n",
			username,
			t->tm_mon+1, t->tm_mday, t->tm_hour, t->tm_min,
			t->tm_sec, pid, event, detail);

		/* we have to run strlen() because sprintf() returns (char*)
		 * on old BSD.
		 */
		if (LogFD < OK || write(LogFD, msg, strlen(msg)) < OK) {
			if (LogFD >= OK)
				warn("%s", LOG_FILE);
			warnx("can't write to log file");
			write(STDERR, msg, strlen(msg));
		}

		free(msg);
	}
#endif /*LOG_FILE*/

#if defined(SYSLOG)
	if (!syslog_open) {
		/* we don't use LOG_PID since the pid passed to us by
		 * our client may not be our own.  therefore we want to
		 * print the pid ourselves.
		 */
# ifdef LOG_DAEMON
		openlog(ProgramName, LOG_PID, LOG_CRON);
# else
		openlog(ProgramName, LOG_PID);
# endif
		syslog_open = TRUE;		/* assume openlog success */
	}

	syslog(LOG_INFO, "(%s) %s (%s)\n", username, event, detail);

#endif /*SYSLOG*/

#if DEBUGGING
	if (DebugFlags) {
		fprintf(stderr, "log_it: (%s %d) %s (%s)\n",
			username, pid, event, detail);
	}
#endif
}