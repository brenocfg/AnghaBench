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
struct diff_queue_struct {int nr; struct diff_filepair** queue; } ;
struct diff_filepair {TYPE_2__* two; TYPE_1__* one; scalar_t__ broken_pair; } ;
struct TYPE_4__ {int /*<<< orphan*/  path; } ;
struct TYPE_3__ {int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIFF_QUEUE_CLEAR (struct diff_queue_struct*) ; 
 int /*<<< orphan*/  diff_q (struct diff_queue_struct*,struct diff_filepair*) ; 
 struct diff_queue_struct diff_queued_diff ; 
 int /*<<< orphan*/  free (struct diff_filepair**) ; 
 int /*<<< orphan*/  merge_broken (struct diff_filepair*,struct diff_filepair*,struct diff_queue_struct*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void diffcore_merge_broken(void)
{
	struct diff_queue_struct *q = &diff_queued_diff;
	struct diff_queue_struct outq;
	int i, j;

	DIFF_QUEUE_CLEAR(&outq);

	for (i = 0; i < q->nr; i++) {
		struct diff_filepair *p = q->queue[i];
		if (!p)
			/* we already merged this with its peer */
			continue;
		else if (p->broken_pair &&
			 !strcmp(p->one->path, p->two->path)) {
			/* If the peer also survived rename/copy, then
			 * we merge them back together.
			 */
			for (j = i + 1; j < q->nr; j++) {
				struct diff_filepair *pp = q->queue[j];
				if (pp->broken_pair &&
				    !strcmp(pp->one->path, pp->two->path) &&
				    !strcmp(p->one->path, pp->two->path)) {
					/* Peer survived.  Merge them */
					merge_broken(p, pp, &outq);
					q->queue[j] = NULL;
					goto next;
				}
			}
			/* The peer did not survive, so we keep
			 * it in the output.
			 */
			diff_q(&outq, p);
		}
		else
			diff_q(&outq, p);
next:;
	}
	free(q->queue);
	*q = outq;

	return;
}