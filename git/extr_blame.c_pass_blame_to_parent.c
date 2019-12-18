#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct blame_scoreboard {int /*<<< orphan*/  xdl_opts; int /*<<< orphan*/  num_get_patch; int /*<<< orphan*/  num_read_blob; TYPE_1__* revs; } ;
struct blame_origin {TYPE_3__* commit; int /*<<< orphan*/  suspects; } ;
struct blame_entry {int dummy; } ;
struct blame_chunk_cb_data {int ignore_diffs; struct blame_entry** dstq; scalar_t__ offset; int /*<<< orphan*/ * srcq; struct blame_origin* target; struct blame_origin* parent; } ;
typedef  int /*<<< orphan*/  mmfile_t ;
struct TYPE_5__ {int /*<<< orphan*/  oid; } ;
struct TYPE_6__ {TYPE_2__ object; } ;
struct TYPE_4__ {int /*<<< orphan*/  diffopt; } ;

/* Variables and functions */
 int /*<<< orphan*/  INT_MAX ; 
 int /*<<< orphan*/  blame_chunk (struct blame_entry***,int /*<<< orphan*/ **,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct blame_origin*,struct blame_origin*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blame_chunk_cb ; 
 int /*<<< orphan*/  compare_blame_suspect ; 
 int /*<<< orphan*/  die (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ diff_hunks (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct blame_chunk_cb_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fill_origin_blob (int /*<<< orphan*/ *,struct blame_origin*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  get_next_blame ; 
 struct blame_entry* llist_mergesort (struct blame_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oid_to_hex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_blames (struct blame_scoreboard*,struct blame_origin*,struct blame_entry*) ; 
 int /*<<< orphan*/  set_next_blame ; 

__attribute__((used)) static void pass_blame_to_parent(struct blame_scoreboard *sb,
				 struct blame_origin *target,
				 struct blame_origin *parent, int ignore_diffs)
{
	mmfile_t file_p, file_o;
	struct blame_chunk_cb_data d;
	struct blame_entry *newdest = NULL;

	if (!target->suspects)
		return; /* nothing remains for this target */

	d.parent = parent;
	d.target = target;
	d.offset = 0;
	d.ignore_diffs = ignore_diffs;
	d.dstq = &newdest; d.srcq = &target->suspects;

	fill_origin_blob(&sb->revs->diffopt, parent, &file_p,
			 &sb->num_read_blob, ignore_diffs);
	fill_origin_blob(&sb->revs->diffopt, target, &file_o,
			 &sb->num_read_blob, ignore_diffs);
	sb->num_get_patch++;

	if (diff_hunks(&file_p, &file_o, blame_chunk_cb, &d, sb->xdl_opts))
		die("unable to generate diff (%s -> %s)",
		    oid_to_hex(&parent->commit->object.oid),
		    oid_to_hex(&target->commit->object.oid));
	/* The rest are the same as the parent */
	blame_chunk(&d.dstq, &d.srcq, INT_MAX, d.offset, INT_MAX, 0,
		    parent, target, 0);
	*d.dstq = NULL;
	if (ignore_diffs)
		newdest = llist_mergesort(newdest, get_next_blame,
					  set_next_blame,
					  compare_blame_suspect);
	queue_blames(sb, parent, newdest);

	return;
}