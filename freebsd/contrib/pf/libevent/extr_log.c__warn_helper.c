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
 int /*<<< orphan*/  event_log (int,char*) ; 
 int /*<<< orphan*/  event_snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event_vsnprintf (char*,int,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static void
_warn_helper(int severity, int log_errno, const char *fmt, va_list ap)
{
	char buf[1024];
	size_t len;

	if (fmt != NULL)
		event_vsnprintf(buf, sizeof(buf), fmt, ap);
	else
		buf[0] = '\0';

	if (log_errno >= 0) {
		len = strlen(buf);
		if (len < sizeof(buf) - 3) {
			event_snprintf(buf + len, sizeof(buf) - len, ": %s",
			    strerror(log_errno));
		}
	}

	event_log(severity, buf);
}