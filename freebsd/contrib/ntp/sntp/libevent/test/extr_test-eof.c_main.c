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
typedef  int /*<<< orphan*/  evutil_socket_t ;
typedef  int /*<<< orphan*/  WSADATA ;
typedef  int /*<<< orphan*/  WORD ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNIX ; 
 int EV_READ ; 
 int EV_TIMEOUT ; 
 int /*<<< orphan*/  MAKEWORD (int,int) ; 
 int /*<<< orphan*/  SHUT_WR ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  WSAStartup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_add (struct event*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_dispatch () ; 
 int /*<<< orphan*/  event_init () ; 
 int /*<<< orphan*/  event_set (struct event*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct event*) ; 
 int evutil_socketpair (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_cb ; 
 scalar_t__ send (int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shutdown (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char const*) ; 
 int test_okay ; 
 int /*<<< orphan*/  timeout ; 

int
main(int argc, char **argv)
{
	struct event ev;
	const char *test = "test string";
	evutil_socket_t pair[2];

#ifdef _WIN32
	WORD wVersionRequested;
	WSADATA wsaData;

	wVersionRequested = MAKEWORD(2, 2);

	(void) WSAStartup(wVersionRequested, &wsaData);
#endif

	if (evutil_socketpair(AF_UNIX, SOCK_STREAM, 0, pair) == -1)
		return (1);


	if (send(pair[0], test, (int)strlen(test)+1, 0) < 0)
		return (1);
	shutdown(pair[0], SHUT_WR);

	/* Initalize the event library */
	event_init();

	/* Initalize one event */
	event_set(&ev, pair[1], EV_READ | EV_TIMEOUT, read_cb, &ev);

	event_add(&ev, &timeout);

	event_dispatch();

	return (test_okay);
}