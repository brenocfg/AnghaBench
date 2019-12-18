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
typedef  int /*<<< orphan*/  va_list ;
typedef  int /*<<< orphan*/  log ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
#define  LOG_ALERT 137 
#define  LOG_CRIT 136 
#define  LOG_DEBUG 135 
#define  LOG_EMERG 134 
#define  LOG_ERR 133 
#define  LOG_INFO 132 
#define  LOG_NOTICE 131 
#define  LOG_WARNING 130 
 scalar_t__ PJDLOG_INITIALIZED ; 
#define  PJDLOG_MODE_STD 129 
#define  PJDLOG_MODE_SYSLOG 128 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  assert (int) ; 
 int errno ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int pjdlog_debug_level ; 
 scalar_t__ pjdlog_initialized ; 
 char* pjdlog_level_string (int) ; 
 int pjdlog_mode ; 
 char* pjdlog_prefix ; 
 int snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/ * stderr ; 
 int /*<<< orphan*/ * stdout ; 
 char* strerror (int) ; 
 int /*<<< orphan*/  syslog (int,char*,char*) ; 
 int /*<<< orphan*/  vfprintf (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int vsnprintf (char*,int,char const*,int /*<<< orphan*/ ) ; 

void
pjdlogv_common(int loglevel, int debuglevel, int error, const char *fmt,
    va_list ap)
{
	int saved_errno;

	assert(pjdlog_initialized == PJDLOG_INITIALIZED);
	assert(loglevel == LOG_EMERG || loglevel == LOG_ALERT ||
	    loglevel == LOG_CRIT || loglevel == LOG_ERR ||
	    loglevel == LOG_WARNING || loglevel == LOG_NOTICE ||
	    loglevel == LOG_INFO || loglevel == LOG_DEBUG);
	assert(loglevel != LOG_DEBUG || debuglevel > 0);
	assert(error >= -1);

	/* Ignore debug above configured level. */
	if (loglevel == LOG_DEBUG && debuglevel > pjdlog_debug_level)
		return;

	saved_errno = errno;

	switch (pjdlog_mode) {
	case PJDLOG_MODE_STD:
	    {
		FILE *out;

		/*
		 * We send errors and warning to stderr and the rest to stdout.
		 */
		switch (loglevel) {
		case LOG_EMERG:
		case LOG_ALERT:
		case LOG_CRIT:
		case LOG_ERR:
		case LOG_WARNING:
			out = stderr;
			break;
		case LOG_NOTICE:
		case LOG_INFO:
		case LOG_DEBUG:
			out = stdout;
			break;
		default:
			assert(!"Invalid loglevel.");
			abort();	/* XXX: gcc */
		}

		fprintf(out, "[%s]", pjdlog_level_string(loglevel));
		/* Attach debuglevel if this is debug log. */
		if (loglevel == LOG_DEBUG)
			fprintf(out, "[%d]", debuglevel);
		fprintf(out, " %s", pjdlog_prefix);
		vfprintf(out, fmt, ap);
		if (error != -1)
			fprintf(out, ": %s.", strerror(error));
		fprintf(out, "\n");
		fflush(out);
		break;
	    }
	case PJDLOG_MODE_SYSLOG:
	    {
		char log[1024];
		int len;

		len = snprintf(log, sizeof(log), "%s", pjdlog_prefix);
		if ((size_t)len < sizeof(log))
			len += vsnprintf(log + len, sizeof(log) - len, fmt, ap);
		if (error != -1 && (size_t)len < sizeof(log)) {
			(void)snprintf(log + len, sizeof(log) - len, ": %s.",
			    strerror(error));
		}
		syslog(loglevel, "%s", log);
		break;
	    }
	default:
		assert(!"Invalid mode.");
	}

	errno = saved_errno;
}