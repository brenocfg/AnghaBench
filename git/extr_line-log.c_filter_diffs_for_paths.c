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
struct line_log_data {int /*<<< orphan*/  path; struct line_log_data* next; } ;
struct diff_queue_struct {int nr; struct diff_filepair** queue; } ;
struct diff_filepair {TYPE_1__* two; } ;
struct TYPE_2__ {int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIFF_FILE_VALID (TYPE_1__*) ; 
 int /*<<< orphan*/  DIFF_QUEUE_CLEAR (struct diff_queue_struct*) ; 
 int /*<<< orphan*/  diff_free_filepair (struct diff_filepair*) ; 
 int /*<<< orphan*/  diff_q (struct diff_queue_struct*,struct diff_filepair*) ; 
 struct diff_queue_struct diff_queued_diff ; 
 int /*<<< orphan*/  free (struct diff_filepair**) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void filter_diffs_for_paths(struct line_log_data *range, int keep_deletions)
{
	int i;
	struct diff_queue_struct outq;
	DIFF_QUEUE_CLEAR(&outq);

	for (i = 0; i < diff_queued_diff.nr; i++) {
		struct diff_filepair *p = diff_queued_diff.queue[i];
		struct line_log_data *rg = NULL;

		if (!DIFF_FILE_VALID(p->two)) {
			if (keep_deletions)
				diff_q(&outq, p);
			else
				diff_free_filepair(p);
			continue;
		}
		for (rg = range; rg; rg = rg->next) {
			if (!strcmp(rg->path, p->two->path))
				break;
		}
		if (rg)
			diff_q(&outq, p);
		else
			diff_free_filepair(p);
	}
	free(diff_queued_diff.queue);
	diff_queued_diff = outq;
}