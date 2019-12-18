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
typedef  scalar_t__ u_int32 ;

/* Variables and functions */
 char DIR_SEP ; 
 scalar_t__ INIT_NTP_SYSLOGMASK ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int LOG_NDELAY ; 
 int /*<<< orphan*/  LOG_NTP ; 
 int LOG_PID ; 
 int /*<<< orphan*/  LOG_UPTO (int /*<<< orphan*/ ) ; 
 int TRUE ; 
 scalar_t__ debug ; 
 char* estrdup (char const*) ; 
 scalar_t__ ntp_syslogmask ; 
 int /*<<< orphan*/  openlog (char const*,int,...) ; 
 char const* progname ; 
 int /*<<< orphan*/  setlogmask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcasecmp (char*,char*) ; 
 char* strrchr (char const*,char) ; 

void
init_logging(
	const char *	name,
	u_int32		def_syslogmask,
	int		is_daemon
	)
{
	static int	was_daemon;
	char *		cp;
	const char *	pname;

	/*
	 * ntpd defaults to only logging sync-category events, when
	 * NLOG() is used to conditionalize.  Other libntp clients
	 * leave it alone so that all NLOG() conditionals will fire.
	 * This presumes all bits lit in ntp_syslogmask can't be
	 * configured via logconfig and all lit is thereby a sentinel
	 * that ntp_syslogmask is still at its default from libntp,
	 * keeping in mind this function is called in forked children
	 * where it has already been called in the parent earlier.
	 * Forked children pass 0 for def_syslogmask.
	 */
	if (INIT_NTP_SYSLOGMASK == ntp_syslogmask &&
	    0 != def_syslogmask)
		ntp_syslogmask = def_syslogmask; /* set more via logconfig */

	/*
	 * Logging.  This may actually work on the gizmo board.  Find a name
	 * to log with by using the basename
	 */
	cp = strrchr(name, DIR_SEP);
	if (NULL == cp)
		pname = name;
	else
		pname = 1 + cp;	/* skip DIR_SEP */
	progname = estrdup(pname);
#ifdef SYS_WINNT			/* strip ".exe" */
	cp = strrchr(progname, '.');
	if (NULL != cp && !strcasecmp(cp, ".exe"))
		*cp = '\0';
#endif

#if !defined(VMS)

	if (is_daemon)
		was_daemon = TRUE;
# ifndef LOG_DAEMON
	openlog(progname, LOG_PID);
# else /* LOG_DAEMON */

#  ifndef LOG_NTP
#	define	LOG_NTP LOG_DAEMON
#  endif
	openlog(progname, LOG_PID | LOG_NDELAY, (was_daemon) 
						    ? LOG_NTP
						    : 0);
#  ifdef DEBUG
	if (debug)
		setlogmask(LOG_UPTO(LOG_DEBUG));
	else
#  endif /* DEBUG */
		setlogmask(LOG_UPTO(LOG_DEBUG)); /* @@@ was INFO */
# endif /* LOG_DAEMON */
#endif	/* !VMS */
}