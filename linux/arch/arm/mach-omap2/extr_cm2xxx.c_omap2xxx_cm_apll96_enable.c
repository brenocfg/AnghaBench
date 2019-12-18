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
 int /*<<< orphan*/  OMAP24XX_EN_96M_PLL_SHIFT ; 
 int /*<<< orphan*/  OMAP24XX_ST_96M_APLL_SHIFT ; 
 int _omap2xxx_apll_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int omap2xxx_cm_apll96_enable(void)
{
	return _omap2xxx_apll_enable(OMAP24XX_EN_96M_PLL_SHIFT,
				     OMAP24XX_ST_96M_APLL_SHIFT);
}