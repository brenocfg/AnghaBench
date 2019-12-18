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
struct qfq_sched {int /*<<< orphan*/ * bitmaps; int /*<<< orphan*/  V; } ;
struct qfq_group {int /*<<< orphan*/  F; int /*<<< orphan*/  index; int /*<<< orphan*/  S; } ;

/* Variables and functions */
 unsigned int EB ; 
 size_t ER ; 
 unsigned long mask_from (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct qfq_group* qfq_ffs (struct qfq_sched*,unsigned long) ; 
 unsigned int qfq_gt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline unsigned int
qfq_calc_state(struct qfq_sched *q, struct qfq_group *grp)
{
	/* if S > V we are not eligible */
	unsigned int state = qfq_gt(grp->S, q->V);
	unsigned long mask = mask_from(q->bitmaps[ER], grp->index);
	struct qfq_group *next;

	if (mask) {
		next = qfq_ffs(q, mask);
		if (qfq_gt(grp->F, next->F))
			state |= EB;
	}

	return state;
}