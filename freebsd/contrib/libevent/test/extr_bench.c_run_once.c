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
struct timeval {int dummy; } ;
typedef  int evutil_socket_t ;
typedef  scalar_t__ ev_intptr_t ;

/* Variables and functions */
 int EVLOOP_NONBLOCK ; 
 int EVLOOP_ONCE ; 
 int EV_PERSIST ; 
 int EV_READ ; 
 int count ; 
 int /*<<< orphan*/  event_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_del (int /*<<< orphan*/ *) ; 
 scalar_t__ event_initialized (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_loop (int) ; 
 int /*<<< orphan*/  event_set (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/ * events ; 
 int /*<<< orphan*/  evutil_gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evutil_timersub (struct timeval*,struct timeval*,struct timeval*) ; 
 int fired ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int) ; 
 long num_active ; 
 long num_pipes ; 
 int /*<<< orphan*/  num_writes ; 
 int* pipes ; 
 int /*<<< orphan*/  read_cb ; 
 int /*<<< orphan*/  send (int,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  writes ; 

__attribute__((used)) static struct timeval *
run_once(void)
{
	evutil_socket_t *cp, space;
	long i;
	static struct timeval ts, te;

	for (cp = pipes, i = 0; i < num_pipes; i++, cp += 2) {
		if (event_initialized(&events[i]))
			event_del(&events[i]);
		event_set(&events[i], cp[0], EV_READ | EV_PERSIST, read_cb, (void *)(ev_intptr_t) i);
		event_add(&events[i], NULL);
	}

	event_loop(EVLOOP_ONCE | EVLOOP_NONBLOCK);

	fired = 0;
	space = num_pipes / num_active;
	space = space * 2;
	for (i = 0; i < num_active; i++, fired++)
		(void) send(pipes[i * space + 1], "e", 1, 0);

	count = 0;
	writes = num_writes;
	{ int xcount = 0;
	evutil_gettimeofday(&ts, NULL);
	do {
		event_loop(EVLOOP_ONCE | EVLOOP_NONBLOCK);
		xcount++;
	} while (count != fired);
	evutil_gettimeofday(&te, NULL);

	if (xcount != count) fprintf(stderr, "Xcount: %d, Rcount: %d\n", xcount, count);
	}

	evutil_timersub(&te, &ts, &te);

	return (&te);
}