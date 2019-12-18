#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct rev_info {int linear; struct commit_list* previous_parents; scalar_t__ reverse; scalar_t__ track_first_time; } ;
struct commit_list {TYPE_2__* item; struct commit_list* next; } ;
struct TYPE_6__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  oid; } ;
struct commit {int /*<<< orphan*/  parents; TYPE_3__ object; } ;
struct TYPE_4__ {int /*<<< orphan*/  oid; } ;
struct TYPE_5__ {TYPE_1__ object; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACK_LINEAR ; 
 struct commit_list* copy_commit_list (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_commit_list (struct commit_list*) ; 
 scalar_t__ oideq (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void track_linear(struct rev_info *revs, struct commit *commit)
{
	if (revs->track_first_time) {
		revs->linear = 1;
		revs->track_first_time = 0;
	} else {
		struct commit_list *p;
		for (p = revs->previous_parents; p; p = p->next)
			if (p->item == NULL || /* first commit */
			    oideq(&p->item->object.oid, &commit->object.oid))
				break;
		revs->linear = p != NULL;
	}
	if (revs->reverse) {
		if (revs->linear)
			commit->object.flags |= TRACK_LINEAR;
	}
	free_commit_list(revs->previous_parents);
	revs->previous_parents = copy_commit_list(commit->parents);
}