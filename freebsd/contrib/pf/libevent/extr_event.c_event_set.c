#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct event {void (* ev_callback ) (int,short,void*) ;int ev_fd; short ev_events; int ev_pri; int /*<<< orphan*/ * ev_pncalls; scalar_t__ ev_ncalls; int /*<<< orphan*/  ev_flags; void* ev_arg; TYPE_1__* ev_base; } ;
struct TYPE_2__ {int nactivequeues; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVLIST_INIT ; 
 TYPE_1__* current_base ; 

void
event_set(struct event *ev, int fd, short events,
	  void (*callback)(int, short, void *), void *arg)
{
	/* Take the current base - caller needs to set the real base later */
	ev->ev_base = current_base;

	ev->ev_callback = callback;
	ev->ev_arg = arg;
	ev->ev_fd = fd;
	ev->ev_events = events;
	ev->ev_flags = EVLIST_INIT;
	ev->ev_ncalls = 0;
	ev->ev_pncalls = NULL;

	/* by default, we put new events into the middle priority */
	ev->ev_pri = current_base->nactivequeues/2;
}