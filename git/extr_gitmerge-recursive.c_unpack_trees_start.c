#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct tree_desc {int dummy; } ;
struct tree {int dummy; } ;
struct index_state {int /*<<< orphan*/  cache_tree; int /*<<< orphan*/ * member_0; } ;
struct TYPE_6__ {int index_only; int update; int merge; int head_idx; int aggressive; struct index_state* src_index; struct index_state* dst_index; int /*<<< orphan*/  fn; } ;
struct merge_options {struct index_state orig_index; TYPE_2__ unpack_opts; TYPE_1__* repo; scalar_t__ call_depth; } ;
struct TYPE_5__ {struct index_state* index; } ;

/* Variables and functions */
 int /*<<< orphan*/  cache_tree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_tree_desc_from_tree (struct tree_desc*,struct tree*) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  merge_detect_rename (struct merge_options*) ; 
 int /*<<< orphan*/  setup_unpack_trees_porcelain (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  threeway_merge ; 
 int unpack_trees (int,struct tree_desc*,TYPE_2__*) ; 

__attribute__((used)) static int unpack_trees_start(struct merge_options *o,
			      struct tree *common,
			      struct tree *head,
			      struct tree *merge)
{
	int rc;
	struct tree_desc t[3];
	struct index_state tmp_index = { NULL };

	memset(&o->unpack_opts, 0, sizeof(o->unpack_opts));
	if (o->call_depth)
		o->unpack_opts.index_only = 1;
	else
		o->unpack_opts.update = 1;
	o->unpack_opts.merge = 1;
	o->unpack_opts.head_idx = 2;
	o->unpack_opts.fn = threeway_merge;
	o->unpack_opts.src_index = o->repo->index;
	o->unpack_opts.dst_index = &tmp_index;
	o->unpack_opts.aggressive = !merge_detect_rename(o);
	setup_unpack_trees_porcelain(&o->unpack_opts, "merge");

	init_tree_desc_from_tree(t+0, common);
	init_tree_desc_from_tree(t+1, head);
	init_tree_desc_from_tree(t+2, merge);

	rc = unpack_trees(3, t, &o->unpack_opts);
	cache_tree_free(&o->repo->index->cache_tree);

	/*
	 * Update o->repo->index to match the new results, AFTER saving a copy
	 * in o->orig_index.  Update src_index to point to the saved copy.
	 * (verify_uptodate() checks src_index, and the original index is
	 * the one that had the necessary modification timestamps.)
	 */
	o->orig_index = *o->repo->index;
	*o->repo->index = tmp_index;
	o->unpack_opts.src_index = &o->orig_index;

	return rc;
}