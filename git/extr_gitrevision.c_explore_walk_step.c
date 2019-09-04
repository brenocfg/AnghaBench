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
struct topo_walk_info {int /*<<< orphan*/  explore_queue; int /*<<< orphan*/  author_date; } ;
struct rev_info {scalar_t__ sort_order; int max_age; struct topo_walk_info* topo_walk_info; } ;
struct commit_list {int /*<<< orphan*/  item; struct commit_list* next; } ;
struct TYPE_2__ {int flags; } ;
struct commit {int date; struct commit_list* parents; TYPE_1__ object; } ;

/* Variables and functions */
 scalar_t__ REV_SORT_BY_AUTHOR_DATE ; 
 int /*<<< orphan*/  TOPO_WALK_EXPLORED ; 
 int UNINTERESTING ; 
 int /*<<< orphan*/  mark_parents_uninteresting (struct commit*) ; 
 scalar_t__ parse_commit_gently (struct commit*,int) ; 
 struct commit* prio_queue_get (int /*<<< orphan*/ *) ; 
 scalar_t__ process_parents (struct rev_info*,struct commit*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  record_author_date (int /*<<< orphan*/ *,struct commit*) ; 
 int /*<<< orphan*/  test_flag_and_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void explore_walk_step(struct rev_info *revs)
{
	struct topo_walk_info *info = revs->topo_walk_info;
	struct commit_list *p;
	struct commit *c = prio_queue_get(&info->explore_queue);

	if (!c)
		return;

	if (parse_commit_gently(c, 1) < 0)
		return;

	if (revs->sort_order == REV_SORT_BY_AUTHOR_DATE)
		record_author_date(&info->author_date, c);

	if (revs->max_age != -1 && (c->date < revs->max_age))
		c->object.flags |= UNINTERESTING;

	if (process_parents(revs, c, NULL, NULL) < 0)
		return;

	if (c->object.flags & UNINTERESTING)
		mark_parents_uninteresting(c);

	for (p = c->parents; p; p = p->next)
		test_flag_and_insert(&info->explore_queue, p->item, TOPO_WALK_EXPLORED);
}