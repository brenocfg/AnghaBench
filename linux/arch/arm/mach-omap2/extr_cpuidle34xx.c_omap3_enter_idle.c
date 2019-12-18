#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct omap3_idle_statedata {int flags; scalar_t__ mpu_state; scalar_t__ core_state; } ;
struct cpuidle_driver {int dummy; } ;
struct cpuidle_device {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/ * pwrdm_clkdms; } ;

/* Variables and functions */
 int OMAP_CPUIDLE_CX_NO_CLKDM_IDLE ; 
 scalar_t__ PWRDM_POWER_OFF ; 
 int /*<<< orphan*/  clkdm_allow_idle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clkdm_deny_idle (int /*<<< orphan*/ ) ; 
 TYPE_1__* core_pd ; 
 int /*<<< orphan*/  cpu_pm_enter () ; 
 int /*<<< orphan*/  cpu_pm_exit () ; 
 TYPE_1__* mpu_pd ; 
 scalar_t__ need_resched () ; 
 struct omap3_idle_statedata* omap3_idle_data ; 
 scalar_t__ omap_irq_pending () ; 
 int /*<<< orphan*/  omap_sram_idle () ; 
 scalar_t__ pwrdm_read_prev_pwrst (TYPE_1__*) ; 
 int /*<<< orphan*/  pwrdm_set_next_pwrst (TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static int omap3_enter_idle(struct cpuidle_device *dev,
			    struct cpuidle_driver *drv,
			    int index)
{
	struct omap3_idle_statedata *cx = &omap3_idle_data[index];

	if (omap_irq_pending() || need_resched())
		goto return_sleep_time;

	/* Deny idle for C1 */
	if (cx->flags & OMAP_CPUIDLE_CX_NO_CLKDM_IDLE) {
		clkdm_deny_idle(mpu_pd->pwrdm_clkdms[0]);
	} else {
		pwrdm_set_next_pwrst(mpu_pd, cx->mpu_state);
		pwrdm_set_next_pwrst(core_pd, cx->core_state);
	}

	/*
	 * Call idle CPU PM enter notifier chain so that
	 * VFP context is saved.
	 */
	if (cx->mpu_state == PWRDM_POWER_OFF)
		cpu_pm_enter();

	/* Execute ARM wfi */
	omap_sram_idle();

	/*
	 * Call idle CPU PM enter notifier chain to restore
	 * VFP context.
	 */
	if (cx->mpu_state == PWRDM_POWER_OFF &&
	    pwrdm_read_prev_pwrst(mpu_pd) == PWRDM_POWER_OFF)
		cpu_pm_exit();

	/* Re-allow idle for C1 */
	if (cx->flags & OMAP_CPUIDLE_CX_NO_CLKDM_IDLE)
		clkdm_allow_idle(mpu_pd->pwrdm_clkdms[0]);

return_sleep_time:

	return index;
}