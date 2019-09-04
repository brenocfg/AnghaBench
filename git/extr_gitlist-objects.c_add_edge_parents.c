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
struct TYPE_3__ {int flags; int /*<<< orphan*/  oid; } ;
struct tree {TYPE_1__ object; } ;
struct rev_info {scalar_t__ edge_hint; } ;
struct oidset {int dummy; } ;
struct commit_list {struct commit* item; struct commit_list* next; } ;
struct TYPE_4__ {int flags; } ;
struct commit {TYPE_2__ object; struct commit_list* parents; } ;
typedef  int /*<<< orphan*/  (* show_edge_fn ) (struct commit*) ;

/* Variables and functions */
 int SHOWN ; 
 int UNINTERESTING ; 
 struct tree* get_commit_tree (struct commit*) ; 
 int /*<<< orphan*/  oidset_insert (struct oidset*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void add_edge_parents(struct commit *commit,
			     struct rev_info *revs,
			     show_edge_fn show_edge,
			     struct oidset *set)
{
	struct commit_list *parents;

	for (parents = commit->parents; parents; parents = parents->next) {
		struct commit *parent = parents->item;
		struct tree *tree = get_commit_tree(parent);

		if (!tree)
			continue;

		oidset_insert(set, &tree->object.oid);

		if (!(parent->object.flags & UNINTERESTING))
			continue;
		tree->object.flags |= UNINTERESTING;

		if (revs->edge_hint && !(parent->object.flags & SHOWN)) {
			parent->object.flags |= SHOWN;
			show_edge(parent);
		}
	}
}