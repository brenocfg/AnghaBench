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
struct mbuf {int /*<<< orphan*/  flow_id; } ;
struct dn_queue {int dummy; } ;
struct cfg_s {int loops; int (* enq ) (int /*<<< orphan*/ ,struct dn_queue*,struct mbuf*) ;int /*<<< orphan*/  pending; int /*<<< orphan*/  drop; int /*<<< orphan*/  si; struct mbuf* (* deq ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  dequeue; scalar_t__ can_dequeue; int /*<<< orphan*/  _enqueue; struct mbuf* tosend; } ;

/* Variables and functions */
 int /*<<< orphan*/  D (char*,int,...) ; 
 int /*<<< orphan*/  DX (int,char*,int,...) ; 
 struct dn_queue* FI2Q (struct cfg_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ND (char*) ; 
 int /*<<< orphan*/  controller (struct cfg_s*) ; 
 int /*<<< orphan*/  drop (struct cfg_s*,struct mbuf*) ; 
 int /*<<< orphan*/  gnet_stats_deq (struct cfg_s*,struct mbuf*) ; 
 int /*<<< orphan*/  gnet_stats_enq (struct cfg_s*,struct mbuf*) ; 
 int stub1 (int /*<<< orphan*/ ,struct dn_queue*,struct mbuf*) ; 
 struct mbuf* stub2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mainloop(struct cfg_s *c)
{
	int i;
	struct mbuf *m;

	for (i=0; i < c->loops; i++) {
		/* implement histeresis */
		controller(c);
		DX(3, "loop %d enq %d send %p rx %d",
			i, c->_enqueue, c->tosend, c->can_dequeue);
		if ( (m = c->tosend) ) {
			int ret;
			struct dn_queue *q = FI2Q(c, m->flow_id);
			c->_enqueue++;
			ret = c->enq(c->si, q, m);
			if (ret) {
				drop(c, m);
				D("loop %d enqueue fail", i );
				/*
				 * XXX do not insist; rather, try dequeue
				 */
				goto do_dequeue;
			} else {
				ND("enqueue ok");
				c->pending++;
				gnet_stats_enq(c, m);
			}
		} else if (c->can_dequeue) {
do_dequeue:
			c->dequeue++;
			m = c->deq(c->si);
			if (m) {
				c->pending--;
				drop(c, m);
				c->drop--;	/* compensate */
				gnet_stats_deq(c, m);
			} else {
				D("--- ouch, cannot operate on iteration %d, pending %d", i, c->pending);
				break;
			}
		}
	}
	DX(1, "mainloop ends %d", i);
	return 0;
}