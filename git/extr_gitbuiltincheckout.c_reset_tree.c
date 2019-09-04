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
struct unpack_trees_options {int head_idx; int update; int skip_unmerged; int reset; int merge; int /*<<< orphan*/ * dst_index; int /*<<< orphan*/ * src_index; int /*<<< orphan*/  verbose_update; int /*<<< orphan*/  fn; } ;
struct tree_desc {int dummy; } ;
struct tree {int /*<<< orphan*/  size; int /*<<< orphan*/  buffer; } ;
struct checkout_opts {int /*<<< orphan*/  show_progress; } ;
typedef  int /*<<< orphan*/  opts ;

/* Variables and functions */
 int /*<<< orphan*/  init_tree_desc (struct tree_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct unpack_trees_options*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  oneway_merge ; 
 int /*<<< orphan*/  parse_tree (struct tree*) ; 
 int /*<<< orphan*/  the_index ; 
 int unpack_trees (int,struct tree_desc*,struct unpack_trees_options*) ; 

__attribute__((used)) static int reset_tree(struct tree *tree, const struct checkout_opts *o,
		      int worktree, int *writeout_error)
{
	struct unpack_trees_options opts;
	struct tree_desc tree_desc;

	memset(&opts, 0, sizeof(opts));
	opts.head_idx = -1;
	opts.update = worktree;
	opts.skip_unmerged = !worktree;
	opts.reset = 1;
	opts.merge = 1;
	opts.fn = oneway_merge;
	opts.verbose_update = o->show_progress;
	opts.src_index = &the_index;
	opts.dst_index = &the_index;
	parse_tree(tree);
	init_tree_desc(&tree_desc, tree->buffer, tree->size);
	switch (unpack_trees(1, &tree_desc, &opts)) {
	case -2:
		*writeout_error = 1;
		/*
		 * We return 0 nevertheless, as the index is all right
		 * and more importantly we have made best efforts to
		 * update paths in the work tree, and we cannot revert
		 * them.
		 */
		/* fallthrough */
	case 0:
		return 0;
	default:
		return 128;
	}
}