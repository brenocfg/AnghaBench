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
struct bcmwd_softc {int wdog_period; int /*<<< orphan*/  mtx; int /*<<< orphan*/  regs_offset; int /*<<< orphan*/ * res; int /*<<< orphan*/  bsh; int /*<<< orphan*/  bst; int /*<<< orphan*/  dev; scalar_t__ wdog_armed; int /*<<< orphan*/  wdog_passwd; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {scalar_t__ ocd_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCM2835_PASSWORD ; 
 int ENXIO ; 
 int /*<<< orphan*/  EVENTHANDLER_REGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bcmwd_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 scalar_t__ UPSTREAM_DTB ; 
 int /*<<< orphan*/  UPSTREAM_DTB_REGS_OFFSET ; 
 struct bcmwd_softc* bcmwd_lsc ; 
 int /*<<< orphan*/  bcmwd_watchdog_fn ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compat_data ; 
 struct bcmwd_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* ofw_bus_search_compatible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  watchdog_list ; 

__attribute__((used)) static int
bcmwd_attach(device_t dev)
{
	struct bcmwd_softc *sc;
	int rid;

	if (bcmwd_lsc != NULL)
		return (ENXIO);

	sc = device_get_softc(dev);
	sc->wdog_period = 7;
	sc->wdog_passwd = BCM2835_PASSWORD;
	sc->wdog_armed = 0;
	sc->dev = dev;

	rid = 0;
	sc->res = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid, RF_ACTIVE);
	if (sc->res == NULL) {
		device_printf(dev, "could not allocate memory resource\n");
		return (ENXIO);
	}

	sc->bst = rman_get_bustag(sc->res);
	sc->bsh = rman_get_bushandle(sc->res);

	/* compensate base address difference */
	if (ofw_bus_search_compatible(dev, compat_data)->ocd_data
	   == UPSTREAM_DTB)
		sc->regs_offset = UPSTREAM_DTB_REGS_OFFSET;

	bcmwd_lsc = sc;
	mtx_init(&sc->mtx, "BCM2835 Watchdog", "bcmwd", MTX_DEF);
	EVENTHANDLER_REGISTER(watchdog_list, bcmwd_watchdog_fn, sc, 0);

	return (0);
}