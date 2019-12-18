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
struct timeval {int tv_sec; int tv_usec; } ;
struct event_base {int dummy; } ;
struct event {int dummy; } ;
struct cpu_usage_timer {int dummy; } ;
typedef  int /*<<< orphan*/  evutil_socket_t ;
typedef  int /*<<< orphan*/  WSADATA ;
typedef  int /*<<< orphan*/  WORD ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNIX ; 
 int EV_PERSIST ; 
 int EV_WRITE ; 
 int /*<<< orphan*/  MAKEWORD (int,int) ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  WSAStartup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_add (struct event*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_base_dispatch (struct event_base*) ; 
 int /*<<< orphan*/  event_base_free (struct event_base*) ; 
 struct event_base* event_base_new () ; 
 int /*<<< orphan*/  event_free (struct event*) ; 
 struct event* event_new (struct event_base*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct event**) ; 
 int /*<<< orphan*/  evtimer_add (struct event*,struct timeval*) ; 
 struct event* evtimer_new (struct event_base*,int /*<<< orphan*/ ,struct event**) ; 
 int evutil_socketpair (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_cpu_usage (struct cpu_usage_timer*,double*,double*,double*) ; 
 int /*<<< orphan*/  printf (char*,int,int,double) ; 
 int /*<<< orphan*/  start_cpu_usage_timer (struct cpu_usage_timer*) ; 
 int /*<<< orphan*/  timeout_cb ; 
 int /*<<< orphan*/  write_cb ; 

int
main(int argc, char **argv)
{
	struct event* ev;
	struct event* timeout;
	struct event_base* base;

	evutil_socket_t pair[2];
	struct timeval tv;
	struct cpu_usage_timer timer;

	double usage, secPassed, secUsed;

#ifdef _WIN32
	WORD wVersionRequested;
	WSADATA wsaData;

	wVersionRequested = MAKEWORD(2, 2);

	(void) WSAStartup(wVersionRequested, &wsaData);
#endif
	if (evutil_socketpair(AF_UNIX, SOCK_STREAM, 0, pair) == -1)
		return (1);

	/* Initialize the event library */
	if (!(base = event_base_new()))
		return (1);

	/* Initialize a timeout to terminate the test */
	timeout = evtimer_new(base,timeout_cb,&timeout);
	/* and watch for writability on one end of the pipe */
	ev = event_new(base,pair[1],EV_WRITE | EV_PERSIST, write_cb, &ev);

	tv.tv_sec  = 1;
	tv.tv_usec = 500*1000;

	evtimer_add(timeout, &tv);

	event_add(ev, NULL);

	start_cpu_usage_timer(&timer);

	event_base_dispatch(base);

	event_free(ev);
	event_free(timeout);
	event_base_free(base);

	get_cpu_usage(&timer, &secPassed, &secUsed, &usage);

	/* attempt to calculate our cpu usage over the test should be
	   virtually nil */

	printf("usec used=%d, usec passed=%d, cpu usage=%.2f%%\n",
	    (int)(secUsed*1e6),
	    (int)(secPassed*1e6),
	    usage*100);

	if (usage > 50.0) /* way too high */
	  return 1;

	return 0;
}