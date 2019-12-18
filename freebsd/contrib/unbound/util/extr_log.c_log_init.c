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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_DAEMON ; 
 int /*<<< orphan*/  LOG_NDELAY ; 
 int /*<<< orphan*/  VERB_QUERY ; 
 scalar_t__ _IOLBF ; 
 int /*<<< orphan*/  closelog () ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  ident ; 
 int key_created ; 
 int /*<<< orphan*/  lock_quick_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_quick_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_quick_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_err (char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_lock ; 
 int /*<<< orphan*/ * logfile ; 
 int logging_to_syslog ; 
 int /*<<< orphan*/  logkey ; 
 int /*<<< orphan*/  openlog (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setvbuf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stderr ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ub_thread_key_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*,char*) ; 

void
log_init(const char* filename, int use_syslog, const char* chrootdir)
{
	FILE *f;
	if(!key_created) {
		key_created = 1;
		ub_thread_key_create(&logkey, NULL);
		lock_quick_init(&log_lock);
	}
	lock_quick_lock(&log_lock);
	if(logfile 
#if defined(HAVE_SYSLOG_H) || defined(UB_ON_WINDOWS)
	|| logging_to_syslog
#endif
	) {
		lock_quick_unlock(&log_lock); /* verbose() needs the lock */
		verbose(VERB_QUERY, "switching log to %s", 
			use_syslog?"syslog":(filename&&filename[0]?filename:"stderr"));
		lock_quick_lock(&log_lock);
	}
	if(logfile && logfile != stderr) {
		FILE* cl = logfile;
		logfile = NULL; /* set to NULL before it is closed, so that
			other threads have a valid logfile or NULL */
		fclose(cl);
	}
#ifdef HAVE_SYSLOG_H
	if(logging_to_syslog) {
		closelog();
		logging_to_syslog = 0;
	}
	if(use_syslog) {
		/* do not delay opening until first write, because we may
		 * chroot and no longer be able to access dev/log and so on */
		openlog(ident, LOG_NDELAY, LOG_DAEMON);
		logging_to_syslog = 1;
		lock_quick_unlock(&log_lock);
		return;
	}
#elif defined(UB_ON_WINDOWS)
	if(logging_to_syslog) {
		logging_to_syslog = 0;
	}
	if(use_syslog) {
		logging_to_syslog = 1;
		lock_quick_unlock(&log_lock);
		return;
	}
#endif /* HAVE_SYSLOG_H */
	if(!filename || !filename[0]) {
		logfile = stderr;
		lock_quick_unlock(&log_lock);
		return;
	}
	/* open the file for logging */
	if(chrootdir && chrootdir[0] && strncmp(filename, chrootdir,
		strlen(chrootdir)) == 0) 
		filename += strlen(chrootdir);
	f = fopen(filename, "a");
	if(!f) {
		lock_quick_unlock(&log_lock);
		log_err("Could not open logfile %s: %s", filename, 
			strerror(errno));
		return;
	}
#ifndef UB_ON_WINDOWS
	/* line buffering does not work on windows */
	setvbuf(f, NULL, (int)_IOLBF, 0);
#endif
	logfile = f;
	lock_quick_unlock(&log_lock);
}