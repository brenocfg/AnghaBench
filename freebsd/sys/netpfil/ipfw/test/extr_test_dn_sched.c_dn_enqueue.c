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
struct TYPE_3__ {scalar_t__ len; } ;
struct mbuf {TYPE_1__ m_pkthdr; } ;
struct TYPE_4__ {int length; int /*<<< orphan*/  drops; int /*<<< orphan*/  tot_pkts; int /*<<< orphan*/  tot_bytes; } ;
struct dn_queue {TYPE_2__ ni; int /*<<< orphan*/  mq; } ;

/* Variables and functions */
 int /*<<< orphan*/  mq_append (int /*<<< orphan*/ *,struct mbuf*) ; 

int
dn_enqueue(struct dn_queue *q, struct mbuf* m, int drop)
{
        if (drop)
                goto drop;
        if (q->ni.length >= 200)
                goto drop;
        mq_append(&q->mq, m);
        q->ni.length++;
        q->ni.tot_bytes += m->m_pkthdr.len;
        q->ni.tot_pkts++;
        return 0;

drop:
        q->ni.drops++;
        return 1;
}