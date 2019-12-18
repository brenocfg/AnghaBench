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
 int /*<<< orphan*/  CM_PER_CPGMAC0_CLKCTRL ; 
 int /*<<< orphan*/  CM_PER_CPSW_CLKSTCTRL ; 
 int ENXIO ; 
 struct am335x_prcm_softc* am335x_prcm_sc ; 
 int prcm_read_4 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prcm_write_4 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
am335x_clk_cpsw_activate(struct ti_clock_dev *clkdev)
{
	struct am335x_prcm_softc *sc = am335x_prcm_sc;

	if (sc == NULL)
		return ENXIO;

	/* set MODULENAME to ENABLE */
	prcm_write_4(CM_PER_CPGMAC0_CLKCTRL, 2);

	/* wait for IDLEST to become Func(0) */
	while(prcm_read_4(CM_PER_CPGMAC0_CLKCTRL) & (3<<16));

	/*set CLKTRCTRL to SW_WKUP(2) */
	prcm_write_4(CM_PER_CPSW_CLKSTCTRL, 2);

	/* wait for 125 MHz OCP clock to become active */
	while((prcm_read_4(CM_PER_CPSW_CLKSTCTRL) & (1<<4)) == 0);
	return(0);
}