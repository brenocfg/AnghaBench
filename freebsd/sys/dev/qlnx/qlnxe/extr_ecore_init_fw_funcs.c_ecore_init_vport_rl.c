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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*) ; 
 scalar_t__ MAX_QM_GLOBAL_RLS ; 
 scalar_t__ QM_REG_RLGLBLCRD ; 
 scalar_t__ QM_REG_RLGLBLINCVAL ; 
 scalar_t__ QM_RL_CRD_REG_SIGN_BIT ; 
 scalar_t__ QM_RL_INC_VAL (scalar_t__) ; 
 scalar_t__ QM_VP_RL_MAX_INC_VAL (scalar_t__) ; 
 int /*<<< orphan*/  ecore_wr (struct ecore_hwfn*,struct ecore_ptt*,scalar_t__,scalar_t__) ; 

int ecore_init_vport_rl(struct ecore_hwfn *p_hwfn,
						struct ecore_ptt *p_ptt,
						u8 vport_id,
						u32 vport_rl,
						u32 link_speed)
{
	u32 inc_val, max_qm_global_rls = MAX_QM_GLOBAL_RLS;

	if (vport_id >= max_qm_global_rls) {
		DP_NOTICE(p_hwfn, true, "Invalid VPORT ID for rate limiter configuration\n");
		return -1;
	}

	inc_val = QM_RL_INC_VAL(vport_rl ? vport_rl : link_speed);
	if (inc_val > QM_VP_RL_MAX_INC_VAL(link_speed)) {
		DP_NOTICE(p_hwfn, true, "Invalid VPORT rate-limit configuration\n");
		return -1;
	}

	ecore_wr(p_hwfn, p_ptt, QM_REG_RLGLBLCRD + vport_id * 4, (u32)QM_RL_CRD_REG_SIGN_BIT);
	ecore_wr(p_hwfn, p_ptt, QM_REG_RLGLBLINCVAL + vport_id * 4, inc_val);

	return 0;
}