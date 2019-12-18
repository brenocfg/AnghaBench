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
struct syslog_data {int dummy; } ;
typedef  int SyslogFacility ;
typedef  scalar_t__ LogLevel ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_AUTH ; 
 int /*<<< orphan*/  LOG_AUTHPRIV ; 
 int /*<<< orphan*/  LOG_DAEMON ; 
 int /*<<< orphan*/  LOG_LOCAL0 ; 
 int /*<<< orphan*/  LOG_LOCAL1 ; 
 int /*<<< orphan*/  LOG_LOCAL2 ; 
 int /*<<< orphan*/  LOG_LOCAL3 ; 
 int /*<<< orphan*/  LOG_LOCAL4 ; 
 int /*<<< orphan*/  LOG_LOCAL5 ; 
 int /*<<< orphan*/  LOG_LOCAL6 ; 
 int /*<<< orphan*/  LOG_LOCAL7 ; 
 int /*<<< orphan*/  LOG_PID ; 
 int /*<<< orphan*/  LOG_USER ; 
 struct syslog_data SYSLOG_DATA_INIT ; 
#define  SYSLOG_FACILITY_AUTH 139 
#define  SYSLOG_FACILITY_AUTHPRIV 138 
#define  SYSLOG_FACILITY_DAEMON 137 
#define  SYSLOG_FACILITY_LOCAL0 136 
#define  SYSLOG_FACILITY_LOCAL1 135 
#define  SYSLOG_FACILITY_LOCAL2 134 
#define  SYSLOG_FACILITY_LOCAL3 133 
#define  SYSLOG_FACILITY_LOCAL4 132 
#define  SYSLOG_FACILITY_LOCAL5 131 
#define  SYSLOG_FACILITY_LOCAL6 130 
#define  SYSLOG_FACILITY_LOCAL7 129 
#define  SYSLOG_FACILITY_USER 128 
 char* __progname ; 
 char* argv0 ; 
 int /*<<< orphan*/  closelog () ; 
 int /*<<< orphan*/  closelog_r (struct syslog_data*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ log_change_level (scalar_t__) ; 
 int /*<<< orphan*/  log_facility ; 
 int /*<<< orphan*/ * log_handler ; 
 int /*<<< orphan*/ * log_handler_ctx ; 
 int log_on_stderr ; 
 int /*<<< orphan*/  openlog (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  openlog_r (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct syslog_data*) ; 
 int /*<<< orphan*/  stderr ; 

void
log_init(char *av0, LogLevel level, SyslogFacility facility, int on_stderr)
{
#if defined(HAVE_OPENLOG_R) && defined(SYSLOG_DATA_INIT)
	struct syslog_data sdata = SYSLOG_DATA_INIT;
#endif

	argv0 = av0;

	if (log_change_level(level) != 0) {
		fprintf(stderr, "Unrecognized internal syslog level code %d\n",
		    (int) level);
		exit(1);
	}

	log_handler = NULL;
	log_handler_ctx = NULL;

	log_on_stderr = on_stderr;
	if (on_stderr)
		return;

	switch (facility) {
	case SYSLOG_FACILITY_DAEMON:
		log_facility = LOG_DAEMON;
		break;
	case SYSLOG_FACILITY_USER:
		log_facility = LOG_USER;
		break;
	case SYSLOG_FACILITY_AUTH:
		log_facility = LOG_AUTH;
		break;
#ifdef LOG_AUTHPRIV
	case SYSLOG_FACILITY_AUTHPRIV:
		log_facility = LOG_AUTHPRIV;
		break;
#endif
	case SYSLOG_FACILITY_LOCAL0:
		log_facility = LOG_LOCAL0;
		break;
	case SYSLOG_FACILITY_LOCAL1:
		log_facility = LOG_LOCAL1;
		break;
	case SYSLOG_FACILITY_LOCAL2:
		log_facility = LOG_LOCAL2;
		break;
	case SYSLOG_FACILITY_LOCAL3:
		log_facility = LOG_LOCAL3;
		break;
	case SYSLOG_FACILITY_LOCAL4:
		log_facility = LOG_LOCAL4;
		break;
	case SYSLOG_FACILITY_LOCAL5:
		log_facility = LOG_LOCAL5;
		break;
	case SYSLOG_FACILITY_LOCAL6:
		log_facility = LOG_LOCAL6;
		break;
	case SYSLOG_FACILITY_LOCAL7:
		log_facility = LOG_LOCAL7;
		break;
	default:
		fprintf(stderr,
		    "Unrecognized internal syslog facility code %d\n",
		    (int) facility);
		exit(1);
	}

	/*
	 * If an external library (eg libwrap) attempts to use syslog
	 * immediately after reexec, syslog may be pointing to the wrong
	 * facility, so we force an open/close of syslog here.
	 */
#if defined(HAVE_OPENLOG_R) && defined(SYSLOG_DATA_INIT)
	openlog_r(argv0 ? argv0 : __progname, LOG_PID, log_facility, &sdata);
	closelog_r(&sdata);
#else
	openlog(argv0 ? argv0 : __progname, LOG_PID, log_facility);
	closelog();
#endif
}