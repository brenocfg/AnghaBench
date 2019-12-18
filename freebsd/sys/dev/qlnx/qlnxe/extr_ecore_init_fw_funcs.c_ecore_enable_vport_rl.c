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
struct ecore_hwfn {int dummy; } ;

/* Variables and functions */
 scalar_t__ QM_BYPASS_EN ; 
 int /*<<< orphan*/  QM_REG_AFULLQMBYPTHRGLBLRL_RT_OFFSET ; 
 int /*<<< orphan*/  QM_REG_RLGLBLENABLE_RT_OFFSET ; 
 int /*<<< orphan*/  QM_REG_RLGLBLPERIODTIMER_0_RT_OFFSET ; 
 int /*<<< orphan*/  QM_REG_RLGLBLPERIOD_0_RT_OFFSET ; 
 int QM_RL_PERIOD_CLK_25M ; 
 int QM_VP_RL_BYPASS_THRESH_SPEED ; 
 int /*<<< orphan*/  STORE_RT_REG (struct ecore_hwfn*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ecore_enable_vport_rl(struct ecore_hwfn *p_hwfn,
								  bool vport_rl_en)
{
	STORE_RT_REG(p_hwfn, QM_REG_RLGLBLENABLE_RT_OFFSET, vport_rl_en ? 1 : 0);
	if (vport_rl_en) {

		/* Write RL period (use timer 0 only) */
		STORE_RT_REG(p_hwfn, QM_REG_RLGLBLPERIOD_0_RT_OFFSET, QM_RL_PERIOD_CLK_25M);
		STORE_RT_REG(p_hwfn, QM_REG_RLGLBLPERIODTIMER_0_RT_OFFSET, QM_RL_PERIOD_CLK_25M);

		/* Set credit threshold for QM bypass flow */
		if (QM_BYPASS_EN)
			STORE_RT_REG(p_hwfn, QM_REG_AFULLQMBYPTHRGLBLRL_RT_OFFSET, QM_VP_RL_BYPASS_THRESH_SPEED);
	}
}