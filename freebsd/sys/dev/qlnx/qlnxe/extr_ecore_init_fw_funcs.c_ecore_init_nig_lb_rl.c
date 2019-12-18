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
typedef  int u32 ;
struct init_nig_lb_rl_req {int /*<<< orphan*/  mtu; scalar_t__* tc_rate; scalar_t__ lb_rate; scalar_t__ lb_mac_rate; } ;
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {int dummy; } ;

/* Variables and functions */
 int NIG_REG_LB_BRBRATELIMIT_CTRL ; 
 int NIG_REG_LB_BRBRATELIMIT_CTRL_LB_BRBRATELIMIT_BASE_TYPE_SHIFT ; 
 int NIG_REG_LB_BRBRATELIMIT_CTRL_LB_BRBRATELIMIT_EN_SHIFT ; 
 int NIG_REG_LB_BRBRATELIMIT_INC_PERIOD ; 
 int NIG_REG_LB_BRBRATELIMIT_INC_VALUE ; 
 int NIG_REG_LB_BRBRATELIMIT_MAX_VALUE ; 
 int NIG_REG_LB_TCRATELIMIT_CTRL_0 ; 
 int NIG_REG_LB_TCRATELIMIT_CTRL_0_LB_TCRATELIMIT_BASE_TYPE_0_SHIFT ; 
 int NIG_REG_LB_TCRATELIMIT_CTRL_0_LB_TCRATELIMIT_EN_0_SHIFT ; 
 int NIG_REG_LB_TCRATELIMIT_INC_PERIOD_0 ; 
 int NIG_REG_LB_TCRATELIMIT_INC_VALUE_0 ; 
 int NIG_REG_LB_TCRATELIMIT_MAX_VALUE_0 ; 
 int NIG_REG_TX_LB_GLBRATELIMIT_CTRL ; 
 int NIG_REG_TX_LB_GLBRATELIMIT_CTRL_TX_LB_GLBRATELIMIT_BASE_TYPE_SHIFT ; 
 int NIG_REG_TX_LB_GLBRATELIMIT_CTRL_TX_LB_GLBRATELIMIT_EN_SHIFT ; 
 int NIG_REG_TX_LB_GLBRATELIMIT_INC_PERIOD ; 
 int NIG_REG_TX_LB_GLBRATELIMIT_INC_VALUE ; 
 int NIG_REG_TX_LB_GLBRATELIMIT_MAX_VALUE ; 
 int NIG_RL_BASE_TYPE ; 
 int NIG_RL_INC_VAL (scalar_t__) ; 
 int NIG_RL_MAX_VAL (int,int /*<<< orphan*/ ) ; 
 int NIG_RL_PERIOD_CLK_25M ; 
 size_t NUM_OF_PHYS_TCS ; 
 int /*<<< orphan*/  ecore_wr (struct ecore_hwfn*,struct ecore_ptt*,int,int) ; 

void ecore_init_nig_lb_rl(struct ecore_hwfn *p_hwfn,
						  struct ecore_ptt *p_ptt,
						  struct init_nig_lb_rl_req* req)
{
	u32 ctrl, inc_val, reg_offset;
	u8 tc;

	/* Disable global MAC+LB RL */
	ctrl = NIG_RL_BASE_TYPE << NIG_REG_TX_LB_GLBRATELIMIT_CTRL_TX_LB_GLBRATELIMIT_BASE_TYPE_SHIFT;
	ecore_wr(p_hwfn, p_ptt, NIG_REG_TX_LB_GLBRATELIMIT_CTRL, ctrl);

	/* Configure and enable global MAC+LB RL */
	if (req->lb_mac_rate) {

		/* Configure  */
		ecore_wr(p_hwfn, p_ptt, NIG_REG_TX_LB_GLBRATELIMIT_INC_PERIOD, NIG_RL_PERIOD_CLK_25M);
		inc_val = NIG_RL_INC_VAL(req->lb_mac_rate);
		ecore_wr(p_hwfn, p_ptt, NIG_REG_TX_LB_GLBRATELIMIT_INC_VALUE, inc_val);
		ecore_wr(p_hwfn, p_ptt, NIG_REG_TX_LB_GLBRATELIMIT_MAX_VALUE, NIG_RL_MAX_VAL(inc_val, req->mtu));

		/* Enable */
		ctrl |= 1 << NIG_REG_TX_LB_GLBRATELIMIT_CTRL_TX_LB_GLBRATELIMIT_EN_SHIFT;
		ecore_wr(p_hwfn, p_ptt, NIG_REG_TX_LB_GLBRATELIMIT_CTRL, ctrl);
	}

	/* Disable global LB-only RL */
	ctrl = NIG_RL_BASE_TYPE << NIG_REG_LB_BRBRATELIMIT_CTRL_LB_BRBRATELIMIT_BASE_TYPE_SHIFT;
	ecore_wr(p_hwfn, p_ptt, NIG_REG_LB_BRBRATELIMIT_CTRL, ctrl);

	/* Configure and enable global LB-only RL */
	if (req->lb_rate) {

		/* Configure  */
		ecore_wr(p_hwfn, p_ptt, NIG_REG_LB_BRBRATELIMIT_INC_PERIOD, NIG_RL_PERIOD_CLK_25M);
		inc_val = NIG_RL_INC_VAL(req->lb_rate);
		ecore_wr(p_hwfn, p_ptt, NIG_REG_LB_BRBRATELIMIT_INC_VALUE, inc_val);
		ecore_wr(p_hwfn, p_ptt, NIG_REG_LB_BRBRATELIMIT_MAX_VALUE, NIG_RL_MAX_VAL(inc_val, req->mtu));

		/* Enable */
		ctrl |= 1 << NIG_REG_LB_BRBRATELIMIT_CTRL_LB_BRBRATELIMIT_EN_SHIFT;
		ecore_wr(p_hwfn, p_ptt, NIG_REG_LB_BRBRATELIMIT_CTRL, ctrl);
	}

	/* Per-TC RLs */
	for (tc = 0, reg_offset = 0; tc < NUM_OF_PHYS_TCS; tc++, reg_offset += 4) {

		/* Disable TC RL */
		ctrl = NIG_RL_BASE_TYPE << NIG_REG_LB_TCRATELIMIT_CTRL_0_LB_TCRATELIMIT_BASE_TYPE_0_SHIFT;
		ecore_wr(p_hwfn, p_ptt, NIG_REG_LB_TCRATELIMIT_CTRL_0 + reg_offset, ctrl);

		/* Configure and enable TC RL */
		if (!req->tc_rate[tc])
			continue;

		/* Configure */
		ecore_wr(p_hwfn, p_ptt, NIG_REG_LB_TCRATELIMIT_INC_PERIOD_0 + reg_offset, NIG_RL_PERIOD_CLK_25M);
		inc_val = NIG_RL_INC_VAL(req->tc_rate[tc]);
		ecore_wr(p_hwfn, p_ptt, NIG_REG_LB_TCRATELIMIT_INC_VALUE_0 + reg_offset, inc_val);
		ecore_wr(p_hwfn, p_ptt, NIG_REG_LB_TCRATELIMIT_MAX_VALUE_0 + reg_offset, NIG_RL_MAX_VAL(inc_val, req->mtu));

		/* Enable */
		ctrl |= 1 << NIG_REG_LB_TCRATELIMIT_CTRL_0_LB_TCRATELIMIT_EN_0_SHIFT;
		ecore_wr(p_hwfn, p_ptt, NIG_REG_LB_TCRATELIMIT_CTRL_0 + reg_offset, ctrl);
	}
}