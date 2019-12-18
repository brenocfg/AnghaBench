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
typedef  size_t u8 ;
typedef  size_t u32 ;
struct init_ets_tc_req {size_t weight; int /*<<< orphan*/  use_wfq; scalar_t__ use_sp; } ;
struct init_ets_req {int /*<<< orphan*/  mtu; struct init_ets_tc_req* tc_req; } ;
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {int dummy; } ;

/* Variables and functions */
 size_t NIG_ETS_MIN_WFQ_BYTES ; 
 size_t NIG_ETS_UP_BOUND (size_t,int /*<<< orphan*/ ) ; 
 size_t NIG_LB_ETS_CLIENT_OFFSET ; 
 size_t NIG_REG_LB_ARB_CLIENT_IS_STRICT ; 
 size_t NIG_REG_LB_ARB_CLIENT_IS_SUBJECT2WFQ ; 
 size_t NIG_REG_LB_ARB_CREDIT_UPPER_BOUND_0 ; 
 size_t NIG_REG_LB_ARB_CREDIT_UPPER_BOUND_1 ; 
 size_t NIG_REG_LB_ARB_CREDIT_WEIGHT_0 ; 
 size_t NIG_REG_LB_ARB_CREDIT_WEIGHT_1 ; 
 size_t NIG_REG_TX_ARB_CLIENT_IS_STRICT ; 
 size_t NIG_REG_TX_ARB_CLIENT_IS_SUBJECT2WFQ ; 
 size_t NIG_REG_TX_ARB_CREDIT_UPPER_BOUND_0 ; 
 size_t NIG_REG_TX_ARB_CREDIT_UPPER_BOUND_1 ; 
 size_t NIG_REG_TX_ARB_CREDIT_WEIGHT_0 ; 
 size_t NIG_REG_TX_ARB_CREDIT_WEIGHT_1 ; 
 size_t NIG_TX_ETS_CLIENT_OFFSET ; 
 size_t NUM_OF_PHYS_TCS ; 
 size_t NUM_OF_TCS ; 
 int /*<<< orphan*/  ecore_wr (struct ecore_hwfn*,struct ecore_ptt*,size_t,size_t) ; 

void ecore_init_nig_ets(struct ecore_hwfn *p_hwfn,
						struct ecore_ptt *p_ptt,
						struct init_ets_req* req,
						bool is_lb)
{
	u32 min_weight, tc_weight_base_addr, tc_weight_addr_diff;
	u32 tc_bound_base_addr, tc_bound_addr_diff;
	u8 sp_tc_map = 0, wfq_tc_map = 0;
	u8 tc, num_tc, tc_client_offset;

	num_tc = is_lb ? NUM_OF_TCS : NUM_OF_PHYS_TCS;
	tc_client_offset = is_lb ? NIG_LB_ETS_CLIENT_OFFSET : NIG_TX_ETS_CLIENT_OFFSET;
	min_weight = 0xffffffff;
	tc_weight_base_addr = is_lb ? NIG_REG_LB_ARB_CREDIT_WEIGHT_0 : NIG_REG_TX_ARB_CREDIT_WEIGHT_0;
	tc_weight_addr_diff = is_lb ? NIG_REG_LB_ARB_CREDIT_WEIGHT_1 - NIG_REG_LB_ARB_CREDIT_WEIGHT_0 :
								  NIG_REG_TX_ARB_CREDIT_WEIGHT_1 - NIG_REG_TX_ARB_CREDIT_WEIGHT_0;
	tc_bound_base_addr = is_lb ? NIG_REG_LB_ARB_CREDIT_UPPER_BOUND_0 : NIG_REG_TX_ARB_CREDIT_UPPER_BOUND_0;
	tc_bound_addr_diff = is_lb ? NIG_REG_LB_ARB_CREDIT_UPPER_BOUND_1 - NIG_REG_LB_ARB_CREDIT_UPPER_BOUND_0 :
								 NIG_REG_TX_ARB_CREDIT_UPPER_BOUND_1 - NIG_REG_TX_ARB_CREDIT_UPPER_BOUND_0;

	for (tc = 0; tc < num_tc; tc++) {
		struct init_ets_tc_req *tc_req = &req->tc_req[tc];

		/* Update SP map */
		if (tc_req->use_sp)
			sp_tc_map |= (1 << tc);

		if (!tc_req->use_wfq)
			continue;

		/* Update WFQ map */
		wfq_tc_map |= (1 << tc);
                                
		/* Find minimal weight */
		if (tc_req->weight < min_weight)
			min_weight = tc_req->weight;
	}

	/* Write SP map */
	ecore_wr(p_hwfn, p_ptt, is_lb ? NIG_REG_LB_ARB_CLIENT_IS_STRICT : NIG_REG_TX_ARB_CLIENT_IS_STRICT, (sp_tc_map << tc_client_offset));

	/* Write WFQ map */
	ecore_wr(p_hwfn, p_ptt, is_lb ? NIG_REG_LB_ARB_CLIENT_IS_SUBJECT2WFQ : NIG_REG_TX_ARB_CLIENT_IS_SUBJECT2WFQ, (wfq_tc_map << tc_client_offset));

	/* Write WFQ weights */
	for (tc = 0; tc < num_tc; tc++, tc_client_offset++) {
		struct init_ets_tc_req *tc_req = &req->tc_req[tc];
		u32 byte_weight;

		if (!tc_req->use_wfq)
			continue;

		/* Translate weight to bytes */
		byte_weight = (NIG_ETS_MIN_WFQ_BYTES * tc_req->weight) / min_weight;

		/* Write WFQ weight */
		ecore_wr(p_hwfn, p_ptt, tc_weight_base_addr + tc_weight_addr_diff * tc_client_offset, byte_weight);

		/* Write WFQ upper bound */
		ecore_wr(p_hwfn, p_ptt, tc_bound_base_addr + tc_bound_addr_diff * tc_client_offset, NIG_ETS_UP_BOUND(byte_weight, req->mtu));
	}
}