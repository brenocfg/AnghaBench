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
typedef  int /*<<< orphan*/  errbuf ;

/* Variables and functions */
 int /*<<< orphan*/  DebugBreak () ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  abort () ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  isc_error_setfatal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msyslog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  vsnprintf (char*,int,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
library_fatal_error(
	const char *file,
	int line,
	const char *format,
	va_list args
	)
{
	char errbuf[256];

	isc_error_setfatal(NULL);  /* Avoid recursion */

	msyslog(LOG_ERR, "%s:%d: fatal error:", file, line);
	vsnprintf(errbuf, sizeof(errbuf), format, args);
	msyslog(LOG_ERR, "%s", errbuf);
	msyslog(LOG_ERR, "exiting (due to fatal error in library)");

#if defined(DEBUG) && defined(SYS_WINNT)
	if (debug)
		DebugBreak();
#endif

	abort();
}