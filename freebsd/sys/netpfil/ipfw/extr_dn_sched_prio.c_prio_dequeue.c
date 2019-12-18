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
struct prio_si {scalar_t__ bitmap; struct dn_queue** q_array; } ;
struct mbuf {int dummy; } ;
struct dn_sch_inst {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * head; } ;
struct dn_queue {TYPE_1__ mq; } ;

/* Variables and functions */
 int /*<<< orphan*/  __clear_bit (int,scalar_t__*) ; 
 struct mbuf* dn_dequeue (struct dn_queue*) ; 
 int ffs (scalar_t__) ; 

__attribute__((used)) static struct mbuf *
prio_dequeue(struct dn_sch_inst *_si)
{
	struct prio_si *si = (struct prio_si *)(_si + 1);
	struct mbuf *m;
	struct dn_queue *q;
	int prio;

	if (si->bitmap == 0) /* scheduler idle */
		return NULL;

	prio = ffs(si->bitmap) - 1;

	/* Take the highest priority queue in the scheduler */
	q = si->q_array[prio];
	// assert(q)

	m = dn_dequeue(q);
	if (q->mq.head == NULL) {
		/* Queue is now empty, remove from scheduler
		 * and mark it
		 */
		si->q_array[prio] = NULL;
		__clear_bit(prio, &si->bitmap);
	}
	return m;
}