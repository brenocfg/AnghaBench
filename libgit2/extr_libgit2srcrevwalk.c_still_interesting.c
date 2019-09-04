#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_5__ {TYPE_1__* item; struct TYPE_5__* next; } ;
typedef  TYPE_2__ git_commit_list ;
struct TYPE_4__ {scalar_t__ time; int /*<<< orphan*/  uninteresting; } ;

/* Variables and functions */
 int SLOP ; 

__attribute__((used)) static int still_interesting(git_commit_list *list, int64_t time, int slop)
{
	/* The empty list is pretty boring */
	if (!list)
		return 0;

	/*
	 * If the destination list has commits with an earlier date than our
	 * source, we want to reset the slop counter as we're not done.
	 */
	if (time <= list->item->time)
		return SLOP;

	for (; list; list = list->next) {
		/*
		 * If the destination list still contains interesting commits we
		 * want to continue looking.
		 */
		if (!list->item->uninteresting || list->item->time > time)
			return SLOP;
	}

	/* Everything's uninteresting, reduce the count */
	return slop - 1;
}