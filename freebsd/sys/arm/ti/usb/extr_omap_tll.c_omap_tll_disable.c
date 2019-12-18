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
struct omap_tll_softc {int /*<<< orphan*/  sc_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  OMAP_USBTLL_SYSCONFIG ; 
 int /*<<< orphan*/  OMAP_USBTLL_SYSSTATUS ; 
 int /*<<< orphan*/  USBTLL_CLK ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int hz ; 
 int omap_tll_read_4 (struct omap_tll_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_tll_write_4 (struct omap_tll_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pause (char*,int) ; 
 int /*<<< orphan*/  ti_prcm_clk_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
omap_tll_disable(struct omap_tll_softc *sc)
{
	unsigned long timeout;

	timeout = (hz < 10) ? 1 : ((100 * hz) / 1000);

	/* Reset the TLL module */
	omap_tll_write_4(sc, OMAP_USBTLL_SYSCONFIG, 0x0002);
	while ((omap_tll_read_4(sc, OMAP_USBTLL_SYSSTATUS) & (0x01)) == 0x00) {
		/* Sleep for a tick */
		pause("USBRESET", 1);

		if (timeout-- == 0) {
			device_printf(sc->sc_dev, "operation timed out\n");
			break;
		}
	}

	/* Disable functional and interface clocks for the TLL and HOST modules */
	ti_prcm_clk_disable(USBTLL_CLK);
}