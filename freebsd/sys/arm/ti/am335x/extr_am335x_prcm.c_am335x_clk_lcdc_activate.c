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
struct ti_clock_dev {int dummy; } ;
struct am335x_prcm_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CM_PER_LCDC_CLKCTRL ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int ENXIO ; 
 int /*<<< orphan*/  am335x_clk_set_arm_disp_freq (struct ti_clock_dev*,int) ; 
 struct am335x_prcm_softc* am335x_prcm_sc ; 
 int prcm_read_4 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prcm_write_4 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
am335x_clk_lcdc_activate(struct ti_clock_dev *clkdev)
{
	struct am335x_prcm_softc *sc = am335x_prcm_sc;

	if (sc == NULL)
		return (ENXIO);

	/*
	 * For now set frequency to 2*VGA_PIXEL_CLOCK 
	 */
	am335x_clk_set_arm_disp_freq(clkdev, 25175000*2);

	/*set MODULEMODE to ENABLE(2) */
	prcm_write_4(CM_PER_LCDC_CLKCTRL, 2);

	/* wait for MODULEMODE to become ENABLE(2) */
	while ((prcm_read_4(CM_PER_LCDC_CLKCTRL) & 0x3) != 2)
		DELAY(10);

	/* wait for IDLEST to become Func(0) */
	while(prcm_read_4(CM_PER_LCDC_CLKCTRL) & (3<<16))
		DELAY(10);

	return (0);
}