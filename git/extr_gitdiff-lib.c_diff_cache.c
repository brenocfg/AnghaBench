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
struct unpack_trees_options {int head_idx; int index_only; int diff_index_cached; int merge; TYPE_4__* pathspec; int /*<<< orphan*/ * dst_index; int /*<<< orphan*/  src_index; struct rev_info* unpack_data; int /*<<< orphan*/  fn; } ;
struct tree_desc {int dummy; } ;
struct tree {int /*<<< orphan*/  size; int /*<<< orphan*/  buffer; } ;
struct TYPE_8__ {int recursive; } ;
struct TYPE_5__ {int /*<<< orphan*/  find_copies_harder; } ;
struct TYPE_7__ {TYPE_4__ pathspec; TYPE_2__* repo; TYPE_1__ flags; } ;
struct rev_info {TYPE_3__ diffopt; } ;
struct object_id {int dummy; } ;
typedef  int /*<<< orphan*/  opts ;
struct TYPE_6__ {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int error (char*,char const*) ; 
 int /*<<< orphan*/  init_tree_desc (struct tree_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct unpack_trees_options*,int /*<<< orphan*/ ,int) ; 
 char const* oid_to_hex (struct object_id const*) ; 
 int /*<<< orphan*/  oneway_diff ; 
 struct tree* parse_tree_indirect (struct object_id const*) ; 
 int unpack_trees (int,struct tree_desc*,struct unpack_trees_options*) ; 

__attribute__((used)) static int diff_cache(struct rev_info *revs,
		      const struct object_id *tree_oid,
		      const char *tree_name,
		      int cached)
{
	struct tree *tree;
	struct tree_desc t;
	struct unpack_trees_options opts;

	tree = parse_tree_indirect(tree_oid);
	if (!tree)
		return error("bad tree object %s",
			     tree_name ? tree_name : oid_to_hex(tree_oid));
	memset(&opts, 0, sizeof(opts));
	opts.head_idx = 1;
	opts.index_only = cached;
	opts.diff_index_cached = (cached &&
				  !revs->diffopt.flags.find_copies_harder);
	opts.merge = 1;
	opts.fn = oneway_diff;
	opts.unpack_data = revs;
	opts.src_index = revs->diffopt.repo->index;
	opts.dst_index = NULL;
	opts.pathspec = &revs->diffopt.pathspec;
	opts.pathspec->recursive = 1;

	init_tree_desc(&t, tree->buffer, tree->size);
	return unpack_trees(1, &t, &opts);
}