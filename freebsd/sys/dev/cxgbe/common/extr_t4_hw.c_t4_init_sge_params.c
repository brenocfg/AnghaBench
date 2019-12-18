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
typedef  int u32 ;
struct sge_params {unsigned int* timer_val; int fl_starve_threshold; int fl_starve_threshold2; int eq_s_qpp; int iq_s_qpp; int page_shift; int sge_control; int spg_len; int pad_boundary; int pack_boundary; void** sge_fl_buffer_size; int /*<<< orphan*/  fl_pktshift; int /*<<< orphan*/ * counter_val; } ;
struct TYPE_2__ {struct sge_params sge; } ;
struct adapter {int pf; TYPE_1__ params; } ;

/* Variables and functions */
 scalar_t__ A_SGE_CONM_CTRL ; 
 scalar_t__ A_SGE_CONTROL ; 
 scalar_t__ A_SGE_CONTROL2 ; 
 scalar_t__ A_SGE_EGRESS_QUEUES_PER_PAGE_PF ; 
 scalar_t__ A_SGE_FL_BUFFER_SIZE0 ; 
 scalar_t__ A_SGE_HOST_PAGE_SIZE ; 
 scalar_t__ A_SGE_INGRESS_QUEUES_PER_PAGE_PF ; 
 scalar_t__ A_SGE_INGRESS_RX_THRESHOLD ; 
 scalar_t__ A_SGE_ITP_CONTROL ; 
 scalar_t__ A_SGE_TIMER_VALUE_0_AND_1 ; 
 scalar_t__ A_SGE_TIMER_VALUE_2_AND_3 ; 
 scalar_t__ A_SGE_TIMER_VALUE_4_AND_5 ; 
 scalar_t__ CHELSIO_T5 ; 
 scalar_t__ CHELSIO_T6 ; 
 int F_EGRSTATUSPAGESIZE ; 
 int G_EGRTHRESHOLD (int) ; 
 int G_EGRTHRESHOLDPACKING (int) ; 
 int G_INGPACKBOUNDARY (int) ; 
 int G_INGPADBOUNDARY (int) ; 
 int /*<<< orphan*/  G_PKTSHIFT (int) ; 
 int G_T6_EGRTHRESHOLDPACKING (int) ; 
 int /*<<< orphan*/  G_THRESHOLD_0 (int) ; 
 int /*<<< orphan*/  G_THRESHOLD_1 (int) ; 
 int /*<<< orphan*/  G_THRESHOLD_2 (int) ; 
 int /*<<< orphan*/  G_THRESHOLD_3 (int) ; 
 int /*<<< orphan*/  G_TIMERVALUE0 (int) ; 
 int /*<<< orphan*/  G_TIMERVALUE1 (int) ; 
 int /*<<< orphan*/  G_TIMERVALUE2 (int) ; 
 int /*<<< orphan*/  G_TIMERVALUE3 (int) ; 
 int /*<<< orphan*/  G_TIMERVALUE4 (int) ; 
 int /*<<< orphan*/  G_TIMERVALUE5 (int) ; 
 unsigned int G_TSCALE (int) ; 
 int M_HOSTPAGESIZEPF0 ; 
 int M_QUEUESPERPAGEPF0 ; 
 unsigned int SGE_FLBUF_SIZES ; 
 int S_HOSTPAGESIZEPF0 ; 
 int S_HOSTPAGESIZEPF1 ; 
 int S_QUEUESPERPAGEPF0 ; 
 int S_QUEUESPERPAGEPF1 ; 
 int X_INGPADBOUNDARY_SHIFT ; 
 int X_T6_INGPADBOUNDARY_SHIFT ; 
 scalar_t__ chip_id (struct adapter*) ; 
 unsigned int core_ticks_to_us (struct adapter*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_t4 (struct adapter*) ; 
 scalar_t__ is_t5 (struct adapter*) ; 
 void* t4_read_reg (struct adapter*,scalar_t__) ; 

int t4_init_sge_params(struct adapter *adapter)
{
	u32 r;
	struct sge_params *sp = &adapter->params.sge;
	unsigned i, tscale = 1;

	r = t4_read_reg(adapter, A_SGE_INGRESS_RX_THRESHOLD);
	sp->counter_val[0] = G_THRESHOLD_0(r);
	sp->counter_val[1] = G_THRESHOLD_1(r);
	sp->counter_val[2] = G_THRESHOLD_2(r);
	sp->counter_val[3] = G_THRESHOLD_3(r);

	if (chip_id(adapter) >= CHELSIO_T6) {
		r = t4_read_reg(adapter, A_SGE_ITP_CONTROL);
		tscale = G_TSCALE(r);
		if (tscale == 0)
			tscale = 1;
		else
			tscale += 2;
	}

	r = t4_read_reg(adapter, A_SGE_TIMER_VALUE_0_AND_1);
	sp->timer_val[0] = core_ticks_to_us(adapter, G_TIMERVALUE0(r)) * tscale;
	sp->timer_val[1] = core_ticks_to_us(adapter, G_TIMERVALUE1(r)) * tscale;
	r = t4_read_reg(adapter, A_SGE_TIMER_VALUE_2_AND_3);
	sp->timer_val[2] = core_ticks_to_us(adapter, G_TIMERVALUE2(r)) * tscale;
	sp->timer_val[3] = core_ticks_to_us(adapter, G_TIMERVALUE3(r)) * tscale;
	r = t4_read_reg(adapter, A_SGE_TIMER_VALUE_4_AND_5);
	sp->timer_val[4] = core_ticks_to_us(adapter, G_TIMERVALUE4(r)) * tscale;
	sp->timer_val[5] = core_ticks_to_us(adapter, G_TIMERVALUE5(r)) * tscale;

	r = t4_read_reg(adapter, A_SGE_CONM_CTRL);
	sp->fl_starve_threshold = G_EGRTHRESHOLD(r) * 2 + 1;
	if (is_t4(adapter))
		sp->fl_starve_threshold2 = sp->fl_starve_threshold;
	else if (is_t5(adapter))
		sp->fl_starve_threshold2 = G_EGRTHRESHOLDPACKING(r) * 2 + 1;
	else
		sp->fl_starve_threshold2 = G_T6_EGRTHRESHOLDPACKING(r) * 2 + 1;

	/* egress queues: log2 of # of doorbells per BAR2 page */
	r = t4_read_reg(adapter, A_SGE_EGRESS_QUEUES_PER_PAGE_PF);
	r >>= S_QUEUESPERPAGEPF0 +
	    (S_QUEUESPERPAGEPF1 - S_QUEUESPERPAGEPF0) * adapter->pf;
	sp->eq_s_qpp = r & M_QUEUESPERPAGEPF0;

	/* ingress queues: log2 of # of doorbells per BAR2 page */
	r = t4_read_reg(adapter, A_SGE_INGRESS_QUEUES_PER_PAGE_PF);
	r >>= S_QUEUESPERPAGEPF0 +
	    (S_QUEUESPERPAGEPF1 - S_QUEUESPERPAGEPF0) * adapter->pf;
	sp->iq_s_qpp = r & M_QUEUESPERPAGEPF0;

	r = t4_read_reg(adapter, A_SGE_HOST_PAGE_SIZE);
	r >>= S_HOSTPAGESIZEPF0 +
	    (S_HOSTPAGESIZEPF1 - S_HOSTPAGESIZEPF0) * adapter->pf;
	sp->page_shift = (r & M_HOSTPAGESIZEPF0) + 10;

	r = t4_read_reg(adapter, A_SGE_CONTROL);
	sp->sge_control = r;
	sp->spg_len = r & F_EGRSTATUSPAGESIZE ? 128 : 64;
	sp->fl_pktshift = G_PKTSHIFT(r);
	if (chip_id(adapter) <= CHELSIO_T5) {
		sp->pad_boundary = 1 << (G_INGPADBOUNDARY(r) +
		    X_INGPADBOUNDARY_SHIFT);
	} else {
		sp->pad_boundary = 1 << (G_INGPADBOUNDARY(r) +
		    X_T6_INGPADBOUNDARY_SHIFT);
	}
	if (is_t4(adapter))
		sp->pack_boundary = sp->pad_boundary;
	else {
		r = t4_read_reg(adapter, A_SGE_CONTROL2);
		if (G_INGPACKBOUNDARY(r) == 0)
			sp->pack_boundary = 16;
		else
			sp->pack_boundary = 1 << (G_INGPACKBOUNDARY(r) + 5);
	}
	for (i = 0; i < SGE_FLBUF_SIZES; i++)
		sp->sge_fl_buffer_size[i] = t4_read_reg(adapter,
		    A_SGE_FL_BUFFER_SIZE0 + (4 * i));

	return 0;
}