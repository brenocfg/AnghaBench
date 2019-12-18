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
typedef  int u8 ;
typedef  int u64 ;
typedef  int u32 ;
struct ecore_hwfn {int /*<<< orphan*/  p_dev; } ;

/* Variables and functions */
 scalar_t__ ECORE_IS_E5 (int /*<<< orphan*/ ) ; 
 int MAX_NUM_VOQS_E4 ; 
 scalar_t__ QM_BYPASS_EN ; 
 int QM_E5_NUM_EXT_VOQ ; 
 int QM_PF_RL_UPPER_BOUND ; 
 int /*<<< orphan*/  QM_REG_AFULLQMBYPTHRPFRL_RT_OFFSET ; 
 int /*<<< orphan*/  QM_REG_RLPFENABLE_RT_OFFSET ; 
 int /*<<< orphan*/  QM_REG_RLPFPERIODTIMER_RT_OFFSET ; 
 int /*<<< orphan*/  QM_REG_RLPFPERIOD_RT_OFFSET ; 
 int /*<<< orphan*/  QM_REG_RLPFVOQENABLE_MSB_RT_OFFSET ; 
 int /*<<< orphan*/  QM_REG_RLPFVOQENABLE_RT_OFFSET ; 
 int QM_RL_PERIOD_CLK_25M ; 
 int /*<<< orphan*/  STORE_RT_REG (struct ecore_hwfn*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ecore_enable_pf_rl(struct ecore_hwfn *p_hwfn,
							   bool pf_rl_en)
{
	STORE_RT_REG(p_hwfn, QM_REG_RLPFENABLE_RT_OFFSET, pf_rl_en ? 1 : 0);
	if (pf_rl_en) {
		u8 num_ext_voqs = ECORE_IS_E5(p_hwfn->p_dev) ? QM_E5_NUM_EXT_VOQ : MAX_NUM_VOQS_E4;
		u64 voq_bit_mask = ((u64)1 << num_ext_voqs) - 1;

		/* Enable RLs for all VOQs */
		STORE_RT_REG(p_hwfn, QM_REG_RLPFVOQENABLE_RT_OFFSET, (u32)voq_bit_mask);
#ifdef QM_REG_RLPFVOQENABLE_MSB_RT_OFFSET
		if (num_ext_voqs >= 32)
			STORE_RT_REG(p_hwfn, QM_REG_RLPFVOQENABLE_MSB_RT_OFFSET, (u32)(voq_bit_mask >> 32));
#endif

		/* Write RL period */
		STORE_RT_REG(p_hwfn, QM_REG_RLPFPERIOD_RT_OFFSET, QM_RL_PERIOD_CLK_25M);
		STORE_RT_REG(p_hwfn, QM_REG_RLPFPERIODTIMER_RT_OFFSET, QM_RL_PERIOD_CLK_25M);

		/* Set credit threshold for QM bypass flow */
		if (QM_BYPASS_EN)
			STORE_RT_REG(p_hwfn, QM_REG_AFULLQMBYPTHRPFRL_RT_OFFSET, QM_PF_RL_UPPER_BOUND);
	}
}