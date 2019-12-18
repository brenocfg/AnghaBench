#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  len; } ;
struct mbuf {TYPE_5__ m_pkthdr; struct mbuf* m_nextpkt; } ;
struct TYPE_7__ {scalar_t__ length; } ;
struct TYPE_8__ {int /*<<< orphan*/  q_time; TYPE_1__ ni; } ;
struct fq_pie_si {TYPE_2__ main_q; } ;
struct TYPE_9__ {scalar_t__ accu_prob; } ;
struct TYPE_10__ {struct mbuf* head; } ;
struct fq_pie_flow {TYPE_3__ pst; TYPE_4__ mq; } ;
struct TYPE_12__ {int /*<<< orphan*/  curr_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE_PKT (struct mbuf*) ; 
 TYPE_6__ dn_cfg ; 
 int /*<<< orphan*/  fq_update_stats (struct fq_pie_flow*,struct fq_pie_si*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
pie_drop_head(struct fq_pie_flow *q, struct fq_pie_si *si)
{
	struct mbuf *m = q->mq.head;

	if (m == NULL)
		return;
	q->mq.head = m->m_nextpkt;

	fq_update_stats(q, si, -m->m_pkthdr.len, 1);

	if (si->main_q.ni.length == 0) /* queue is now idle */
			si->main_q.q_time = dn_cfg.curr_time;
	/* reset accu_prob after packet drop */
	q->pst.accu_prob = 0;
	
	FREE_PKT(m);
}