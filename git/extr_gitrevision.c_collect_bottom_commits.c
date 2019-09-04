#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct commit_list {TYPE_2__* item; struct commit_list* next; } ;
struct TYPE_3__ {int flags; } ;
struct TYPE_4__ {TYPE_1__ object; } ;

/* Variables and functions */
 int BOTTOM ; 
 int /*<<< orphan*/  commit_list_insert (TYPE_2__*,struct commit_list**) ; 

__attribute__((used)) static struct commit_list *collect_bottom_commits(struct commit_list *list)
{
	struct commit_list *elem, *bottom = NULL;
	for (elem = list; elem; elem = elem->next)
		if (elem->item->object.flags & BOTTOM)
			commit_list_insert(elem->item, &bottom);
	return bottom;
}