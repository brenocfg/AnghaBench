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
struct timespec {int /*<<< orphan*/  tv_nsec; scalar_t__ tv_sec; } ;
struct mk48txx_softc {int sc_year0; int sc_flag; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/ * sc_res; int /*<<< orphan*/ * sc_model; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int MK48TXX_WDOG_ENABLE_WDS ; 
 int MK48TXX_WDOG_REGISTER ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int OF_getproplen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 struct mk48txx_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int mk48txx_attach (int /*<<< orphan*/ ) ; 
 scalar_t__ mk48txx_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ofw_bus_get_model (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sparc64_model ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
eeprom_attach(device_t dev)
{
	struct mk48txx_softc *sc;
	struct timespec ts;
	int error, rid;

	sc = device_get_softc(dev);

	mtx_init(&sc->sc_mtx, "eeprom_mtx", NULL, MTX_DEF);

	rid = 0;
	sc->sc_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid,
	    RF_ACTIVE);
	if (sc->sc_res == NULL) {
		device_printf(dev, "cannot allocate resources\n");
		error = ENXIO;
		goto fail_mtx;
	}

	if ((sc->sc_model = ofw_bus_get_model(dev)) == NULL) {
		device_printf(dev, "cannot determine model\n");
		error = ENXIO;
		goto fail_res;
	}

	/* Our TOD clock year 0 is 1968. */
	sc->sc_year0 = 1968;
	/* Use default register read/write functions. */
	sc->sc_flag = 0;
	/*
	 * Generally, if the `eeprom' node has a `watchdog-enable' property
	 * this indicates that the watchdog part of the MK48T59 is usable,
	 * i.e. its RST pin is connected to the WDR input of the CPUs or
	 * something. The `eeprom' nodes of E250, E450 and the clock board
	 * variant in Exx00 have such properties. For E250 and E450 the
	 * watchdog just works, for Exx00 the delivery of the reset signal
	 * apparently has to be additionally enabled elsewhere...
	 * The OFW environment variable `watchdog-reboot?' is ignored for
	 * these watchdogs as they always trigger a system reset when they
	 * time out and can't be made to issue a break to the boot monitor
	 * instead.
	 */
	if (OF_getproplen(ofw_bus_get_node(dev), "watchdog-enable") != -1 &&
	    (strcmp(sparc64_model, "SUNW,Ultra-250") == 0 ||
	    strcmp(sparc64_model, "SUNW,Ultra-4") == 0))
		sc->sc_flag |= MK48TXX_WDOG_REGISTER | MK48TXX_WDOG_ENABLE_WDS;
	if ((error = mk48txx_attach(dev)) != 0) {
		device_printf(dev, "cannot attach time of day clock\n");
		goto fail_res;
	}

	if (bootverbose) {
		if (mk48txx_gettime(dev, &ts) != 0)
			device_printf(dev, "invalid time");
		else
			device_printf(dev, "current time: %ld.%09ld\n",
			    (long)ts.tv_sec, ts.tv_nsec);
	}

	return (0);

 fail_res:
	bus_release_resource(dev, SYS_RES_MEMORY, rid, sc->sc_res);
 fail_mtx:
	mtx_destroy(&sc->sc_mtx);

	return (error);
}