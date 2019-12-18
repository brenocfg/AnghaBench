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
struct rr_si {struct rr_queue* head; struct rr_queue* tail; } ;
struct rr_queue {int status; struct rr_queue* qnext; int /*<<< orphan*/  quantum; int /*<<< orphan*/  credit; } ;

/* Variables and functions */

__attribute__((used)) static inline void
rr_append(struct rr_queue *q, struct rr_si *si)
{
	q->status = 1;		/* mark as in-rr_list */
	q->credit = q->quantum;	/* initialize credit */

	/* append to the tail */
	if (si->head == NULL)
		si->head = q;
	else
		si->tail->qnext = q;
	si->tail = q;		/* advance the tail pointer */
	q->qnext = si->head;	/* make it circular */
}