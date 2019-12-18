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
struct timeval {int tv_sec; } ;
struct event_base {int dummy; } ;
struct event {int dummy; } ;
typedef  int /*<<< orphan*/  WSADATA ;
typedef  int /*<<< orphan*/  WORD ;

/* Variables and functions */
 int EV_PERSIST ; 
 int /*<<< orphan*/  MAKEWORD (int,int) ; 
 int /*<<< orphan*/  WSAStartup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_add (struct event*,struct timeval*) ; 
 int /*<<< orphan*/  event_assign (struct event*,struct event_base*,int,int,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  event_base_dispatch (struct event_base*) ; 
 struct event_base* event_base_new () ; 
 int event_is_persistent ; 
 int /*<<< orphan*/  evutil_gettimeofday (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evutil_timerclear (struct timeval*) ; 
 int /*<<< orphan*/  lasttime ; 
 int /*<<< orphan*/  setbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  timeout_cb ; 

int
main(int argc, char **argv)
{
	struct event timeout;
	struct timeval tv;
	struct event_base *base;
	int flags;

#ifdef _WIN32
	WORD wVersionRequested;
	WSADATA wsaData;

	wVersionRequested = MAKEWORD(2, 2);

	(void)WSAStartup(wVersionRequested, &wsaData);
#endif

	if (argc == 2 && !strcmp(argv[1], "-p")) {
		event_is_persistent = 1;
		flags = EV_PERSIST;
	} else {
		event_is_persistent = 0;
		flags = 0;
	}

	/* Initialize the event library */
	base = event_base_new();

	/* Initialize one event */
	event_assign(&timeout, base, -1, flags, timeout_cb, (void*) &timeout);

	evutil_timerclear(&tv);
	tv.tv_sec = 2;
	event_add(&timeout, &tv);

	evutil_gettimeofday(&lasttime, NULL);

	setbuf(stdout, NULL);
	setbuf(stderr, NULL);

	event_base_dispatch(base);

	return (0);
}