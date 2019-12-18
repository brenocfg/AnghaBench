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
struct event_changelist {int n_changes; struct event_change* changes; } ;
struct event_change {int dummy; } ;
struct event_base {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVUTIL_ASSERT (int) ; 
 struct event_changelist_fdinfo* event_change_get_fdinfo (struct event_base*,struct event_change*) ; 
 int /*<<< orphan*/  event_changelist_check (struct event_base*) ; 

void
event_changelist_remove_all_(struct event_changelist *changelist,
    struct event_base *base)
{
	int i;

	event_changelist_check(base);

	for (i = 0; i < changelist->n_changes; ++i) {
		struct event_change *ch = &changelist->changes[i];
		struct event_changelist_fdinfo *fdinfo =
		    event_change_get_fdinfo(base, ch);
		EVUTIL_ASSERT(fdinfo->idxplus1 == i + 1);
		fdinfo->idxplus1 = 0;
	}

	changelist->n_changes = 0;

	event_changelist_check(base);
}