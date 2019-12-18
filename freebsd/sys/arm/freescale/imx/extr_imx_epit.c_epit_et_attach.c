#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_2__ {char* et_name; int et_flags; int et_quality; int et_frequency; int et_min_period; int et_max_period; struct epit_softc* et_priv; int /*<<< orphan*/  et_stop; int /*<<< orphan*/  et_start; } ;
struct epit_softc {int clkfreq; TYPE_1__ et; int /*<<< orphan*/  ctlreg; int /*<<< orphan*/  dev; int /*<<< orphan*/  inthandle; int /*<<< orphan*/ * intres; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  EPIT_CR_OCIEN ; 
 int ET_FLAGS_ONESHOT ; 
 int ET_FLAGS_PERIODIC ; 
 scalar_t__ ET_MAX_TICKS ; 
 scalar_t__ ET_MIN_TICKS ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_CLK ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct epit_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  epit_et_start ; 
 int /*<<< orphan*/  epit_et_stop ; 
 int /*<<< orphan*/  epit_intr ; 
 int /*<<< orphan*/  et_register (TYPE_1__*) ; 

__attribute__((used)) static int
epit_et_attach(struct epit_softc *sc)
{
	int err, rid;

	rid = 0;
	sc->intres = bus_alloc_resource_any(sc->dev, SYS_RES_IRQ, &rid,
	    RF_ACTIVE);
	if (sc->intres == NULL) {
		device_printf(sc->dev, "could not allocate interrupt\n");
		return (ENXIO);
	}

	err = bus_setup_intr(sc->dev, sc->intres, INTR_TYPE_CLK | INTR_MPSAFE,
	    epit_intr, NULL, sc, &sc->inthandle);
	if (err != 0) {
		device_printf(sc->dev, "unable to setup the irq handler\n");
		return (err);
	}

	/* To be an eventtimer, we need interrupts enabled. */
	sc->ctlreg |= EPIT_CR_OCIEN;

	/* Register as an eventtimer. */
	sc->et.et_name = "EPIT";
	sc->et.et_flags = ET_FLAGS_ONESHOT | ET_FLAGS_PERIODIC;
	sc->et.et_quality = 1000;
	sc->et.et_frequency = sc->clkfreq;
	sc->et.et_min_period = ((uint64_t)ET_MIN_TICKS  << 32) / sc->clkfreq;
	sc->et.et_max_period = ((uint64_t)ET_MAX_TICKS  << 32) / sc->clkfreq;
	sc->et.et_start = epit_et_start;
	sc->et.et_stop = epit_et_stop;
	sc->et.et_priv = sc;
	et_register(&sc->et);

	return (0);
}