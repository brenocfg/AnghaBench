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
typedef  int suspend_state_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IMX5_DEFAULT_CPU_IDLE_STATE ; 
 scalar_t__ MXC_SRPG_EMPGC0_SRPGCR ; 
 scalar_t__ MXC_SRPG_EMPGC1_SRPGCR ; 
#define  PM_SUSPEND_MEM 129 
#define  PM_SUSPEND_STANDBY 128 
 int /*<<< orphan*/  STOP_POWER_OFF ; 
 int /*<<< orphan*/  cpu_do_idle () ; 
 int /*<<< orphan*/  flush_cache_all () ; 
 scalar_t__ gpc_base ; 
 int /*<<< orphan*/  imx5_suspend_in_ocram_fn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx_writel (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  local_flush_tlb_all () ; 
 int /*<<< orphan*/  mx5_cpu_lp_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  suspend_ocram_base ; 

__attribute__((used)) static int mx5_suspend_enter(suspend_state_t state)
{
	switch (state) {
	case PM_SUSPEND_MEM:
		mx5_cpu_lp_set(STOP_POWER_OFF);
		break;
	case PM_SUSPEND_STANDBY:
		/* DEFAULT_IDLE_STATE already configured */
		break;
	default:
		return -EINVAL;
	}

	if (state == PM_SUSPEND_MEM) {
		local_flush_tlb_all();
		flush_cache_all();

		/*clear the EMPGC0/1 bits */
		imx_writel(0, gpc_base + MXC_SRPG_EMPGC0_SRPGCR);
		imx_writel(0, gpc_base + MXC_SRPG_EMPGC1_SRPGCR);

		if (imx5_suspend_in_ocram_fn)
			imx5_suspend_in_ocram_fn(suspend_ocram_base);
		else
			cpu_do_idle();

	} else {
		cpu_do_idle();
	}

	/* return registers to default idle state */
	mx5_cpu_lp_set(IMX5_DEFAULT_CPU_IDLE_STATE);
	return 0;
}