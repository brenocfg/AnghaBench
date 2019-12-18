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
typedef  int /*<<< orphan*/  WSADATA ;
typedef  int /*<<< orphan*/  WORD ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT_DBG_ALL ; 
 int /*<<< orphan*/  MAKEWORD (int,int) ; 
 int /*<<< orphan*/  SIGPIPE ; 
 scalar_t__ SIG_ERR ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  WSAStartup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_enable_debug_logging (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event_enable_debug_mode () ; 
 int /*<<< orphan*/  evthread_enable_lock_debugging () ; 
 int /*<<< orphan*/  evutil_weakrand_seed_ (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ getenv (char*) ; 
 int /*<<< orphan*/  libevent_global_shutdown () ; 
 int libevent_tests_running_in_debug_mode ; 
 scalar_t__ signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_weakrand_state ; 
 int /*<<< orphan*/  testaliases ; 
 int /*<<< orphan*/  testgroups ; 
 scalar_t__ tinytest_main (int,char const**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tinytest_set_aliases (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tinytest_skip (int /*<<< orphan*/ ,char*) ; 

int
main(int argc, const char **argv)
{
#ifdef _WIN32
	WORD wVersionRequested;
	WSADATA wsaData;

	wVersionRequested = MAKEWORD(2, 2);

	(void) WSAStartup(wVersionRequested, &wsaData);
#endif

#ifndef _WIN32
	if (signal(SIGPIPE, SIG_IGN) == SIG_ERR)
		return 1;
#endif

#ifdef _WIN32
	tinytest_skip(testgroups, "http/connection_retry");
	tinytest_skip(testgroups, "http/https_connection_retry");
#endif

#ifndef EVENT__DISABLE_THREAD_SUPPORT
	if (!getenv("EVENT_NO_DEBUG_LOCKS"))
		evthread_enable_lock_debugging();
#endif

	if (getenv("EVENT_DEBUG_MODE")) {
		event_enable_debug_mode();
		libevent_tests_running_in_debug_mode = 1;
	}
	if (getenv("EVENT_DEBUG_LOGGING_ALL")) {
		event_enable_debug_logging(EVENT_DBG_ALL);
	}

	tinytest_set_aliases(testaliases);

	evutil_weakrand_seed_(&test_weakrand_state, 0);

	if (tinytest_main(argc,argv,testgroups))
		return 1;

	libevent_global_shutdown();

	return 0;
}