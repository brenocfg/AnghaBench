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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 scalar_t__ OMAP2_DEVICE_TYPE_EMU ; 
 scalar_t__ OMAP2_DEVICE_TYPE_SEC ; 
 scalar_t__ OMAP3430_REV_ES3_0 ; 
#define  PWRDM_POWER_OFF 130 
#define  PWRDM_POWER_ON 129 
#define  PWRDM_POWER_RET 128 
 int /*<<< orphan*/  SDRC_POWER ; 
 int /*<<< orphan*/  core_pwrdm ; 
 int /*<<< orphan*/  cpu_cluster_pm_enter () ; 
 int /*<<< orphan*/  cpu_cluster_pm_exit () ; 
 scalar_t__ cpu_is_omap3430 () ; 
 int /*<<< orphan*/  cpu_suspend (int,int /*<<< orphan*/  (*) (int)) ; 
 int /*<<< orphan*/  mpu_pwrdm ; 
 int /*<<< orphan*/  neon_pwrdm ; 
 int /*<<< orphan*/  omap2_sms_restore_context () ; 
 int /*<<< orphan*/  omap34xx_do_sram_idle (int) ; 
 int /*<<< orphan*/  omap34xx_save_context (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap3_arm_context ; 
 int /*<<< orphan*/  omap3_cm_restore_context () ; 
 int /*<<< orphan*/  omap3_cm_save_context () ; 
 int /*<<< orphan*/  omap3_core_restore_context () ; 
 int /*<<< orphan*/  omap3_core_save_context () ; 
 int /*<<< orphan*/  omap3_intc_prepare_idle () ; 
 int /*<<< orphan*/  omap3_intc_resume_idle () ; 
 int /*<<< orphan*/  omap3_sram_restore_context () ; 
 int /*<<< orphan*/  omap3_vc_set_pmic_signaling (int) ; 
 scalar_t__ omap_rev () ; 
 scalar_t__ omap_type () ; 
 int /*<<< orphan*/  per_pwrdm ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pwrdm_post_transition (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pwrdm_pre_transition (int /*<<< orphan*/ *) ; 
 int pwrdm_read_next_pwrst (int /*<<< orphan*/ ) ; 
 int const pwrdm_read_prev_pwrst (int /*<<< orphan*/ ) ; 
 int pwrdm_read_pwrst (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pwrdm_set_next_pwrst (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sdrc_read_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdrc_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void omap_sram_idle(void)
{
	/* Variable to tell what needs to be saved and restored
	 * in omap_sram_idle*/
	/* save_state = 0 => Nothing to save and restored */
	/* save_state = 1 => Only L1 and logic lost */
	/* save_state = 2 => Only L2 lost */
	/* save_state = 3 => L1, L2 and logic lost */
	int save_state = 0;
	int mpu_next_state = PWRDM_POWER_ON;
	int per_next_state = PWRDM_POWER_ON;
	int core_next_state = PWRDM_POWER_ON;
	u32 sdrc_pwr = 0;

	mpu_next_state = pwrdm_read_next_pwrst(mpu_pwrdm);
	switch (mpu_next_state) {
	case PWRDM_POWER_ON:
	case PWRDM_POWER_RET:
		/* No need to save context */
		save_state = 0;
		break;
	case PWRDM_POWER_OFF:
		save_state = 3;
		break;
	default:
		/* Invalid state */
		pr_err("Invalid mpu state in sram_idle\n");
		return;
	}

	/* NEON control */
	if (pwrdm_read_pwrst(neon_pwrdm) == PWRDM_POWER_ON)
		pwrdm_set_next_pwrst(neon_pwrdm, mpu_next_state);

	/* Enable IO-PAD and IO-CHAIN wakeups */
	per_next_state = pwrdm_read_next_pwrst(per_pwrdm);
	core_next_state = pwrdm_read_next_pwrst(core_pwrdm);

	pwrdm_pre_transition(NULL);

	/* PER */
	if (per_next_state == PWRDM_POWER_OFF)
		cpu_cluster_pm_enter();

	/* CORE */
	if (core_next_state < PWRDM_POWER_ON) {
		if (core_next_state == PWRDM_POWER_OFF) {
			omap3_core_save_context();
			omap3_cm_save_context();
		}
	}

	/* Configure PMIC signaling for I2C4 or sys_off_mode */
	omap3_vc_set_pmic_signaling(core_next_state);

	omap3_intc_prepare_idle();

	/*
	 * On EMU/HS devices ROM code restores a SRDC value
	 * from scratchpad which has automatic self refresh on timeout
	 * of AUTO_CNT = 1 enabled. This takes care of erratum ID i443.
	 * Hence store/restore the SDRC_POWER register here.
	 */
	if (cpu_is_omap3430() && omap_rev() >= OMAP3430_REV_ES3_0 &&
	    (omap_type() == OMAP2_DEVICE_TYPE_EMU ||
	     omap_type() == OMAP2_DEVICE_TYPE_SEC) &&
	    core_next_state == PWRDM_POWER_OFF)
		sdrc_pwr = sdrc_read_reg(SDRC_POWER);

	/*
	 * omap3_arm_context is the location where some ARM context
	 * get saved. The rest is placed on the stack, and restored
	 * from there before resuming.
	 */
	if (save_state)
		omap34xx_save_context(omap3_arm_context);
	if (save_state == 1 || save_state == 3)
		cpu_suspend(save_state, omap34xx_do_sram_idle);
	else
		omap34xx_do_sram_idle(save_state);

	/* Restore normal SDRC POWER settings */
	if (cpu_is_omap3430() && omap_rev() >= OMAP3430_REV_ES3_0 &&
	    (omap_type() == OMAP2_DEVICE_TYPE_EMU ||
	     omap_type() == OMAP2_DEVICE_TYPE_SEC) &&
	    core_next_state == PWRDM_POWER_OFF)
		sdrc_write_reg(sdrc_pwr, SDRC_POWER);

	/* CORE */
	if (core_next_state < PWRDM_POWER_ON &&
	    pwrdm_read_prev_pwrst(core_pwrdm) == PWRDM_POWER_OFF) {
		omap3_core_restore_context();
		omap3_cm_restore_context();
		omap3_sram_restore_context();
		omap2_sms_restore_context();
	} else {
		/*
		 * In off-mode resume path above, omap3_core_restore_context
		 * also handles the INTC autoidle restore done here so limit
		 * this to non-off mode resume paths so we don't do it twice.
		 */
		omap3_intc_resume_idle();
	}

	pwrdm_post_transition(NULL);

	/* PER */
	if (per_next_state == PWRDM_POWER_OFF)
		cpu_cluster_pm_exit();
}