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
#define  PLAT_PM_LPM20 128 
 int /*<<< orphan*/  RCPM_POWMGTCSR_LPM20_RQ ; 
 int RCPM_POWMGTCSR_LPM20_ST ; 
 int /*<<< orphan*/  RCPM_POWMGTCSR_P_LPM20_ST ; 
 int in_be32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_warn (char*,int) ; 
 TYPE_1__* rcpm_v2_regs ; 
 int /*<<< orphan*/  setbits32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int spin_event_timeout (int,int,int) ; 

__attribute__((used)) static int rcpm_v2_plat_enter_state(int state)
{
	u32 *pmcsr_reg = &rcpm_v2_regs->powmgtcsr;
	int ret = 0;
	int result;

	switch (state) {
	case PLAT_PM_LPM20:
		/* clear previous LPM20 status */
		setbits32(pmcsr_reg, RCPM_POWMGTCSR_P_LPM20_ST);
		/* enter LPM20 status */
		setbits32(pmcsr_reg, RCPM_POWMGTCSR_LPM20_RQ);

		/* At this point, the device is in LPM20 status. */

		/* resume ... */
		result = spin_event_timeout(
		  !(in_be32(pmcsr_reg) & RCPM_POWMGTCSR_LPM20_ST), 10000, 10);
		if (!result) {
			pr_err("timeout waiting for LPM20 bit to be cleared\n");
			ret = -ETIMEDOUT;
		}
		break;
	default:
		pr_warn("Unknown platform PM state (%d)\n", state);
		ret = -EINVAL;
	}

	return ret;
}