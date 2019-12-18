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
struct topo_walk_info {int /*<<< orphan*/  indegree_queue; int /*<<< orphan*/  indegree; } ;
struct rev_info {scalar_t__ first_parent_only; struct topo_walk_info* topo_walk_info; } ;
struct commit_list {struct commit* item; struct commit_list* next; } ;
struct commit {struct commit_list* parents; int /*<<< orphan*/  generation; } ;

/* Variables and functions */
 int /*<<< orphan*/  TOPO_WALK_INDEGREE ; 
 int /*<<< orphan*/  explore_to_depth (struct rev_info*,int /*<<< orphan*/ ) ; 
 int* indegree_slab_at (int /*<<< orphan*/ *,struct commit*) ; 
 scalar_t__ parse_commit_gently (struct commit*,int) ; 
 struct commit* prio_queue_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_flag_and_insert (int /*<<< orphan*/ *,struct commit*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void indegree_walk_step(struct rev_info *revs)
{
	struct commit_list *p;
	struct topo_walk_info *info = revs->topo_walk_info;
	struct commit *c = prio_queue_get(&info->indegree_queue);

	if (!c)
		return;

	if (parse_commit_gently(c, 1) < 0)
		return;

	explore_to_depth(revs, c->generation);

	for (p = c->parents; p; p = p->next) {
		struct commit *parent = p->item;
		int *pi = indegree_slab_at(&info->indegree, parent);

		if (*pi)
			(*pi)++;
		else
			*pi = 2;

		test_flag_and_insert(&info->indegree_queue, parent, TOPO_WALK_INDEGREE);

		if (revs->first_parent_only)
			return;
	}
}