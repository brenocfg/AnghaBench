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
typedef  int /*<<< orphan*/  isc_assertiontype_t ;

/* Variables and functions */
 int /*<<< orphan*/  DebugBreak () ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  abort () ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  isc_assertion_setcallback (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isc_assertion_typetotext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msyslog (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void
assertion_failed(
	const char *file,
	int line,
	isc_assertiontype_t type,
	const char *cond
	)
{
	isc_assertion_setcallback(NULL);    /* Avoid recursion */

	msyslog(LOG_ERR, "%s:%d: %s(%s) failed",
		file, line, isc_assertion_typetotext(type), cond);
	msyslog(LOG_ERR, "exiting (due to assertion failure)");

#if defined(DEBUG) && defined(SYS_WINNT)
	if (debug)
		DebugBreak();
#endif

	abort();
}