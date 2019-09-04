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
struct TYPE_5__ {int flags; int /*<<< orphan*/  oid; } ;
struct tree {TYPE_1__ object; } ;
struct TYPE_8__ {int nr; TYPE_3__* rev; } ;
struct rev_info {int /*<<< orphan*/  repo; TYPE_4__ cmdline; scalar_t__ edge_hint_aggressive; struct commit_list* commits; } ;
struct oidset {int dummy; } ;
struct object {scalar_t__ type; int flags; } ;
struct commit_list {struct commit* item; struct commit_list* next; } ;
struct TYPE_6__ {int flags; } ;
struct commit {TYPE_2__ object; } ;
typedef  int /*<<< orphan*/  (* show_edge_fn ) (struct commit*) ;
struct TYPE_7__ {struct object* item; } ;

/* Variables and functions */
 scalar_t__ OBJ_COMMIT ; 
 int SHOWN ; 
 int UNINTERESTING ; 
 int /*<<< orphan*/  add_edge_parents (struct commit*,struct rev_info*,int /*<<< orphan*/  (*) (struct commit*),struct oidset*) ; 
 struct tree* get_commit_tree (struct commit*) ; 
 int /*<<< orphan*/  mark_edge_parents_uninteresting (struct commit*,struct rev_info*,int /*<<< orphan*/  (*) (struct commit*)) ; 
 int /*<<< orphan*/  mark_tree_uninteresting (int /*<<< orphan*/ ,struct tree*) ; 
 int /*<<< orphan*/  mark_trees_uninteresting_sparse (int /*<<< orphan*/ ,struct oidset*) ; 
 int /*<<< orphan*/  oidset_clear (struct oidset*) ; 
 int /*<<< orphan*/  oidset_init (struct oidset*,int) ; 
 int /*<<< orphan*/  oidset_insert (struct oidset*,int /*<<< orphan*/ *) ; 

void mark_edges_uninteresting(struct rev_info *revs,
			      show_edge_fn show_edge,
			      int sparse)
{
	struct commit_list *list;
	int i;

	if (sparse) {
		struct oidset set;
		oidset_init(&set, 16);

		for (list = revs->commits; list; list = list->next) {
			struct commit *commit = list->item;
			struct tree *tree = get_commit_tree(commit);

			if (commit->object.flags & UNINTERESTING)
				tree->object.flags |= UNINTERESTING;

			oidset_insert(&set, &tree->object.oid);
			add_edge_parents(commit, revs, show_edge, &set);
		}

		mark_trees_uninteresting_sparse(revs->repo, &set);
		oidset_clear(&set);
	} else {
		for (list = revs->commits; list; list = list->next) {
			struct commit *commit = list->item;
			if (commit->object.flags & UNINTERESTING) {
				mark_tree_uninteresting(revs->repo,
							get_commit_tree(commit));
				if (revs->edge_hint_aggressive && !(commit->object.flags & SHOWN)) {
					commit->object.flags |= SHOWN;
					show_edge(commit);
				}
				continue;
			}
			mark_edge_parents_uninteresting(commit, revs, show_edge);
		}
	}

	if (revs->edge_hint_aggressive) {
		for (i = 0; i < revs->cmdline.nr; i++) {
			struct object *obj = revs->cmdline.rev[i].item;
			struct commit *commit = (struct commit *)obj;
			if (obj->type != OBJ_COMMIT || !(obj->flags & UNINTERESTING))
				continue;
			mark_tree_uninteresting(revs->repo,
						get_commit_tree(commit));
			if (!(obj->flags & SHOWN)) {
				obj->flags |= SHOWN;
				show_edge(commit);
			}
		}
	}
}