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
struct rev_info {scalar_t__ right_only; } ;
struct commit_list {struct commit* item; struct commit_list* next; } ;
struct TYPE_2__ {int flags; } ;
struct commit {TYPE_1__ object; } ;

/* Variables and functions */
 int SHOWN ; 
 int SYMMETRIC_LEFT ; 

__attribute__((used)) static void limit_left_right(struct commit_list *list, struct rev_info *revs)
{
	struct commit_list *p;

	for (p = list; p; p = p->next) {
		struct commit *commit = p->item;

		if (revs->right_only) {
			if (commit->object.flags & SYMMETRIC_LEFT)
				commit->object.flags |= SHOWN;
		} else	/* revs->left_only is set */
			if (!(commit->object.flags & SYMMETRIC_LEFT))
				commit->object.flags |= SHOWN;
	}
}