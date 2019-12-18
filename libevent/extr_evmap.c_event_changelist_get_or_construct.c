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
struct event_changelist_fdinfo {int idxplus1; } ;
struct event_changelist {scalar_t__ n_changes; scalar_t__ changes_size; struct event_change* changes; } ;
struct event_change {scalar_t__ fd; short old_events; } ;
typedef  scalar_t__ evutil_socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  EVUTIL_ASSERT (int) ; 
 scalar_t__ event_changelist_grow (struct event_changelist*) ; 
 int /*<<< orphan*/  memset (struct event_change*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct event_change *
event_changelist_get_or_construct(struct event_changelist *changelist,
    evutil_socket_t fd,
    short old_events,
    struct event_changelist_fdinfo *fdinfo)
{
	struct event_change *change;

	if (fdinfo->idxplus1 == 0) {
		int idx;
		EVUTIL_ASSERT(changelist->n_changes <= changelist->changes_size);

		if (changelist->n_changes == changelist->changes_size) {
			if (event_changelist_grow(changelist) < 0)
				return NULL;
		}

		idx = changelist->n_changes++;
		change = &changelist->changes[idx];
		fdinfo->idxplus1 = idx + 1;

		memset(change, 0, sizeof(struct event_change));
		change->fd = fd;
		change->old_events = old_events;
	} else {
		change = &changelist->changes[fdinfo->idxplus1 - 1];
		EVUTIL_ASSERT(change->fd == fd);
	}
	return change;
}