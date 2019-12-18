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
typedef  enum reboot_mode { ____Placeholder_reboot_mode } reboot_mode ;

/* Variables and functions */
 int /*<<< orphan*/  clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_set_rate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_prm_reset_system () ; 
 int /*<<< orphan*/  reset_sys_ck ; 
 int /*<<< orphan*/  reset_virt_prcm_set_ck ; 

void omap2xxx_restart(enum reboot_mode mode, const char *cmd)
{
	u32 rate;

	rate = clk_get_rate(reset_sys_ck);
	clk_set_rate(reset_virt_prcm_set_ck, rate);

	/* XXX Should save the cmd argument for use after the reboot */

	omap_prm_reset_system();
}