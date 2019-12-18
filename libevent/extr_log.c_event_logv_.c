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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int EVENT_LOG_DEBUG ; 
 int /*<<< orphan*/  event_debug_get_logging_mask_ () ; 
 int /*<<< orphan*/  event_log (int,char*) ; 
 int /*<<< orphan*/  evutil_snprintf (char*,int,char*,char const*) ; 
 int /*<<< orphan*/  evutil_vsnprintf (char*,int,char const*,int /*<<< orphan*/ ) ; 
 size_t strlen (char*) ; 

void
event_logv_(int severity, const char *errstr, const char *fmt, va_list ap)
{
	char buf[1024];
	size_t len;

	if (severity == EVENT_LOG_DEBUG && !event_debug_get_logging_mask_())
		return;

	if (fmt != NULL)
		evutil_vsnprintf(buf, sizeof(buf), fmt, ap);
	else
		buf[0] = '\0';

	if (errstr) {
		len = strlen(buf);
		if (len < sizeof(buf) - 3) {
			evutil_snprintf(buf + len, sizeof(buf) - len, ": %s", errstr);
		}
	}

	event_log(severity, buf);
}