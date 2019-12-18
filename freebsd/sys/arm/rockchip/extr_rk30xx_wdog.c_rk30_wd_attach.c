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
struct rk30_wd_softc {int freq; int /*<<< orphan*/  mtx; int /*<<< orphan*/ * res; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int pcell_t ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  cell ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  EVENTHANDLER_REGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rk30_wd_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MTX_DEF ; 
 scalar_t__ OF_getencprop (int /*<<< orphan*/ ,char*,int*,int) ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 struct rk30_wd_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 struct rk30_wd_softc* rk30_wd_sc ; 
 int /*<<< orphan*/  rk30_wd_watchdog_fn ; 
 int /*<<< orphan*/  watchdog_list ; 

__attribute__((used)) static int
rk30_wd_attach(device_t dev)
{
	struct rk30_wd_softc *sc;
	int rid;
	phandle_t node;
	pcell_t cell;

	if (rk30_wd_sc != NULL)
		return (ENXIO);

	sc = device_get_softc(dev);
	sc->dev = dev;

	node = ofw_bus_get_node(sc->dev);
	if (OF_getencprop(node, "clock-frequency", &cell, sizeof(cell)) > 0)
		sc->freq = cell / 1000000;
	else
		return (ENXIO);

	rid = 0;
	sc->res = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid, RF_ACTIVE);
	if (sc->res == NULL) {
		device_printf(dev, "could not allocate memory resource\n");
		return (ENXIO);
	}

	rk30_wd_sc = sc;
	mtx_init(&sc->mtx, "RK30XX Watchdog", "rk30_wd", MTX_DEF);
	EVENTHANDLER_REGISTER(watchdog_list, rk30_wd_watchdog_fn, sc, 0);

	return (0);
}