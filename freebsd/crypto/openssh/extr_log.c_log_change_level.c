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
typedef  int LogLevel ;

/* Variables and functions */
#define  SYSLOG_LEVEL_DEBUG1 135 
#define  SYSLOG_LEVEL_DEBUG2 134 
#define  SYSLOG_LEVEL_DEBUG3 133 
#define  SYSLOG_LEVEL_ERROR 132 
#define  SYSLOG_LEVEL_FATAL 131 
#define  SYSLOG_LEVEL_INFO 130 
#define  SYSLOG_LEVEL_QUIET 129 
#define  SYSLOG_LEVEL_VERBOSE 128 
 int /*<<< orphan*/ * argv0 ; 
 int log_level ; 

int
log_change_level(LogLevel new_log_level)
{
	/* no-op if log_init has not been called */
	if (argv0 == NULL)
		return 0;

	switch (new_log_level) {
	case SYSLOG_LEVEL_QUIET:
	case SYSLOG_LEVEL_FATAL:
	case SYSLOG_LEVEL_ERROR:
	case SYSLOG_LEVEL_INFO:
	case SYSLOG_LEVEL_VERBOSE:
	case SYSLOG_LEVEL_DEBUG1:
	case SYSLOG_LEVEL_DEBUG2:
	case SYSLOG_LEVEL_DEBUG3:
		log_level = new_log_level;
		return 0;
	default:
		return -1;
	}
}