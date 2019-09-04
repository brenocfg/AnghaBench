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
struct line_log_data {int dummy; } ;
struct diff_queue_struct {int dummy; } ;
struct diff_options {scalar_t__ detect_rename; } ;
struct commit {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIFF_QUEUE_CLEAR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (struct commit*) ; 
 scalar_t__ diff_might_be_rename () ; 
 int /*<<< orphan*/  diff_queued_diff ; 
 int /*<<< orphan*/  diff_tree_oid (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,struct diff_options*) ; 
 int /*<<< orphan*/  diffcore_std (struct diff_options*) ; 
 int /*<<< orphan*/  filter_diffs_for_paths (struct line_log_data*,int) ; 
 int /*<<< orphan*/ * get_commit_tree_oid (struct commit*) ; 
 int /*<<< orphan*/  move_diff_queue (struct diff_queue_struct*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void queue_diffs(struct line_log_data *range,
			struct diff_options *opt,
			struct diff_queue_struct *queue,
			struct commit *commit, struct commit *parent)
{
	assert(commit);

	DIFF_QUEUE_CLEAR(&diff_queued_diff);
	diff_tree_oid(parent ? get_commit_tree_oid(parent) : NULL,
		      get_commit_tree_oid(commit), "", opt);
	if (opt->detect_rename) {
		filter_diffs_for_paths(range, 1);
		if (diff_might_be_rename())
			diffcore_std(opt);
		filter_diffs_for_paths(range, 0);
	}
	move_diff_queue(queue, &diff_queued_diff);
}