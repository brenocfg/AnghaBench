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
struct unpack_trees_options {int head_idx; int index_only; int merge; int /*<<< orphan*/  fn; int /*<<< orphan*/ * dst_index; int /*<<< orphan*/ * src_index; } ;
struct tree_desc {int dummy; } ;
struct tree {int /*<<< orphan*/  size; int /*<<< orphan*/  buffer; } ;
struct TYPE_2__ {int /*<<< orphan*/  oid; } ;
struct commit {TYPE_1__ object; } ;
typedef  int /*<<< orphan*/  opts ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  discard_cache () ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  init_tree_desc (struct tree_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct unpack_trees_options*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  oneway_merge ; 
 int /*<<< orphan*/  parse_tree (struct tree*) ; 
 struct tree* parse_tree_indirect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  the_index ; 
 scalar_t__ unpack_trees (int,struct tree_desc*,struct unpack_trees_options*) ; 

__attribute__((used)) static void create_base_index(const struct commit *current_head)
{
	struct tree *tree;
	struct unpack_trees_options opts;
	struct tree_desc t;

	if (!current_head) {
		discard_cache();
		return;
	}

	memset(&opts, 0, sizeof(opts));
	opts.head_idx = 1;
	opts.index_only = 1;
	opts.merge = 1;
	opts.src_index = &the_index;
	opts.dst_index = &the_index;

	opts.fn = oneway_merge;
	tree = parse_tree_indirect(&current_head->object.oid);
	if (!tree)
		die(_("failed to unpack HEAD tree object"));
	parse_tree(tree);
	init_tree_desc(&t, tree->buffer, tree->size);
	if (unpack_trees(1, &t, &opts))
		exit(128); /* We've already reported the error, finish dying */
}