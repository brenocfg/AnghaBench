#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct tree {int /*<<< orphan*/  object; } ;
struct TYPE_6__ {int ignore_submodules; int quick; } ;
struct TYPE_9__ {TYPE_1__ flags; } ;
struct TYPE_7__ {int /*<<< orphan*/  nr; } ;
struct rev_info {TYPE_4__ diffopt; TYPE_2__ pending; } ;
struct repository {int /*<<< orphan*/  index; } ;
struct TYPE_8__ {int /*<<< orphan*/  empty_tree; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_head_to_pending (struct rev_info*) ; 
 int /*<<< orphan*/  add_pending_object (struct rev_info*,int /*<<< orphan*/ *,char*) ; 
 int diff_result_code (TYPE_4__*,int) ; 
 int /*<<< orphan*/  diff_setup_done (TYPE_4__*) ; 
 scalar_t__ is_index_unborn (int /*<<< orphan*/ ) ; 
 struct tree* lookup_tree (struct repository*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  repo_init_revisions (struct repository*,struct rev_info*,int /*<<< orphan*/ *) ; 
 int run_diff_index (struct rev_info*,int) ; 
 TYPE_3__* the_hash_algo ; 

int has_uncommitted_changes(struct repository *r,
			    int ignore_submodules)
{
	struct rev_info rev_info;
	int result;

	if (is_index_unborn(r->index))
		return 0;

	repo_init_revisions(r, &rev_info, NULL);
	if (ignore_submodules)
		rev_info.diffopt.flags.ignore_submodules = 1;
	rev_info.diffopt.flags.quick = 1;

	add_head_to_pending(&rev_info);
	if (!rev_info.pending.nr) {
		/*
		 * We have no head (or it's corrupt); use the empty tree,
		 * which will complain if the index is non-empty.
		 */
		struct tree *tree = lookup_tree(r, the_hash_algo->empty_tree);
		add_pending_object(&rev_info, &tree->object, "");
	}

	diff_setup_done(&rev_info.diffopt);
	result = run_diff_index(&rev_info, 1);
	return diff_result_code(&rev_info.diffopt, result);
}