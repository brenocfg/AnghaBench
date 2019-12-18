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
struct ccm_softc {int /*<<< orphan*/  dev; int /*<<< orphan*/ * res; int /*<<< orphan*/  bsh; int /*<<< orphan*/  bst; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CCM_CCGR (int) ; 
 int CCM_CCGRN ; 
 int /*<<< orphan*/  CCM_CCR ; 
 int /*<<< orphan*/  CCM_CSR ; 
 int ENXIO ; 
 int FIRC_EN ; 
 int FXOSC_EN ; 
 int FXOSC_RDY ; 
 int READ4 (struct ccm_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE4 (struct ccm_softc*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ccm_fdt_set (struct ccm_softc*) ; 
 int /*<<< orphan*/  ccm_spec ; 
 int /*<<< orphan*/  cpufunc_nullop () ; 
 struct ccm_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ccm_attach(device_t dev)
{
	struct ccm_softc *sc;
	int reg;
	int i;

	sc = device_get_softc(dev);
	sc->dev = dev;

	if (bus_alloc_resources(dev, ccm_spec, sc->res)) {
		device_printf(dev, "could not allocate resources\n");
		return (ENXIO);
	}

	/* Memory interface */
	sc->bst = rman_get_bustag(sc->res[0]);
	sc->bsh = rman_get_bushandle(sc->res[0]);

	/* Enable oscillator */
	reg = READ4(sc, CCM_CCR);
	reg |= (FIRC_EN | FXOSC_EN);
	WRITE4(sc, CCM_CCR, reg);

	/* Wait 10 times */
	for (i = 0; i < 10; i++) {
		if (READ4(sc, CCM_CSR) & FXOSC_RDY) {
			device_printf(sc->dev, "On board oscillator is ready.\n");
			break;
		}

		cpufunc_nullop();
	}

	/* Clock is on during all modes, except stop mode. */
	for (i = 0; i < CCM_CCGRN; i++) {
		WRITE4(sc, CCM_CCGR(i), 0xffffffff);
	}

	/* Take and apply FDT clocks */
	ccm_fdt_set(sc);

	return (0);
}