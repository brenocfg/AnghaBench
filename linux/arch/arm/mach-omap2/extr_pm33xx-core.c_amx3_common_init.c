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

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ OMAP2_DEVICE_TYPE_GP ; 
 int /*<<< orphan*/  PWRDM_POWER_OFF ; 
 void* cefuse_pwrdm ; 
 int /*<<< orphan*/  clkdm_for_each (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* gfx_pwrdm ; 
 void* mpu_pwrdm ; 
 int /*<<< orphan*/  omap_pm_clkdms_setup ; 
 int /*<<< orphan*/  omap_set_pwrdm_state (void*,int /*<<< orphan*/ ) ; 
 scalar_t__ omap_type () ; 
 void* per_pwrdm ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 void* pwrdm_lookup (char*) ; 

__attribute__((used)) static int amx3_common_init(void)
{
	gfx_pwrdm = pwrdm_lookup("gfx_pwrdm");
	per_pwrdm = pwrdm_lookup("per_pwrdm");
	mpu_pwrdm = pwrdm_lookup("mpu_pwrdm");

	if ((!gfx_pwrdm) || (!per_pwrdm) || (!mpu_pwrdm))
		return -ENODEV;

	(void)clkdm_for_each(omap_pm_clkdms_setup, NULL);

	/* CEFUSE domain can be turned off post bootup */
	cefuse_pwrdm = pwrdm_lookup("cefuse_pwrdm");
	if (!cefuse_pwrdm)
		pr_err("PM: Failed to get cefuse_pwrdm\n");
	else if (omap_type() != OMAP2_DEVICE_TYPE_GP)
		pr_info("PM: Leaving EFUSE power domain active\n");
	else
		omap_set_pwrdm_state(cefuse_pwrdm, PWRDM_POWER_OFF);

	return 0;
}