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
struct clk_hw_omap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OMAP2_APLL_AUTOIDLE_LOW_POWER_STOP ; 
 int /*<<< orphan*/  omap2_apll_set_autoidle (struct clk_hw_omap*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void omap2_apll_allow_idle(struct clk_hw_omap *clk)
{
	omap2_apll_set_autoidle(clk, OMAP2_APLL_AUTOIDLE_LOW_POWER_STOP);
}