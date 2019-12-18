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
 int PWRDM_POWER_OFF ; 
 int /*<<< orphan*/  gfx_pwrdm ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int pwrdm_read_pwrst (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void amx3_post_suspend_common(void)
{
	int status;
	/*
	 * Because gfx_pwrdm is the only one under MPU control,
	 * comment on transition status
	 */
	status = pwrdm_read_pwrst(gfx_pwrdm);
	if (status != PWRDM_POWER_OFF)
		pr_err("PM: GFX domain did not transition: %x\n", status);
}