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
struct rev_info {int dummy; } ;
struct line_log_data {int /*<<< orphan*/  diff; int /*<<< orphan*/  pair; struct line_log_data* next; int /*<<< orphan*/  path; } ;
struct diff_ranges {int dummy; } ;
struct diff_queue_struct {int nr; struct diff_filepair** queue; } ;
struct diff_filepair {TYPE_1__* two; } ;
struct TYPE_2__ {int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (struct line_log_data*) ; 
 int /*<<< orphan*/  diff_filepair_dup (struct diff_filepair*) ; 
 int /*<<< orphan*/  free (struct diff_ranges*) ; 
 struct line_log_data* line_log_data_copy (struct line_log_data*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct diff_ranges*,int) ; 
 scalar_t__ process_diff_filepair (struct rev_info*,struct diff_filepair*,struct line_log_data*,struct diff_ranges**) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int process_all_files(struct line_log_data **range_out,
			     struct rev_info *rev,
			     struct diff_queue_struct *queue,
			     struct line_log_data *range)
{
	int i, changed = 0;

	*range_out = line_log_data_copy(range);

	for (i = 0; i < queue->nr; i++) {
		struct diff_ranges *pairdiff = NULL;
		struct diff_filepair *pair = queue->queue[i];
		if (process_diff_filepair(rev, pair, *range_out, &pairdiff)) {
			/*
			 * Store away the diff for later output.  We
			 * tuck it in the ranges we got as _input_,
			 * since that's the commit that caused the
			 * diff.
			 *
			 * NEEDSWORK not enough when we get around to
			 * doing something interesting with merges;
			 * currently each invocation on a merge parent
			 * trashes the previous one's diff.
			 *
			 * NEEDSWORK tramples over data structures not owned here
			 */
			struct line_log_data *rg = range;
			changed++;
			while (rg && strcmp(rg->path, pair->two->path))
				rg = rg->next;
			assert(rg);
			rg->pair = diff_filepair_dup(queue->queue[i]);
			memcpy(&rg->diff, pairdiff, sizeof(struct diff_ranges));
		}
		free(pairdiff);
	}

	return changed;
}