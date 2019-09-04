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
struct diff_queue_struct {int nr; struct diff_filepair** queue; } ;
struct TYPE_2__ {int /*<<< orphan*/  no_index; } ;
struct diff_options {int /*<<< orphan*/  skip_stat_unmatch; TYPE_1__ flags; int /*<<< orphan*/  repo; } ;
struct diff_filepair {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIFF_QUEUE_CLEAR (struct diff_queue_struct*) ; 
 scalar_t__ diff_filespec_check_stat_unmatch (int /*<<< orphan*/ ,struct diff_filepair*) ; 
 int /*<<< orphan*/  diff_free_filepair (struct diff_filepair*) ; 
 int /*<<< orphan*/  diff_q (struct diff_queue_struct*,struct diff_filepair*) ; 
 struct diff_queue_struct diff_queued_diff ; 
 int /*<<< orphan*/  free (struct diff_filepair**) ; 

__attribute__((used)) static void diffcore_skip_stat_unmatch(struct diff_options *diffopt)
{
	int i;
	struct diff_queue_struct *q = &diff_queued_diff;
	struct diff_queue_struct outq;
	DIFF_QUEUE_CLEAR(&outq);

	for (i = 0; i < q->nr; i++) {
		struct diff_filepair *p = q->queue[i];

		if (diff_filespec_check_stat_unmatch(diffopt->repo, p))
			diff_q(&outq, p);
		else {
			/*
			 * The caller can subtract 1 from skip_stat_unmatch
			 * to determine how many paths were dirty only
			 * due to stat info mismatch.
			 */
			if (!diffopt->flags.no_index)
				diffopt->skip_stat_unmatch++;
			diff_free_filepair(p);
		}
	}
	free(q->queue);
	*q = outq;
}