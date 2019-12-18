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
struct qfq_sched {int wsum; int iwsum; } ;
struct qfq_class {int inv_w; } ;
struct dn_queue {scalar_t__ _si; } ;

/* Variables and functions */
 int ONE_FP ; 

__attribute__((used)) static int
qfq_free_queue(struct dn_queue *_q)
{
	struct qfq_sched *q = (struct qfq_sched *)(_q->_si + 1);
	struct qfq_class *cl = (struct qfq_class *)_q;
	if (cl->inv_w) {
		q->wsum -= ONE_FP/cl->inv_w;
		if (q->wsum != 0)
			q->iwsum = ONE_FP / q->wsum;
		cl->inv_w = 0; /* reset weight to avoid run twice */
	}
	return 0;
}