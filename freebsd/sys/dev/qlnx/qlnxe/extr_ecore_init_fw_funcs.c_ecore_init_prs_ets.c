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
typedef  scalar_t__ u32 ;
struct init_ets_tc_req {scalar_t__ weight; int /*<<< orphan*/  use_wfq; scalar_t__ use_sp; } ;
struct init_ets_req {int /*<<< orphan*/  mtu; struct init_ets_tc_req* tc_req; } ;
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {int dummy; } ;

/* Variables and functions */
 size_t NUM_OF_TCS ; 
 scalar_t__ PRS_ETS_MIN_WFQ_BYTES ; 
 scalar_t__ PRS_ETS_UP_BOUND (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ PRS_REG_ETS_ARB_CLIENT_IS_STRICT ; 
 scalar_t__ PRS_REG_ETS_ARB_CLIENT_IS_SUBJECT2WFQ ; 
 scalar_t__ PRS_REG_ETS_ARB_CREDIT_UPPER_BOUND_0 ; 
 scalar_t__ PRS_REG_ETS_ARB_CREDIT_UPPER_BOUND_1 ; 
 scalar_t__ PRS_REG_ETS_ARB_CREDIT_WEIGHT_0 ; 
 scalar_t__ PRS_REG_ETS_ARB_CREDIT_WEIGHT_1 ; 
 int /*<<< orphan*/  ecore_wr (struct ecore_hwfn*,struct ecore_ptt*,scalar_t__,scalar_t__) ; 

void ecore_init_prs_ets(struct ecore_hwfn *p_hwfn,
						struct ecore_ptt *p_ptt,
						struct init_ets_req* req)
{
	u32 tc_weight_addr_diff, tc_bound_addr_diff, min_weight = 0xffffffff;
	u8 tc, sp_tc_map = 0, wfq_tc_map = 0;

	tc_weight_addr_diff = PRS_REG_ETS_ARB_CREDIT_WEIGHT_1 - PRS_REG_ETS_ARB_CREDIT_WEIGHT_0;
	tc_bound_addr_diff = PRS_REG_ETS_ARB_CREDIT_UPPER_BOUND_1 - PRS_REG_ETS_ARB_CREDIT_UPPER_BOUND_0;

	for (tc = 0; tc < NUM_OF_TCS; tc++) {
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
	ecore_wr(p_hwfn, p_ptt, PRS_REG_ETS_ARB_CLIENT_IS_STRICT, sp_tc_map);

	/* Write WFQ map */
	ecore_wr(p_hwfn, p_ptt, PRS_REG_ETS_ARB_CLIENT_IS_SUBJECT2WFQ, wfq_tc_map);

	/* Write WFQ weights */
	for (tc = 0; tc < NUM_OF_TCS; tc++) {
		struct init_ets_tc_req *tc_req = &req->tc_req[tc];
		u32 byte_weight;

		if (!tc_req->use_wfq)
			continue;

		/* Translate weight to bytes */
		byte_weight = (PRS_ETS_MIN_WFQ_BYTES * tc_req->weight) / min_weight;

		/* Write WFQ weight */
		ecore_wr(p_hwfn, p_ptt, PRS_REG_ETS_ARB_CREDIT_WEIGHT_0 + tc * tc_weight_addr_diff, byte_weight);

		/* Write WFQ upper bound */
		ecore_wr(p_hwfn, p_ptt, PRS_REG_ETS_ARB_CREDIT_UPPER_BOUND_0 + tc * tc_bound_addr_diff, PRS_ETS_UP_BOUND(byte_weight, req->mtu));
	}
}