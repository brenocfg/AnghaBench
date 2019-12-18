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
 int amx3_common_init () ; 
 int /*<<< orphan*/  clkdm_lookup (char*) ; 
 int /*<<< orphan*/  gfx_l4ls_clkdm ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int am33xx_suspend_init(void)
{
	int ret;

	gfx_l4ls_clkdm = clkdm_lookup("gfx_l4ls_gfx_clkdm");

	if (!gfx_l4ls_clkdm) {
		pr_err("PM: Cannot lookup gfx_l4ls_clkdm clockdomains\n");
		return -ENODEV;
	}

	ret = amx3_common_init();

	return ret;
}