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
struct event_dlist {int dummy; } ;
struct event {int dummy; } ;

/* Variables and functions */
 struct event* LIST_FIRST (struct event_dlist*) ; 
 int /*<<< orphan*/  event_del (struct event*) ; 

__attribute__((used)) static int
delete_all_in_dlist(struct event_dlist *dlist)
{
	struct event *ev;
	while ((ev = LIST_FIRST(dlist)))
		event_del(ev);
	return 0;
}