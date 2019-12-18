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
typedef  int u32 ;
typedef  enum ulp_cpu_pwr_mode { ____Placeholder_ulp_cpu_pwr_mode } ulp_cpu_pwr_mode ;

/* Variables and functions */
 int BM_PMCTRL_PSTOPO ; 
 int BM_PMCTRL_RUNM ; 
 int BM_PMCTRL_STOPM ; 
 int BP_PMCTRL_PSTOPO ; 
 int EINVAL ; 
 int PSTOPO_PSTOP1 ; 
 int PSTOPO_PSTOP2 ; 
 int PSTOPO_PSTOP3 ; 
 scalar_t__ SMC_PMCTRL ; 
#define  ULP_PM_RUN 130 
#define  ULP_PM_STOP 129 
#define  ULP_PM_WAIT 128 
 int readl_relaxed (scalar_t__) ; 
 scalar_t__ smc1_base ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

int imx7ulp_set_lpm(enum ulp_cpu_pwr_mode mode)
{
	u32 val = readl_relaxed(smc1_base + SMC_PMCTRL);

	/* clear all */
	val &= ~(BM_PMCTRL_RUNM | BM_PMCTRL_STOPM | BM_PMCTRL_PSTOPO);

	switch (mode) {
	case ULP_PM_RUN:
		/* system/bus clock enabled */
		val |= PSTOPO_PSTOP3 << BP_PMCTRL_PSTOPO;
		break;
	case ULP_PM_WAIT:
		/* system clock disabled, bus clock enabled */
		val |= PSTOPO_PSTOP2 << BP_PMCTRL_PSTOPO;
		break;
	case ULP_PM_STOP:
		/* system/bus clock disabled */
		val |= PSTOPO_PSTOP1 << BP_PMCTRL_PSTOPO;
		break;
	default:
		return -EINVAL;
	}

	writel_relaxed(val, smc1_base + SMC_PMCTRL);

	return 0;
}