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
 int EINVAL ; 
 int /*<<< orphan*/  OMAP_USBTLL_SYSCONFIG ; 
 int /*<<< orphan*/  OMAP_USBTLL_SYSSTATUS ; 
 int TLL_SYSCONFIG_AUTOIDLE ; 
 int TLL_SYSCONFIG_CACTIVITY ; 
 int TLL_SYSCONFIG_ENAWAKEUP ; 
 int TLL_SYSCONFIG_SIDLE_SMART_IDLE ; 
 int TLL_SYSCONFIG_SOFTRESET ; 
 int TLL_SYSSTATUS_RESETDONE ; 
 int /*<<< orphan*/  USBTLL_CLK ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int hz ; 
 int omap_tll_read_4 (struct omap_tll_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_tll_write_4 (struct omap_tll_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pause (char*,int) ; 
 int /*<<< orphan*/  ti_prcm_clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ti_prcm_clk_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
omap_tll_init(struct omap_tll_softc *sc)
{
	unsigned long timeout;
	int ret = 0;

	/* Enable the USB TLL */
	ti_prcm_clk_enable(USBTLL_CLK);

	/* Perform TLL soft reset, and wait until reset is complete */
	omap_tll_write_4(sc, OMAP_USBTLL_SYSCONFIG, TLL_SYSCONFIG_SOFTRESET);

	/* Set the timeout to 100ms*/
	timeout = (hz < 10) ? 1 : ((100 * hz) / 1000);

	/* Wait for TLL reset to complete */
	while ((omap_tll_read_4(sc, OMAP_USBTLL_SYSSTATUS) &
	        TLL_SYSSTATUS_RESETDONE) == 0x00) {

		/* Sleep for a tick */
		pause("USBRESET", 1);

		if (timeout-- == 0) {
			device_printf(sc->sc_dev, "TLL reset operation timed out\n");
			ret = EINVAL;
			goto err_sys_status;
		}
	}

	/* CLOCKACTIVITY = 1 : OCP-derived internal clocks ON during idle
	 * SIDLEMODE = 2     : Smart-idle mode. Sidleack asserted after Idlereq
	 *                     assertion when no more activity on the USB.
	 * ENAWAKEUP = 1     : Wakeup generation enabled
	 */
	omap_tll_write_4(sc, OMAP_USBTLL_SYSCONFIG, TLL_SYSCONFIG_ENAWAKEUP |
	                                            TLL_SYSCONFIG_AUTOIDLE |
	                                            TLL_SYSCONFIG_SIDLE_SMART_IDLE |
	                                            TLL_SYSCONFIG_CACTIVITY);

	return(0);

err_sys_status:
	/* Disable the TLL clocks */
	ti_prcm_clk_disable(USBTLL_CLK);

	return(ret);
}