#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct mbuf {int dummy; } ;
struct TYPE_6__ {scalar_t__ sched; } ;
struct fq_pie_si {int /*<<< orphan*/  newflows; TYPE_2__ _si; TYPE_1__* si_extra; } ;
struct dn_sch_fq_pie_parms {int flows_cnt; scalar_t__ limit; int /*<<< orphan*/  quantum; } ;
struct fq_pie_schk {struct dn_sch_fq_pie_parms cfg; } ;
struct TYPE_8__ {scalar_t__ length; } ;
struct fq_pie_flow {int active; TYPE_4__ stats; int /*<<< orphan*/  deficit; } ;
struct dn_sch_inst {int dummy; } ;
struct TYPE_7__ {scalar_t__ length; } ;
struct dn_queue {TYPE_3__ ni; } ;
struct TYPE_5__ {struct fq_pie_flow* flows; } ;

/* Variables and functions */
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct fq_pie_flow*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flowchain ; 
 int /*<<< orphan*/  fq_activate_pie (struct fq_pie_flow*) ; 
 int fq_pie_classify_flow (struct mbuf*,int,struct fq_pie_si*) ; 
 int /*<<< orphan*/  pie_drop_head (struct fq_pie_flow*,struct fq_pie_si*) ; 
 int pie_enqueue (struct fq_pie_flow*,struct mbuf*,struct fq_pie_si*) ; 

__attribute__((used)) static int 
fq_pie_enqueue(struct dn_sch_inst *_si, struct dn_queue *_q, 
	struct mbuf *m)
{ 
	struct fq_pie_si *si;
	struct fq_pie_schk *schk;
	struct dn_sch_fq_pie_parms *param;
	struct dn_queue *mainq;
	struct fq_pie_flow *flows;
	int idx, drop, i, maxidx;

	mainq = (struct dn_queue *)(_si + 1);
	si = (struct fq_pie_si *)_si;
	flows = si->si_extra->flows;
	schk = (struct fq_pie_schk *)(si->_si.sched+1);
	param = &schk->cfg;

	 /* classify a packet to queue number*/
	idx = fq_pie_classify_flow(m, param->flows_cnt, si);

	/* enqueue packet into appropriate queue using PIE AQM.
	 * Note: 'pie_enqueue' function returns 1 only when it unable to 
	 * add timestamp to packet (no limit check)*/
	drop = pie_enqueue(&flows[idx], m, si);
	
	/* pie unable to timestamp a packet */ 
	if (drop)
		return 1;
	
	/* If the flow (sub-queue) is not active ,then add it to tail of
	 * new flows list, initialize and activate it.
	 */
	if (!flows[idx].active) {
		STAILQ_INSERT_TAIL(&si->newflows, &flows[idx], flowchain);
		flows[idx].deficit = param->quantum;
		fq_activate_pie(&flows[idx]);
		flows[idx].active = 1;
	}

	/* check the limit for all queues and remove a packet from the
	 * largest one 
	 */
	if (mainq->ni.length > schk->cfg.limit) {
		/* find first active flow */
		for (maxidx = 0; maxidx < schk->cfg.flows_cnt; maxidx++)
			if (flows[maxidx].active)
				break;
		if (maxidx < schk->cfg.flows_cnt) {
			/* find the largest sub- queue */
			for (i = maxidx + 1; i < schk->cfg.flows_cnt; i++) 
				if (flows[i].active && flows[i].stats.length >
					flows[maxidx].stats.length)
					maxidx = i;
			pie_drop_head(&flows[maxidx], si);
			drop = 1;
		}
	}

	return drop;
}