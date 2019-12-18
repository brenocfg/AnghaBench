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
struct event_changelist_fdinfo {int dummy; } ;
struct event_changelist {int dummy; } ;
struct event_change {short read_change; short write_change; short close_change; } ;
struct event_base {struct event_changelist changelist; } ;
typedef  int /*<<< orphan*/  evutil_socket_t ;

/* Variables and functions */
 short EV_CHANGE_ADD ; 
 short EV_CLOSED ; 
 short EV_ET ; 
 short EV_PERSIST ; 
 short EV_READ ; 
 short EV_SIGNAL ; 
 short EV_WRITE ; 
 int /*<<< orphan*/  event_changelist_check (struct event_base*) ; 
 struct event_change* event_changelist_get_or_construct (struct event_changelist*,int /*<<< orphan*/ ,short,struct event_changelist_fdinfo*) ; 

int
event_changelist_add_(struct event_base *base, evutil_socket_t fd, short old, short events,
    void *p)
{
	struct event_changelist *changelist = &base->changelist;
	struct event_changelist_fdinfo *fdinfo = p;
	struct event_change *change;

	event_changelist_check(base);

	change = event_changelist_get_or_construct(changelist, fd, old, fdinfo);
	if (!change)
		return -1;

	/* An add replaces any previous delete, but doesn't result in a no-op,
	 * since the delete might fail (because the fd had been closed since
	 * the last add, for instance. */

	if (events & (EV_READ|EV_SIGNAL)) {
		change->read_change = EV_CHANGE_ADD |
		    (events & (EV_ET|EV_PERSIST|EV_SIGNAL));
	}
	if (events & EV_WRITE) {
		change->write_change = EV_CHANGE_ADD |
		    (events & (EV_ET|EV_PERSIST|EV_SIGNAL));
	}
	if (events & EV_CLOSED) {
		change->close_change = EV_CHANGE_ADD |
		    (events & (EV_ET|EV_PERSIST|EV_SIGNAL));
	}

	event_changelist_check(base);
	return (0);
}