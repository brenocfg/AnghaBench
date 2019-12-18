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
 int /*<<< orphan*/  AM43XX_RM_GFX_RSTCTRL_OFFSET ; 
 int /*<<< orphan*/  AM43XX_RM_GFX_RSTST_OFFSET ; 
 int /*<<< orphan*/  AM43XX_RM_PER_RSTCTRL_OFFSET ; 
 int /*<<< orphan*/  AM43XX_RM_PER_RSTST_OFFSET ; 
 int /*<<< orphan*/  RSTCTRL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RSTST (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  am33xx_gfx_hwmod ; 
 int /*<<< orphan*/  am33xx_pruss_hwmod ; 

__attribute__((used)) static void omap_hwmod_am43xx_rst(void)
{
	RSTCTRL(am33xx_pruss_hwmod, AM43XX_RM_PER_RSTCTRL_OFFSET);
	RSTCTRL(am33xx_gfx_hwmod, AM43XX_RM_GFX_RSTCTRL_OFFSET);
	RSTST(am33xx_pruss_hwmod, AM43XX_RM_PER_RSTST_OFFSET);
	RSTST(am33xx_gfx_hwmod, AM43XX_RM_GFX_RSTST_OFFSET);
}