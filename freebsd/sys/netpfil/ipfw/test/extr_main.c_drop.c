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
struct mbuf {struct mbuf* m_nextpkt; int /*<<< orphan*/  flow_id; } ;
struct list_head {int dummy; } ;
struct TYPE_2__ {int length; struct list_head h; } ;
struct dn_queue {TYPE_1__ ni; } ;
struct cfg_s {int llmask; struct mbuf* freelist; int /*<<< orphan*/ * ll; int /*<<< orphan*/  drop; } ;

/* Variables and functions */
 int BACKLOG ; 
 struct dn_queue* FI2Q (struct cfg_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ND (char*,struct dn_queue*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  list_add_tail (struct list_head*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (struct list_head*) ; 

__attribute__((used)) static int
drop(struct cfg_s *c, struct mbuf *m)
{
	struct dn_queue *q;
	int i;

	c->drop++;
	q = FI2Q(c, m->flow_id);
	i = q->ni.length; // XXX or ffs...

	ND("q %p id %d current length %d", q, m->flow_id, i);
	if (i < BACKLOG) {
		struct list_head *h = &q->ni.h;
		c->llmask &= ~(1<<(i+1));
		c->llmask |= (1<<(i));
		list_del(h);
		list_add_tail(h, &c->ll[i]);
	}
	m->m_nextpkt = c->freelist;
	c->freelist = m;
	return 0;
}