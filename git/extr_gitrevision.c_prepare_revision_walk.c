#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ name; } ;
struct TYPE_6__ {char* name; } ;
struct TYPE_8__ {int /*<<< orphan*/ * objects; scalar_t__ alloc; scalar_t__ nr; } ;
struct rev_info {scalar_t__ no_walk; TYPE_3__ children; scalar_t__ simplify_merges; scalar_t__ line_level_traverse; scalar_t__ topo_order; int /*<<< orphan*/  sort_order; struct commit_list* commits; scalar_t__ limited; scalar_t__ exclude_promisor_objects; TYPE_2__ treesame; TYPE_4__ pending; } ;
struct object_array_entry {int dummy; } ;
struct object_array {int nr; struct object_array_entry* objects; } ;
struct commit_list {int dummy; } ;
struct TYPE_5__ {int flags; } ;
struct commit {TYPE_1__ object; } ;
typedef  int /*<<< orphan*/  old_pending ;

/* Variables and functions */
 int /*<<< orphan*/  FOR_EACH_OBJECT_PROMISOR_ONLY ; 
 scalar_t__ REVISION_WALK_NO_WALK_UNSORTED ; 
 int SEEN ; 
 struct commit_list** commit_list_append (struct commit*,struct commit_list**) ; 
 int /*<<< orphan*/  commit_list_sort_by_date (struct commit_list**) ; 
 int /*<<< orphan*/  for_each_packed_object (int /*<<< orphan*/ ,struct rev_info*,int /*<<< orphan*/ ) ; 
 struct commit* handle_commit (struct rev_info*,struct object_array_entry*) ; 
 int /*<<< orphan*/  init_topo_walk (struct rev_info*) ; 
 scalar_t__ limit_list (struct rev_info*) ; 
 scalar_t__ limiting_can_increase_treesame (struct rev_info*) ; 
 int /*<<< orphan*/  line_log_filter (struct rev_info*) ; 
 int /*<<< orphan*/  mark_uninteresting ; 
 int /*<<< orphan*/  memcpy (struct object_array*,TYPE_4__*,int) ; 
 int /*<<< orphan*/  object_array_clear (struct object_array*) ; 
 int /*<<< orphan*/  set_children (struct rev_info*) ; 
 int /*<<< orphan*/  simplify_merges (struct rev_info*) ; 
 int /*<<< orphan*/  sort_in_topological_order (struct commit_list**,int /*<<< orphan*/ ) ; 

int prepare_revision_walk(struct rev_info *revs)
{
	int i;
	struct object_array old_pending;
	struct commit_list **next = &revs->commits;

	memcpy(&old_pending, &revs->pending, sizeof(old_pending));
	revs->pending.nr = 0;
	revs->pending.alloc = 0;
	revs->pending.objects = NULL;
	for (i = 0; i < old_pending.nr; i++) {
		struct object_array_entry *e = old_pending.objects + i;
		struct commit *commit = handle_commit(revs, e);
		if (commit) {
			if (!(commit->object.flags & SEEN)) {
				commit->object.flags |= SEEN;
				next = commit_list_append(commit, next);
			}
		}
	}
	object_array_clear(&old_pending);

	/* Signal whether we need per-parent treesame decoration */
	if (revs->simplify_merges ||
	    (revs->limited && limiting_can_increase_treesame(revs)))
		revs->treesame.name = "treesame";

	if (revs->exclude_promisor_objects) {
		for_each_packed_object(mark_uninteresting, revs,
				       FOR_EACH_OBJECT_PROMISOR_ONLY);
	}

	if (revs->no_walk != REVISION_WALK_NO_WALK_UNSORTED)
		commit_list_sort_by_date(&revs->commits);
	if (revs->no_walk)
		return 0;
	if (revs->limited) {
		if (limit_list(revs) < 0)
			return -1;
		if (revs->topo_order)
			sort_in_topological_order(&revs->commits, revs->sort_order);
	} else if (revs->topo_order)
		init_topo_walk(revs);
	if (revs->line_level_traverse)
		line_log_filter(revs);
	if (revs->simplify_merges)
		simplify_merges(revs);
	if (revs->children.name)
		set_children(revs);
	return 0;
}