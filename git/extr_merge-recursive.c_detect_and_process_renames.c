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
struct tree {int dummy; } ;
struct string_list {int dummy; } ;
struct rename_info {int /*<<< orphan*/ * merge_renames; int /*<<< orphan*/ * head_renames; } ;
struct merge_options {scalar_t__ detect_directory_renames; int /*<<< orphan*/  branch2; int /*<<< orphan*/  branch1; TYPE_1__* priv; } ;
struct hashmap {int dummy; } ;
struct diff_queue_struct {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  call_depth; } ;

/* Variables and functions */
 scalar_t__ MERGE_DIRECTORY_RENAMES_CONFLICT ; 
 scalar_t__ MERGE_DIRECTORY_RENAMES_TRUE ; 
 int /*<<< orphan*/  dir_rename_init (struct hashmap*) ; 
 struct diff_queue_struct* get_diffpairs (struct merge_options*,struct tree*,struct tree*) ; 
 struct hashmap* get_directory_renames (struct diff_queue_struct*) ; 
 void* get_renames (struct merge_options*,int /*<<< orphan*/ ,struct diff_queue_struct*,struct hashmap*,struct hashmap*,struct tree*,struct tree*,struct tree*,struct tree*,struct string_list*,int*) ; 
 int /*<<< orphan*/  handle_directory_level_conflicts (struct merge_options*,struct hashmap*,struct tree*,struct hashmap*,struct tree*) ; 
 int /*<<< orphan*/  initial_cleanup_rename (struct diff_queue_struct*,struct hashmap*) ; 
 int /*<<< orphan*/  merge_detect_rename (struct merge_options*) ; 
 int process_renames (struct merge_options*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct hashmap* xmalloc (int) ; 

__attribute__((used)) static int detect_and_process_renames(struct merge_options *opt,
				      struct tree *common,
				      struct tree *head,
				      struct tree *merge,
				      struct string_list *entries,
				      struct rename_info *ri)
{
	struct diff_queue_struct *head_pairs, *merge_pairs;
	struct hashmap *dir_re_head, *dir_re_merge;
	int clean = 1;

	ri->head_renames = NULL;
	ri->merge_renames = NULL;

	if (!merge_detect_rename(opt))
		return 1;

	head_pairs = get_diffpairs(opt, common, head);
	merge_pairs = get_diffpairs(opt, common, merge);

	if ((opt->detect_directory_renames == MERGE_DIRECTORY_RENAMES_TRUE) ||
	    (opt->detect_directory_renames == MERGE_DIRECTORY_RENAMES_CONFLICT &&
	     !opt->priv->call_depth)) {
		dir_re_head = get_directory_renames(head_pairs);
		dir_re_merge = get_directory_renames(merge_pairs);

		handle_directory_level_conflicts(opt,
						 dir_re_head, head,
						 dir_re_merge, merge);
	} else {
		dir_re_head  = xmalloc(sizeof(*dir_re_head));
		dir_re_merge = xmalloc(sizeof(*dir_re_merge));
		dir_rename_init(dir_re_head);
		dir_rename_init(dir_re_merge);
	}

	ri->head_renames  = get_renames(opt, opt->branch1, head_pairs,
					dir_re_merge, dir_re_head, head,
					common, head, merge, entries,
					&clean);
	if (clean < 0)
		goto cleanup;
	ri->merge_renames = get_renames(opt, opt->branch2, merge_pairs,
					dir_re_head, dir_re_merge, merge,
					common, head, merge, entries,
					&clean);
	if (clean < 0)
		goto cleanup;
	clean &= process_renames(opt, ri->head_renames, ri->merge_renames);

cleanup:
	/*
	 * Some cleanup is deferred until cleanup_renames() because the
	 * data structures are still needed and referenced in
	 * process_entry().  But there are a few things we can free now.
	 */
	initial_cleanup_rename(head_pairs, dir_re_head);
	initial_cleanup_rename(merge_pairs, dir_re_merge);

	return clean;
}