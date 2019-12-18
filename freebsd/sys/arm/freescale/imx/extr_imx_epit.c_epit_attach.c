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
typedef  int uint32_t ;
struct epit_softc {int clkfreq; int ctlreg; int /*<<< orphan*/  dev; int /*<<< orphan*/ * memres; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  EPIT_CR ; 
#define  EPIT_CR_CLKSRC_HFCLK 130 
#define  EPIT_CR_CLKSRC_IPG 129 
#define  EPIT_CR_CLKSRC_LFCLK 128 
 int EPIT_CR_CLKSRC_SHIFT ; 
 int EPIT_CR_DBGEN ; 
 int EPIT_CR_ENMOD ; 
 int EPIT_CR_RLD ; 
 int EPIT_CR_STOPEN ; 
 int EPIT_CR_SWR ; 
 int EPIT_CR_WAITEN ; 
 int RD4 (struct epit_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  WR4 (struct epit_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WR4B (struct epit_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 struct epit_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int epit_et_attach (struct epit_softc*) ; 
 int epit_tc_attach (struct epit_softc*) ; 
 int imx_ccm_ipg_hz () ; 
 int imx_ccm_perclk_hz () ; 

__attribute__((used)) static int
epit_attach(device_t dev)
{
	struct epit_softc *sc;
	int err, rid;
	uint32_t clksrc;

	sc = device_get_softc(dev);
	sc->dev = dev;

	rid = 0;
	sc->memres = bus_alloc_resource_any(sc->dev, SYS_RES_MEMORY, &rid,
	    RF_ACTIVE);
	if (sc->memres == NULL) {
		device_printf(sc->dev, "could not allocate registers\n");
		return (ENXIO);
	}

	/*
	 * For now, use ipg (66 MHz).  Some day we should get this from fdt.
	 */
	clksrc = EPIT_CR_CLKSRC_IPG;

	switch (clksrc) {
	default:
		device_printf(dev, 
		    "Unsupported clock source '%d', using IPG\n", clksrc);
                /* FALLTHROUGH */
	case EPIT_CR_CLKSRC_IPG:
		sc->clkfreq = imx_ccm_ipg_hz();
		break;
	case EPIT_CR_CLKSRC_HFCLK:
		sc->clkfreq = imx_ccm_perclk_hz();
		break;
	case EPIT_CR_CLKSRC_LFCLK:
		sc->clkfreq = 32768;
		break;
	}

	/*
	 * Init: stop operations and clear all options, then set up options and
	 * clock source, then do a soft-reset and wait for it to complete.
	 */
	WR4(sc, EPIT_CR, 0);

	sc->ctlreg =
	    (clksrc << EPIT_CR_CLKSRC_SHIFT) |  /* Use selected clock */
	    EPIT_CR_ENMOD  |                    /* Reload counter on enable */
	    EPIT_CR_RLD    |                    /* Reload counter from LR */
	    EPIT_CR_STOPEN |                    /* Run in STOP mode */
	    EPIT_CR_WAITEN |                    /* Run in WAIT mode */
	    EPIT_CR_DBGEN;                      /* Run in DEBUG mode */

	WR4B(sc, EPIT_CR, sc->ctlreg | EPIT_CR_SWR);
	while (RD4(sc, EPIT_CR) & EPIT_CR_SWR)
		continue;

	/*
	 * Unit 0 is the timecounter, 1 (if instantiated) is the eventtimer.
	 */
	if (device_get_unit(sc->dev) == 0)
		err = epit_tc_attach(sc);
	else
		err = epit_et_attach(sc);

	return (err);
}