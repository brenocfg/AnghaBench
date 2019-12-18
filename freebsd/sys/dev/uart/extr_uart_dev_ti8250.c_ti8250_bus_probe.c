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
struct uart_softc {int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_bas; } ;
typedef  scalar_t__ clk_ident_t ;

/* Variables and functions */
 scalar_t__ INVALID_CLK_IDENT ; 
 int /*<<< orphan*/  MDR1_MODE_DISABLE ; 
 int /*<<< orphan*/  MDR1_MODE_UART ; 
 int /*<<< orphan*/  MDR1_REG ; 
 int /*<<< orphan*/  SYSCC_REG ; 
 int /*<<< orphan*/  SYSCC_SOFTRESET ; 
 int /*<<< orphan*/  SYSS_REG ; 
 int SYSS_STATUS_RESETDONE ; 
 scalar_t__ UART1_CLK ; 
 scalar_t__ device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 int ns8250_bus_probe (struct uart_softc*) ; 
 scalar_t__ ti_hwmods_get_clock (int /*<<< orphan*/ ) ; 
 int ti_prcm_clk_enable (scalar_t__) ; 
 int uart_getreg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_setreg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ti8250_bus_probe(struct uart_softc *sc)
{
	int status;
	clk_ident_t clkid;

	/* Enable clocks for this device.  We can't continue if that fails.  */
	clkid = ti_hwmods_get_clock(sc->sc_dev);
	if (clkid == INVALID_CLK_IDENT) {
		device_printf(sc->sc_dev,
		    "failed to get clock based on hwmods\n");
		clkid = UART1_CLK + device_get_unit(sc->sc_dev);
	}
	if ((status = ti_prcm_clk_enable(clkid)) != 0)
		return (status);

	/*
	 * Set the hardware to disabled mode, do a full device reset, then set
	 * it to uart mode.  Most devices will be reset-and-disabled already,
	 * but you never know what a bootloader might have done.
	 */
	uart_setreg(&sc->sc_bas, MDR1_REG, MDR1_MODE_DISABLE);
	uart_setreg(&sc->sc_bas, SYSCC_REG, SYSCC_SOFTRESET);
	while (uart_getreg(&sc->sc_bas, SYSS_REG) & SYSS_STATUS_RESETDONE)
		continue;
	uart_setreg(&sc->sc_bas, MDR1_REG, MDR1_MODE_UART);

	status = ns8250_bus_probe(sc); 
	if (status == 0)
		device_set_desc(sc->sc_dev, "TI UART (16550 compatible)");

	return (status);
}