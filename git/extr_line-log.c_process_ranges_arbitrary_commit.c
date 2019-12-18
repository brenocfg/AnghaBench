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
struct rev_info {int dummy; } ;
struct line_log_data {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
struct commit {TYPE_2__ object; TYPE_1__* parents; } ;
struct TYPE_3__ {int /*<<< orphan*/  next; } ;

/* Variables and functions */
 int /*<<< orphan*/  TREESAME ; 
 struct line_log_data* lookup_line_range (struct rev_info*,struct commit*) ; 
 int process_ranges_merge_commit (struct rev_info*,struct commit*,struct line_log_data*) ; 
 int process_ranges_ordinary_commit (struct rev_info*,struct commit*,struct line_log_data*) ; 

__attribute__((used)) static int process_ranges_arbitrary_commit(struct rev_info *rev, struct commit *commit)
{
	struct line_log_data *range = lookup_line_range(rev, commit);
	int changed = 0;

	if (range) {
		if (!commit->parents || !commit->parents->next)
			changed = process_ranges_ordinary_commit(rev, commit, range);
		else
			changed = process_ranges_merge_commit(rev, commit, range);
	}

	if (!changed)
		commit->object.flags |= TREESAME;

	return changed;
}