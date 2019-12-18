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
struct commit_list {struct commit_list* next; struct commit* item; } ;
struct TYPE_2__ {int flags; } ;
struct commit {TYPE_1__ object; } ;

/* Variables and functions */
 int UNINTERESTING ; 

__attribute__((used)) static int everybody_uninteresting(struct commit_list *orig,
				   struct commit **interesting_cache)
{
	struct commit_list *list = orig;

	if (*interesting_cache) {
		struct commit *commit = *interesting_cache;
		if (!(commit->object.flags & UNINTERESTING))
			return 0;
	}

	while (list) {
		struct commit *commit = list->item;
		list = list->next;
		if (commit->object.flags & UNINTERESTING)
			continue;

		*interesting_cache = commit;
		return 0;
	}
	return 1;
}