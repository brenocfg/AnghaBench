#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned int sorting; int limited; int /*<<< orphan*/ * enqueue; int /*<<< orphan*/ * get_next; scalar_t__ walking; } ;
typedef  TYPE_1__ git_revwalk ;

/* Variables and functions */
 int GIT_SORT_NONE ; 
 int GIT_SORT_TIME ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  git_revwalk_reset (TYPE_1__*) ; 
 int /*<<< orphan*/  revwalk_enqueue_timesort ; 
 int /*<<< orphan*/  revwalk_enqueue_unsorted ; 
 int /*<<< orphan*/  revwalk_next_timesort ; 
 int /*<<< orphan*/  revwalk_next_unsorted ; 

void git_revwalk_sorting(git_revwalk *walk, unsigned int sort_mode)
{
	assert(walk);

	if (walk->walking)
		git_revwalk_reset(walk);

	walk->sorting = sort_mode;

	if (walk->sorting & GIT_SORT_TIME) {
		walk->get_next = &revwalk_next_timesort;
		walk->enqueue = &revwalk_enqueue_timesort;
	} else {
		walk->get_next = &revwalk_next_unsorted;
		walk->enqueue = &revwalk_enqueue_unsorted;
	}

	if (walk->sorting != GIT_SORT_NONE)
		walk->limited = 1;
}