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
 int /*<<< orphan*/  _omap2xxx_apll_disable (int /*<<< orphan*/ ) ; 

void omap2xxx_cm_apll96_disable(void)
{
	_omap2xxx_apll_disable(OMAP24XX_EN_96M_PLL_SHIFT);
}