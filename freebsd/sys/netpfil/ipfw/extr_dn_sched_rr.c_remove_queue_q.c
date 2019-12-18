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
struct rr_si {struct rr_queue* tail; struct rr_queue* head; } ;
struct rr_queue {int status; struct rr_queue* qnext; } ;

/* Variables and functions */
 int /*<<< orphan*/  rr_remove_head (struct rr_si*) ; 

__attribute__((used)) static inline void
remove_queue_q(struct rr_queue *q, struct rr_si *si)
{
	struct rr_queue *prev;

	if (q->status != 1)
		return;
	if (q == si->head) {
		rr_remove_head(si);
		return;
	}

	for (prev = si->head; prev; prev = prev->qnext) {
		if (prev->qnext != q)
			continue;
		prev->qnext = q->qnext;
		if (q == si->tail)
			si->tail = prev;
		q->status = 0;
		break;
	}
}