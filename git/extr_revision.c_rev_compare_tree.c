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
struct TYPE_7__ {int /*<<< orphan*/  oid; } ;
struct tree {TYPE_3__ object; } ;
struct TYPE_6__ {scalar_t__ has_changes; } ;
struct TYPE_8__ {TYPE_2__ flags; } ;
struct TYPE_5__ {int /*<<< orphan*/  nr; } ;
struct rev_info {TYPE_4__ pruning; TYPE_1__ prune_data; scalar_t__ simplify_by_decoration; } ;
struct commit {int /*<<< orphan*/  object; } ;

/* Variables and functions */
 int REV_TREE_DIFFERENT ; 
 int REV_TREE_NEW ; 
 int REV_TREE_OLD ; 
 int REV_TREE_SAME ; 
 scalar_t__ diff_tree_oid (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,TYPE_4__*) ; 
 struct tree* get_commit_tree (struct commit*) ; 
 scalar_t__ get_name_decoration (int /*<<< orphan*/ *) ; 
 int tree_difference ; 

__attribute__((used)) static int rev_compare_tree(struct rev_info *revs,
			    struct commit *parent, struct commit *commit)
{
	struct tree *t1 = get_commit_tree(parent);
	struct tree *t2 = get_commit_tree(commit);

	if (!t1)
		return REV_TREE_NEW;
	if (!t2)
		return REV_TREE_OLD;

	if (revs->simplify_by_decoration) {
		/*
		 * If we are simplifying by decoration, then the commit
		 * is worth showing if it has a tag pointing at it.
		 */
		if (get_name_decoration(&commit->object))
			return REV_TREE_DIFFERENT;
		/*
		 * A commit that is not pointed by a tag is uninteresting
		 * if we are not limited by path.  This means that you will
		 * see the usual "commits that touch the paths" plus any
		 * tagged commit by specifying both --simplify-by-decoration
		 * and pathspec.
		 */
		if (!revs->prune_data.nr)
			return REV_TREE_SAME;
	}

	tree_difference = REV_TREE_SAME;
	revs->pruning.flags.has_changes = 0;
	if (diff_tree_oid(&t1->object.oid, &t2->object.oid, "",
			   &revs->pruning) < 0)
		return REV_TREE_DIFFERENT;
	return tree_difference;
}