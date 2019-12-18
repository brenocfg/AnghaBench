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
struct match_list {int /*<<< orphan*/  unmatched_count; int /*<<< orphan*/  count; struct match** last; } ;
struct match {struct match* next; } ;

/* Variables and functions */

__attribute__((used)) static void
match_list_add(struct match_list *list, struct match *m)
{
	*list->last = m;
	list->last = &(m->next);
	list->count++;
	list->unmatched_count++;
}