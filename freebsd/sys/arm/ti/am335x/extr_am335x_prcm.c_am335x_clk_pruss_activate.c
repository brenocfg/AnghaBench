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
 int /*<<< orphan*/  CLKSEL_PRUSS_OCP_CLK ; 
 int /*<<< orphan*/  CM_PER_PRUSS_CLKCTRL ; 
 int /*<<< orphan*/  CM_PER_PRUSS_CLKSTCTRL ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int ENXIO ; 
 int /*<<< orphan*/  PRM_PER_RSTCTRL ; 
 struct am335x_prcm_softc* am335x_prcm_sc ; 
 int prcm_read_4 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prcm_write_4 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
am335x_clk_pruss_activate(struct ti_clock_dev *clkdev)
{
	struct am335x_prcm_softc *sc = am335x_prcm_sc;

	if (sc == NULL)
		return (ENXIO);

	/* Set MODULEMODE to ENABLE(2) */
	prcm_write_4(CM_PER_PRUSS_CLKCTRL, 2);

	/* Wait for MODULEMODE to become ENABLE(2) */
	while ((prcm_read_4(CM_PER_PRUSS_CLKCTRL) & 0x3) != 2)
		DELAY(10);

	/* Set CLKTRCTRL to SW_WKUP(2) */
	prcm_write_4(CM_PER_PRUSS_CLKSTCTRL, 2);

	/* Wait for the 200 MHz OCP clock to become active */
	while ((prcm_read_4(CM_PER_PRUSS_CLKSTCTRL) & (1<<4)) == 0)
		DELAY(10);

	/* Wait for the 200 MHz IEP clock to become active */
	while ((prcm_read_4(CM_PER_PRUSS_CLKSTCTRL) & (1<<5)) == 0)
		DELAY(10);

	/* Wait for the 192 MHz UART clock to become active */
	while ((prcm_read_4(CM_PER_PRUSS_CLKSTCTRL) & (1<<6)) == 0)
		DELAY(10);

	/* Select L3F as OCP clock */
	prcm_write_4(CLKSEL_PRUSS_OCP_CLK, 0);
	while ((prcm_read_4(CLKSEL_PRUSS_OCP_CLK) & 0x3) != 0)
		DELAY(10);

	/* Clear the RESET bit */
	prcm_write_4(PRM_PER_RSTCTRL, prcm_read_4(PRM_PER_RSTCTRL) & ~2);

	return (0);
}