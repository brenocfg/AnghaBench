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
typedef  int /*<<< orphan*/  uint64_t ;
struct qfq_sched {int /*<<< orphan*/ * bitmaps; } ;
struct qfq_group {int /*<<< orphan*/  F; } ;

/* Variables and functions */
 int /*<<< orphan*/  EB ; 
 size_t ER ; 
 int /*<<< orphan*/  IB ; 
 size_t IR ; 
 unsigned long mask_from (int /*<<< orphan*/ ,int) ; 
 struct qfq_group* qfq_ffs (struct qfq_sched*,unsigned long) ; 
 int /*<<< orphan*/  qfq_gt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qfq_move_groups (struct qfq_sched*,unsigned long,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static inline void
qfq_unblock_groups(struct qfq_sched *q, int index, uint64_t old_finish)
{
	unsigned long mask = mask_from(q->bitmaps[ER], index + 1);
	struct qfq_group *next;

	if (mask) {
		next = qfq_ffs(q, mask);
		if (!qfq_gt(next->F, old_finish))
			return;
	}

	mask = (1UL << index) - 1;
	qfq_move_groups(q, mask, EB, ER);
	qfq_move_groups(q, mask, IB, IR);
}