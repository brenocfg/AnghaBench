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
struct rr_si {int dummy; } ;
struct rr_queue {int status; } ;
struct mbuf {int dummy; } ;
struct dn_sch_inst {int dummy; } ;
struct TYPE_2__ {struct mbuf* head; } ;
struct dn_queue {TYPE_1__ mq; } ;

/* Variables and functions */
 scalar_t__ dn_enqueue (struct dn_queue*,struct mbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rr_append (struct rr_queue*,struct rr_si*) ; 

__attribute__((used)) static int
rr_enqueue(struct dn_sch_inst *_si, struct dn_queue *q, struct mbuf *m)
{
	struct rr_si *si;
	struct rr_queue *rrq;

	if (m != q->mq.head) {
		if (dn_enqueue(q, m, 0)) /* packet was dropped */
			return 1;
		if (m != q->mq.head)
			return 0;
	}

	/* If reach this point, queue q was idle */
	si = (struct rr_si *)(_si + 1);
	rrq = (struct rr_queue *)q;

	if (rrq->status == 1) /* Queue is already in the queue list */
		return 0;

	/* Insert the queue in the queue list */
	rr_append(rrq, si);

	return 0;
}