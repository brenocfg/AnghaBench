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

/* Variables and functions */
 int LOG_DEBUG ; 
 int LOG_ERR ; 
 int LOG_NOTICE ; 
 int LOG_WARNING ; 
#define  _EVENT_LOG_DEBUG 131 
#define  _EVENT_LOG_ERR 130 
#define  _EVENT_LOG_MSG 129 
#define  _EVENT_LOG_WARN 128 
 int /*<<< orphan*/  msyslog (int,char*,char const*) ; 

void
sntp_libevent_log_cb(
	int		severity,
	const char *	msg
	)
{
	int		level;

	switch (severity) {

	default:
	case _EVENT_LOG_DEBUG:
		level = LOG_DEBUG;
		break;

	case _EVENT_LOG_MSG:
		level = LOG_NOTICE;
		break;

	case _EVENT_LOG_WARN:
		level = LOG_WARNING;
		break;

	case _EVENT_LOG_ERR:
		level = LOG_ERR;
		break;
	}

	msyslog(level, "%s", msg);
}