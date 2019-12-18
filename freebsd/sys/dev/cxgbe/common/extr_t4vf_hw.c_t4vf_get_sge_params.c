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
typedef  unsigned int u32 ;
struct sge_params {unsigned int sge_control; int fl_starve_threshold; int fl_starve_threshold2; unsigned int page_shift; unsigned int* sge_fl_buffer_size; int spg_len; int pad_boundary; int pack_boundary; unsigned int eq_s_qpp; unsigned int iq_s_qpp; int /*<<< orphan*/  fl_pktshift; void** timer_val; int /*<<< orphan*/ * counter_val; } ;
struct TYPE_2__ {struct sge_params sge; } ;
struct adapter {TYPE_1__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_PL_VF_WHOAMI ; 
 scalar_t__ A_SGE_CONM_CTRL ; 
 scalar_t__ A_SGE_CONTROL ; 
 scalar_t__ A_SGE_CONTROL2 ; 
 scalar_t__ A_SGE_EGRESS_QUEUES_PER_PAGE_VF ; 
 scalar_t__ A_SGE_FL_BUFFER_SIZE0 ; 
 scalar_t__ A_SGE_HOST_PAGE_SIZE ; 
 scalar_t__ A_SGE_INGRESS_QUEUES_PER_PAGE_VF ; 
 scalar_t__ A_SGE_INGRESS_RX_THRESHOLD ; 
 scalar_t__ A_SGE_TIMER_VALUE_0_AND_1 ; 
 scalar_t__ A_SGE_TIMER_VALUE_2_AND_3 ; 
 scalar_t__ A_SGE_TIMER_VALUE_4_AND_5 ; 
 scalar_t__ CHELSIO_T5 ; 
 int /*<<< orphan*/  CH_ERR (struct adapter*,char*) ; 
 int /*<<< orphan*/  CH_WARN (struct adapter*,char*) ; 
 int /*<<< orphan*/  FW_PARAMS_MNEM_REG ; 
 int FW_SUCCESS ; 
 int F_EGRSTATUSPAGESIZE ; 
 int G_EGRTHRESHOLD (unsigned int) ; 
 int G_EGRTHRESHOLDPACKING (unsigned int) ; 
 int G_INGPACKBOUNDARY (unsigned int) ; 
 int G_INGPADBOUNDARY (int) ; 
 int /*<<< orphan*/  G_PKTSHIFT (int) ; 
 unsigned int G_SOURCEPF (unsigned int) ; 
 int G_T6_EGRTHRESHOLDPACKING (unsigned int) ; 
 int /*<<< orphan*/  G_THRESHOLD_0 (unsigned int) ; 
 int /*<<< orphan*/  G_THRESHOLD_1 (unsigned int) ; 
 int /*<<< orphan*/  G_THRESHOLD_2 (unsigned int) ; 
 int /*<<< orphan*/  G_THRESHOLD_3 (unsigned int) ; 
 int /*<<< orphan*/  G_TIMERVALUE0 (unsigned int) ; 
 int /*<<< orphan*/  G_TIMERVALUE1 (unsigned int) ; 
 int /*<<< orphan*/  G_TIMERVALUE2 (unsigned int) ; 
 int /*<<< orphan*/  G_TIMERVALUE3 (unsigned int) ; 
 int /*<<< orphan*/  G_TIMERVALUE4 (unsigned int) ; 
 int /*<<< orphan*/  G_TIMERVALUE5 (unsigned int) ; 
 unsigned int M_HOSTPAGESIZEPF0 ; 
 unsigned int M_QUEUESPERPAGEPF0 ; 
 int SGE_FLBUF_SIZES ; 
 unsigned int S_HOSTPAGESIZEPF0 ; 
 unsigned int S_HOSTPAGESIZEPF1 ; 
 unsigned int S_QUEUESPERPAGEPF0 ; 
 unsigned int S_QUEUESPERPAGEPF1 ; 
 int /*<<< orphan*/  VF_PL_REG (int /*<<< orphan*/ ) ; 
 unsigned int V_FW_PARAMS_MNEM (int /*<<< orphan*/ ) ; 
 unsigned int V_FW_PARAMS_PARAM_XYZ (scalar_t__) ; 
 int X_INGPADBOUNDARY_SHIFT ; 
 int X_T6_INGPADBOUNDARY_SHIFT ; 
 scalar_t__ chip_id (struct adapter*) ; 
 void* core_ticks_to_us (struct adapter*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_t4 (struct adapter*) ; 
 scalar_t__ is_t5 (struct adapter*) ; 
 unsigned int t4_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 
 int t4vf_query_params (struct adapter*,int,unsigned int*,unsigned int*) ; 

int t4vf_get_sge_params(struct adapter *adapter)
{
	struct sge_params *sp = &adapter->params.sge;
	u32 params[7], vals[7];
	u32 whoami;
	unsigned int pf, s_hps;
	int i, v;

	params[0] = (V_FW_PARAMS_MNEM(FW_PARAMS_MNEM_REG) |
		     V_FW_PARAMS_PARAM_XYZ(A_SGE_CONTROL));
	params[1] = (V_FW_PARAMS_MNEM(FW_PARAMS_MNEM_REG) |
		     V_FW_PARAMS_PARAM_XYZ(A_SGE_HOST_PAGE_SIZE));
	params[2] = (V_FW_PARAMS_MNEM(FW_PARAMS_MNEM_REG) |
		     V_FW_PARAMS_PARAM_XYZ(A_SGE_TIMER_VALUE_0_AND_1));
	params[3] = (V_FW_PARAMS_MNEM(FW_PARAMS_MNEM_REG) |
		     V_FW_PARAMS_PARAM_XYZ(A_SGE_TIMER_VALUE_2_AND_3));
	params[4] = (V_FW_PARAMS_MNEM(FW_PARAMS_MNEM_REG) |
		     V_FW_PARAMS_PARAM_XYZ(A_SGE_TIMER_VALUE_4_AND_5));
	params[5] = (V_FW_PARAMS_MNEM(FW_PARAMS_MNEM_REG) |
		     V_FW_PARAMS_PARAM_XYZ(A_SGE_CONM_CTRL));
	params[6] = (V_FW_PARAMS_MNEM(FW_PARAMS_MNEM_REG) |
		     V_FW_PARAMS_PARAM_XYZ(A_SGE_INGRESS_RX_THRESHOLD));
	v = t4vf_query_params(adapter, 7, params, vals);
	if (v != FW_SUCCESS)
		return v;

	sp->sge_control = vals[0];
	sp->counter_val[0] = G_THRESHOLD_0(vals[6]);
	sp->counter_val[1] = G_THRESHOLD_1(vals[6]);
	sp->counter_val[2] = G_THRESHOLD_2(vals[6]);
	sp->counter_val[3] = G_THRESHOLD_3(vals[6]);
	sp->timer_val[0] = core_ticks_to_us(adapter, G_TIMERVALUE0(vals[2]));
	sp->timer_val[1] = core_ticks_to_us(adapter, G_TIMERVALUE1(vals[2]));
	sp->timer_val[2] = core_ticks_to_us(adapter, G_TIMERVALUE2(vals[3]));
	sp->timer_val[3] = core_ticks_to_us(adapter, G_TIMERVALUE3(vals[3]));
	sp->timer_val[4] = core_ticks_to_us(adapter, G_TIMERVALUE4(vals[4]));
	sp->timer_val[5] = core_ticks_to_us(adapter, G_TIMERVALUE5(vals[4]));

	sp->fl_starve_threshold = G_EGRTHRESHOLD(vals[5]) * 2 + 1;
	if (is_t4(adapter))
		sp->fl_starve_threshold2 = sp->fl_starve_threshold;
	else if (is_t5(adapter))
		sp->fl_starve_threshold2 = G_EGRTHRESHOLDPACKING(vals[5]) * 2 + 1;
	else
		sp->fl_starve_threshold2 = G_T6_EGRTHRESHOLDPACKING(vals[5]) * 2 + 1;

	/*
	 * We need the Queues/Page and Host Page Size for our VF.
	 * This is based on the PF from which we're instantiated.
	 */
	whoami = t4_read_reg(adapter, VF_PL_REG(A_PL_VF_WHOAMI));
	pf = G_SOURCEPF(whoami);

	s_hps = (S_HOSTPAGESIZEPF0 +
	    (S_HOSTPAGESIZEPF1 - S_HOSTPAGESIZEPF0) * pf);
	sp->page_shift = ((vals[1] >> s_hps) & M_HOSTPAGESIZEPF0) + 10;

	for (i = 0; i < SGE_FLBUF_SIZES; i++) {
		params[0] = (V_FW_PARAMS_MNEM(FW_PARAMS_MNEM_REG) |
		    V_FW_PARAMS_PARAM_XYZ(A_SGE_FL_BUFFER_SIZE0 + (4 * i)));
		v = t4vf_query_params(adapter, 1, params, vals);
		if (v != FW_SUCCESS)
			return v;

		sp->sge_fl_buffer_size[i] = vals[0];
	}

	/*
	 * T4 uses a single control field to specify both the PCIe Padding and
	 * Packing Boundary.  T5 introduced the ability to specify these
	 * separately with the Padding Boundary in SGE_CONTROL and and Packing
	 * Boundary in SGE_CONTROL2.  So for T5 and later we need to grab
	 * SGE_CONTROL in order to determine how ingress packet data will be
	 * laid out in Packed Buffer Mode.  Unfortunately, older versions of
	 * the firmware won't let us retrieve SGE_CONTROL2 so if we get a
	 * failure grabbing it we throw an error since we can't figure out the
	 * right value.
	 */
	sp->spg_len = sp->sge_control & F_EGRSTATUSPAGESIZE ? 128 : 64;
	sp->fl_pktshift = G_PKTSHIFT(sp->sge_control);
	if (chip_id(adapter) <= CHELSIO_T5) {
		sp->pad_boundary = 1 << (G_INGPADBOUNDARY(sp->sge_control) +
		    X_INGPADBOUNDARY_SHIFT);
	} else {
		sp->pad_boundary = 1 << (G_INGPADBOUNDARY(sp->sge_control) +
		    X_T6_INGPADBOUNDARY_SHIFT);
	}
	if (is_t4(adapter))
		sp->pack_boundary = sp->pad_boundary;
	else {
		params[0] = (V_FW_PARAMS_MNEM(FW_PARAMS_MNEM_REG) |
			     V_FW_PARAMS_PARAM_XYZ(A_SGE_CONTROL2));
		v = t4vf_query_params(adapter, 1, params, vals);
		if (v != FW_SUCCESS) {
			CH_ERR(adapter, "Unable to get SGE Control2; "
			       "probably old firmware.\n");
			return v;
		}
		if (G_INGPACKBOUNDARY(vals[0]) == 0)
			sp->pack_boundary = 16;
		else
			sp->pack_boundary = 1 << (G_INGPACKBOUNDARY(vals[0]) +
			    5);
	}

	/*
	 * For T5 and later we want to use the new BAR2 Doorbells.
	 * Unfortunately, older firmware didn't allow the this register to be
	 * read.
	 */
	if (!is_t4(adapter)) {
		unsigned int s_qpp;

		params[0] = (V_FW_PARAMS_MNEM(FW_PARAMS_MNEM_REG) |
			     V_FW_PARAMS_PARAM_XYZ(A_SGE_EGRESS_QUEUES_PER_PAGE_VF));
		params[1] = (V_FW_PARAMS_MNEM(FW_PARAMS_MNEM_REG) |
			     V_FW_PARAMS_PARAM_XYZ(A_SGE_INGRESS_QUEUES_PER_PAGE_VF));
		v = t4vf_query_params(adapter, 2, params, vals);
		if (v != FW_SUCCESS) {
			CH_WARN(adapter, "Unable to get VF SGE Queues/Page; "
				"probably old firmware.\n");
			return v;
		}

		s_qpp = (S_QUEUESPERPAGEPF0 +
			 (S_QUEUESPERPAGEPF1 - S_QUEUESPERPAGEPF0) * pf);
		sp->eq_s_qpp = ((vals[0] >> s_qpp) & M_QUEUESPERPAGEPF0);
		sp->iq_s_qpp = ((vals[1] >> s_qpp) & M_QUEUESPERPAGEPF0);
	}

	return 0;
}