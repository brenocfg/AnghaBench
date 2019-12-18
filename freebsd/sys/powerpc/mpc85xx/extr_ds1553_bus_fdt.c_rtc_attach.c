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
struct ds1553_softc {int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/ * res; int /*<<< orphan*/  rid; int /*<<< orphan*/  sc_bsh; int /*<<< orphan*/  sc_bst; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  MTX_SPIN ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bzero (struct ds1553_softc*,int) ; 
 int /*<<< orphan*/  clock_register (int /*<<< orphan*/ ,int) ; 
 struct ds1553_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int ds1553_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ds1553_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
rtc_attach(device_t dev)
{
	struct timespec ts;
	struct ds1553_softc *sc;
	int error;

	sc = device_get_softc(dev);
	bzero(sc, sizeof(struct ds1553_softc));

	mtx_init(&sc->sc_mtx, "rtc_mtx", NULL, MTX_SPIN);

	sc->res = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &sc->rid,
	    RF_ACTIVE);
	if (sc->res == NULL) {
		device_printf(dev, "cannot allocate resources\n");
		mtx_destroy(&sc->sc_mtx);
		return (ENXIO);
	}

	sc->sc_bst = rman_get_bustag(sc->res);
	sc->sc_bsh = rman_get_bushandle(sc->res);

	if ((error = ds1553_attach(dev)) != 0) {
		device_printf(dev, "cannot attach time of day clock\n");
		bus_release_resource(dev, SYS_RES_MEMORY, sc->rid, sc->res);
		mtx_destroy(&sc->sc_mtx);
		return (error);
	}

	clock_register(dev, 1000000);

	if (bootverbose) {
		ds1553_gettime(dev, &ts);
		device_printf(dev, "current time: %ld.%09ld\n",
		    (long)ts.tv_sec, ts.tv_nsec);
	}

	return (0);
}