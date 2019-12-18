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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  powmgtcsr; } ;

/* Variables and functions */
 int EINVAL ; 
 int ETIMEDOUT ; 
#define  PLAT_PM_SLEEP 128 
 int RCPM_POWMGTCSR_SLP ; 
 int in_be32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_warn (char*,int) ; 
 TYPE_1__* rcpm_v1_regs ; 
 int /*<<< orphan*/  setbits32 (int /*<<< orphan*/ *,int) ; 
 int spin_event_timeout (int,int,int) ; 

__attribute__((used)) static int rcpm_v1_plat_enter_state(int state)
{
	u32 *pmcsr_reg = &rcpm_v1_regs->powmgtcsr;
	int ret = 0;
	int result;

	switch (state) {
	case PLAT_PM_SLEEP:
		setbits32(pmcsr_reg, RCPM_POWMGTCSR_SLP);

		/* Upon resume, wait for RCPM_POWMGTCSR_SLP bit to be clear. */
		result = spin_event_timeout(
		  !(in_be32(pmcsr_reg) & RCPM_POWMGTCSR_SLP), 10000, 10);
		if (!result) {
			pr_err("timeout waiting for SLP bit to be cleared\n");
			ret = -ETIMEDOUT;
		}
		break;
	default:
		pr_warn("Unknown platform PM state (%d)", state);
		ret = -EINVAL;
	}

	return ret;
}