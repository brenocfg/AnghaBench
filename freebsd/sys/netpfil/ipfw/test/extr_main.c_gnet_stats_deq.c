#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int len; } ;
struct mbuf {size_t flow_id; TYPE_1__ m_pkthdr; } ;
struct TYPE_7__ {int bytes; } ;
struct dn_sch_inst {TYPE_2__ ni; } ;
struct TYPE_8__ {int bytes; scalar_t__ length; double sch_bytes; } ;
struct dn_queue {TYPE_5__* fs; TYPE_3__ ni; } ;
struct cfg_s {double wsum; double* q_wfi; struct dn_sch_inst* si; } ;
struct TYPE_9__ {scalar_t__* par; } ;
struct TYPE_10__ {TYPE_4__ fs; } ;

/* Variables and functions */
 struct dn_queue* FI2Q (struct cfg_s*,size_t) ; 

__attribute__((used)) static void
gnet_stats_deq(struct cfg_s *c, struct mbuf *mb)
{
	struct dn_sch_inst *si = c->si;
	struct dn_queue *_q = FI2Q(c, mb->flow_id);
	int len = mb->m_pkthdr.len;

	_q->ni.bytes += len;
	si->ni.bytes += len;

	if (_q->ni.length == 0) {
		double bytes = (double)_q->ni.bytes;
		double sch_bytes = (double)si->ni.bytes - _q->ni.sch_bytes;
		double weight = (double)_q->fs->fs.par[0] / c->wsum;
		double wfi = sch_bytes * weight - bytes;

		if (c->q_wfi[mb->flow_id] < wfi)
			c->q_wfi[mb->flow_id] = wfi;
	}
}