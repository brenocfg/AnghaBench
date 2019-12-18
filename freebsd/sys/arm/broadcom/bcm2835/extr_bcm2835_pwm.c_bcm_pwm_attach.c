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
struct bcm_pwm_softc {int freq; int period; int ratio; int period2; int ratio2; int /*<<< orphan*/  sc_mem_res; int /*<<< orphan*/  sc_m_bsh; int /*<<< orphan*/  sc_m_bst; int /*<<< orphan*/ * clkman; int /*<<< orphan*/  sc_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bcm_pwm_sysctl_init (struct bcm_pwm_softc*) ; 
 int /*<<< orphan*/  bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devclass_find (char*) ; 
 int /*<<< orphan*/ * devclass_get_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bcm_pwm_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bcm_pwm_attach(device_t dev)
{
	struct bcm_pwm_softc *sc;
	int rid;

	if (device_get_unit(dev) != 0) {
		device_printf(dev, "only one PWM controller supported\n");
		return (ENXIO);
	}

	sc = device_get_softc(dev);
	sc->sc_dev = dev;

	sc->clkman = devclass_get_device(devclass_find("bcm2835_clkman"), 0);
	if (sc->clkman == NULL) {
		device_printf(dev, "cannot find Clock Manager\n");
		return (ENXIO);
	}

	rid = 0;
	sc->sc_mem_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid,
	    RF_ACTIVE);
	if (!sc->sc_mem_res) {
		device_printf(dev, "cannot allocate memory window\n");
		return (ENXIO);
	}

	sc->sc_m_bst = rman_get_bustag(sc->sc_mem_res);
	sc->sc_m_bsh = rman_get_bushandle(sc->sc_mem_res);

	/* Add sysctl nodes. */
	bcm_pwm_sysctl_init(sc);

	sc->freq = 125000000; /* 125 Mhz */
	sc->period = 10000;   /* 12.5 khz */
	sc->ratio = 2500;     /* 25% */
	sc->period2 = 10000;  /* 12.5 khz */
	sc->ratio2 = 2500;    /* 25% */

	return (bus_generic_attach(dev));
}