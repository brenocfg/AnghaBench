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
struct clk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCM63XX_RESET_SAR ; 
 int /*<<< orphan*/  BCMCPU_IS_6368 () ; 
 int /*<<< orphan*/  CKCTL_6368_SAR_EN ; 
 int /*<<< orphan*/  bcm63xx_core_set_reset (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bcm_hwclock_set (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  clk_disable_unlocked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_enable_unlocked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_swpkt_sar ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static void xtm_set(struct clk *clk, int enable)
{
	if (!BCMCPU_IS_6368())
		return;

	if (enable)
		clk_enable_unlocked(&clk_swpkt_sar);
	else
		clk_disable_unlocked(&clk_swpkt_sar);

	bcm_hwclock_set(CKCTL_6368_SAR_EN, enable);

	if (enable) {
		/* reset sar core afer clock change */
		bcm63xx_core_set_reset(BCM63XX_RESET_SAR, 1);
		mdelay(1);
		bcm63xx_core_set_reset(BCM63XX_RESET_SAR, 0);
		mdelay(1);
	}
}