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
struct timeval {int /*<<< orphan*/  tv_usec; scalar_t__ tv_sec; } ;
struct event {int dummy; } ;
typedef  int /*<<< orphan*/  WSADATA ;
typedef  int /*<<< orphan*/  WORD ;

/* Variables and functions */
 int /*<<< orphan*/  MAKEWORD (int,int) ; 
 int NEVENT ; 
 int /*<<< orphan*/  WSAStartup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int called ; 
 int /*<<< orphan*/ * ev ; 
 int /*<<< orphan*/  event_dispatch () ; 
 int /*<<< orphan*/  event_init () ; 
 int /*<<< orphan*/  evtimer_add (int /*<<< orphan*/ ,struct timeval*) ; 
 int /*<<< orphan*/  evtimer_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evutil_weakrand_seed_ (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  malloc (int) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 
 int /*<<< orphan*/  rand_int (int) ; 
 int /*<<< orphan*/  time_cb ; 
 int /*<<< orphan*/  weakrand_state ; 

int
main(int argc, char **argv)
{
	struct timeval tv;
	int i;
#ifdef _WIN32
	WORD wVersionRequested;
	WSADATA wsaData;

	wVersionRequested = MAKEWORD(2, 2);

	(void) WSAStartup(wVersionRequested, &wsaData);
#endif

	evutil_weakrand_seed_(&weakrand_state, 0);

	/* Initalize the event library */
	event_init();

	for (i = 0; i < NEVENT; i++) {
		ev[i] = malloc(sizeof(struct event));

		/* Initalize one event */
		evtimer_set(ev[i], time_cb, ev[i]);
		tv.tv_sec = 0;
		tv.tv_usec = rand_int(50000);
		evtimer_add(ev[i], &tv);
	}

	event_dispatch();


	printf("%d, %d\n", called, NEVENT);
	return (called < NEVENT);
}