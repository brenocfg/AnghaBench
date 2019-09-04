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
struct diff_queue_struct {int nr; struct diff_filepair** queue; } ;
struct diff_options {int /*<<< orphan*/  filter; } ;
struct diff_filepair {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIFF_QUEUE_CLEAR (struct diff_queue_struct*) ; 
 int /*<<< orphan*/  DIFF_STATUS_FILTER_AON ; 
 int /*<<< orphan*/  diff_free_filepair (struct diff_filepair*) ; 
 int /*<<< orphan*/  diff_q (struct diff_queue_struct*,struct diff_filepair*) ; 
 struct diff_queue_struct diff_queued_diff ; 
 scalar_t__ filter_bit_tst (int /*<<< orphan*/ ,struct diff_options*) ; 
 int /*<<< orphan*/  free (struct diff_filepair**) ; 
 scalar_t__ match_filter (struct diff_options*,struct diff_filepair*) ; 

__attribute__((used)) static void diffcore_apply_filter(struct diff_options *options)
{
	int i;
	struct diff_queue_struct *q = &diff_queued_diff;
	struct diff_queue_struct outq;

	DIFF_QUEUE_CLEAR(&outq);

	if (!options->filter)
		return;

	if (filter_bit_tst(DIFF_STATUS_FILTER_AON, options)) {
		int found;
		for (i = found = 0; !found && i < q->nr; i++) {
			if (match_filter(options, q->queue[i]))
				found++;
		}
		if (found)
			return;

		/* otherwise we will clear the whole queue
		 * by copying the empty outq at the end of this
		 * function, but first clear the current entries
		 * in the queue.
		 */
		for (i = 0; i < q->nr; i++)
			diff_free_filepair(q->queue[i]);
	}
	else {
		/* Only the matching ones */
		for (i = 0; i < q->nr; i++) {
			struct diff_filepair *p = q->queue[i];
			if (match_filter(options, p))
				diff_q(&outq, p);
			else
				diff_free_filepair(p);
		}
	}
	free(q->queue);
	*q = outq;
}