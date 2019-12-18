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
typedef  int u64 ;
typedef  size_t u32 ;
struct rmid_read {int /*<<< orphan*/  evtid; TYPE_1__* d; } ;
struct rdt_resource {int mon_scale; } ;
struct mbm_state {int prev_bw_msr; int chunks_bw; int chunks; int delta_comp; int prev_bw; int /*<<< orphan*/  delta_bw; } ;
struct TYPE_2__ {struct mbm_state* mbm_local; } ;

/* Variables and functions */
 size_t RDT_RESOURCE_L3 ; 
 int RMID_VAL_ERROR ; 
 int RMID_VAL_UNAVAIL ; 
 int __rmid_read (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  abs (int) ; 
 int mbm_overflow_count (int,int) ; 
 struct rdt_resource* rdt_resources_all ; 

__attribute__((used)) static void mbm_bw_count(u32 rmid, struct rmid_read *rr)
{
	struct rdt_resource *r = &rdt_resources_all[RDT_RESOURCE_L3];
	struct mbm_state *m = &rr->d->mbm_local[rmid];
	u64 tval, cur_bw, chunks;

	tval = __rmid_read(rmid, rr->evtid);
	if (tval & (RMID_VAL_ERROR | RMID_VAL_UNAVAIL))
		return;

	chunks = mbm_overflow_count(m->prev_bw_msr, tval);
	m->chunks_bw += chunks;
	m->chunks = m->chunks_bw;
	cur_bw = (chunks * r->mon_scale) >> 20;

	if (m->delta_comp)
		m->delta_bw = abs(cur_bw - m->prev_bw);
	m->delta_comp = false;
	m->prev_bw = cur_bw;
	m->prev_bw_msr = tval;
}