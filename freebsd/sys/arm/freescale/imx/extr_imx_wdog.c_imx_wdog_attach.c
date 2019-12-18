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
typedef  int /*<<< orphan*/  timeout ;
struct imx_wdog_softc {int sc_pde_enabled; int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_ih; int /*<<< orphan*/ * sc_res; int /*<<< orphan*/  sc_mtx; } ;
typedef  int pcell_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  EVENTHANDLER_REGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct imx_wdog_softc*,int /*<<< orphan*/ ) ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_MISC ; 
 size_t IRQRES ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int OF_getencprop (int /*<<< orphan*/ ,char*,int*,int) ; 
 int RD2 (struct imx_wdog_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WDOG_CR_REG ; 
 int WDOG_CR_WDT ; 
 int /*<<< orphan*/  WDOG_ICR_REG ; 
 int WDOG_ICR_WIE ; 
 int WDOG_MCR_PDE ; 
 int /*<<< orphan*/  WDOG_MCR_REG ; 
 int /*<<< orphan*/  WR2 (struct imx_wdog_softc*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct imx_wdog_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct imx_wdog_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  imx_watchdog ; 
 int /*<<< orphan*/  imx_wdog_enable (struct imx_wdog_softc*,int) ; 
 int /*<<< orphan*/  imx_wdog_intr ; 
 int /*<<< orphan*/  imx_wdog_spec ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 scalar_t__ ofw_bus_has_prop (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  watchdog_list ; 

__attribute__((used)) static int
imx_wdog_attach(device_t dev)
{
	struct imx_wdog_softc *sc;
	pcell_t timeout;

	sc = device_get_softc(dev);
	sc->sc_dev = dev;

	if (bus_alloc_resources(dev, imx_wdog_spec, sc->sc_res)) {
		device_printf(dev, "could not allocate resources\n");
		return (ENXIO);
	}

	mtx_init(&sc->sc_mtx, device_get_nameunit(dev), "imx_wdt", MTX_DEF);

	/*
	 * If we're configured to assert an external reset signal, set up the
	 * hardware to do so, and install an interrupt handler whose only
	 * purpose is to backstop the external reset.  Don't worry if the
	 * interrupt setup fails, since it's only a backstop measure.
	 */
	if (ofw_bus_has_prop(sc->sc_dev, "fsl,ext-reset-output")) {
		WR2(sc, WDOG_CR_REG, WDOG_CR_WDT | RD2(sc, WDOG_CR_REG));
		bus_setup_intr(sc->sc_dev, sc->sc_res[IRQRES],
		    INTR_TYPE_MISC | INTR_MPSAFE, imx_wdog_intr, NULL, sc,
		    &sc->sc_ih);
		WR2(sc, WDOG_ICR_REG, WDOG_ICR_WIE); /* Enable, count is 0. */
	}

	/*
	 * Note whether the rom-boot so-called "power-down" watchdog is active,
	 * so we can disable it when the regular watchdog is first enabled.
	 */
	if (RD2(sc, WDOG_MCR_REG) & WDOG_MCR_PDE)
		sc->sc_pde_enabled = true;

	EVENTHANDLER_REGISTER(watchdog_list, imx_watchdog, sc, 0);

	/* If there is a timeout-sec property, activate the watchdog. */
	if (OF_getencprop(ofw_bus_get_node(sc->sc_dev), "timeout-sec",
	    &timeout, sizeof(timeout)) == sizeof(timeout)) {
		if (timeout < 1 || timeout > 128) {
			device_printf(sc->sc_dev, "ERROR: bad timeout-sec "
			    "property value %u, using 128\n", timeout);
			timeout = 128;
		}
		imx_wdog_enable(sc, timeout);
		device_printf(sc->sc_dev, "watchdog enabled using "
		    "timeout-sec property value %u\n", timeout);
	}

	/*
	 * The watchdog hardware cannot be disabled, so there's little point in
	 * coding up a detach() routine to carefully tear everything down, just
	 * make the device busy so that detach can't happen.
	 */
	device_busy(sc->sc_dev);
	return (0);
}