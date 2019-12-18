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
struct imx_wdog_softc {int /*<<< orphan*/ * sc_res; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_SPACE_PHYSADDR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int FILTER_HANDLED ; 
 size_t MEMRES ; 
 int /*<<< orphan*/  WDOG_CR_REG ; 
 int /*<<< orphan*/  imx_wdog_cpu_reset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
imx_wdog_intr(void *arg)
{
	struct imx_wdog_softc *sc = arg;

	/*
	 * When configured for external reset, the actual reset is supposed to
	 * happen when some external device responds to the assertion of the
	 * WDOG_B signal by asserting the POR signal to the chip.  This
	 * interrupt handler is a backstop mechanism; it is set up to fire
	 * simultaneously with WDOG_B, and if the external reset happens we'll
	 * never actually make it to here.  If we do make it here, just trigger
	 * a software reset.  That code will see that external reset is
	 * configured, and it will wait for 1 second for it to take effect, then
	 * it will do a software reset as a fallback.
	 */
	imx_wdog_cpu_reset(BUS_SPACE_PHYSADDR(sc->sc_res[MEMRES], WDOG_CR_REG));

	return (FILTER_HANDLED); /* unreached */
}