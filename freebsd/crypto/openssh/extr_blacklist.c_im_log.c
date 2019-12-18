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
typedef  int /*<<< orphan*/  LogLevel ;

/* Variables and functions */
#define  LOG_DEBUG 130 
#define  LOG_ERR 129 
#define  LOG_INFO 128 
 int /*<<< orphan*/  SYSLOG_LEVEL_DEBUG1 ; 
 int /*<<< orphan*/  SYSLOG_LEVEL_DEBUG2 ; 
 int /*<<< orphan*/  SYSLOG_LEVEL_ERROR ; 
 int /*<<< orphan*/  SYSLOG_LEVEL_INFO ; 
 int /*<<< orphan*/  do_log (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

void
im_log(int priority, const char *message, va_list args)
{
	LogLevel imlevel;

	switch (priority) {
	case LOG_ERR:
		imlevel = SYSLOG_LEVEL_ERROR;
		break;
	case LOG_DEBUG:
		imlevel = SYSLOG_LEVEL_DEBUG1;
		break;
	case LOG_INFO:
		imlevel = SYSLOG_LEVEL_INFO;
		break;
	default:
		imlevel = SYSLOG_LEVEL_DEBUG2;
	}
	do_log(imlevel, message, args);
}