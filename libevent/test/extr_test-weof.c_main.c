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
struct event {int dummy; } ;
typedef  int /*<<< orphan*/  WSADATA ;
typedef  int /*<<< orphan*/  WORD ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNIX ; 
 int /*<<< orphan*/  EV_WRITE ; 
 int /*<<< orphan*/  MAKEWORD (int,int) ; 
 int /*<<< orphan*/  SIGPIPE ; 
 scalar_t__ SIG_ERR ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  WSAStartup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_add (struct event*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_dispatch () ; 
 int /*<<< orphan*/  event_init () ; 
 int /*<<< orphan*/  event_set (struct event*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct event*) ; 
 int evutil_socketpair (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pair ; 
 scalar_t__ signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int test_okay ; 
 int /*<<< orphan*/  write_cb ; 

int
main(int argc, char **argv)
{
	struct event ev;

#ifdef _WIN32
	WORD wVersionRequested;
	WSADATA wsaData;

	wVersionRequested = MAKEWORD(2, 2);

	(void) WSAStartup(wVersionRequested, &wsaData);
#endif

#ifndef _WIN32
	if (signal(SIGPIPE, SIG_IGN) == SIG_ERR)
		return (1);
#endif

	if (evutil_socketpair(AF_UNIX, SOCK_STREAM, 0, pair) == -1)
		return (1);

	/* Initialize the event library */
	event_init();

	/* Initialize one event */
	event_set(&ev, pair[1], EV_WRITE, write_cb, &ev);

	event_add(&ev, NULL);

	event_dispatch();

	return (test_okay);
}