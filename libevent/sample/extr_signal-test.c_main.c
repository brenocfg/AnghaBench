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
struct event_base {int dummy; } ;
struct event {int dummy; } ;
typedef  int /*<<< orphan*/  WSADATA ;
typedef  int /*<<< orphan*/  WORD ;

/* Variables and functions */
 int /*<<< orphan*/  MAKEWORD (int,int) ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  WSAStartup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_add (struct event*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_base_dispatch (struct event_base*) ; 
 int /*<<< orphan*/  event_base_free (struct event_base*) ; 
 struct event_base* event_base_new () ; 
 int /*<<< orphan*/  event_free (struct event*) ; 
 int /*<<< orphan*/  event_self_cbarg () ; 
 struct event* evsignal_new (struct event_base*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal_cb ; 

int
main(int argc, char **argv)
{
	struct event *signal_int = NULL;
	struct event_base* base;
	int ret = 0;
#ifdef _WIN32
	WORD wVersionRequested;
	WSADATA wsaData;

	wVersionRequested = MAKEWORD(2, 2);

	(void) WSAStartup(wVersionRequested, &wsaData);
#endif

	/* Initialize the event library */
	base = event_base_new();
	if (!base) {
		ret = 1;
		goto out;
	}

	/* Initialize one event */
	signal_int = evsignal_new(base, SIGINT, signal_cb, event_self_cbarg());
	if (!signal_int) {
		ret = 2;
		goto out;
	}
	event_add(signal_int, NULL);

	event_base_dispatch(base);

out:
	if (signal_int)
		event_free(signal_int);
	if (base)
		event_base_free(base);
	return ret;
}