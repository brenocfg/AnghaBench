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
struct event_changelist {scalar_t__ changes; } ;

/* Variables and functions */
 int /*<<< orphan*/  event_changelist_init_ (struct event_changelist*) ; 
 int /*<<< orphan*/  mm_free (scalar_t__) ; 

void
event_changelist_freemem_(struct event_changelist *changelist)
{
	if (changelist->changes)
		mm_free(changelist->changes);
	event_changelist_init_(changelist); /* zero it all out. */
}