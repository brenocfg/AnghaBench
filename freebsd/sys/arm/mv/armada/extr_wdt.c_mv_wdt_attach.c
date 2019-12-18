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
struct mv_wdt_softc {struct mv_wdt_config* wdt_config; int /*<<< orphan*/  wdt_mtx; int /*<<< orphan*/  wdt_res; } ;
struct mv_wdt_config {scalar_t__ wdt_clock_src; int /*<<< orphan*/  (* wdt_disable ) () ;} ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {scalar_t__ ocd_data; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  EVENTHANDLER_REGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mv_wdt_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct mv_wdt_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ get_tclk () ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mv_watchdog_event ; 
 int /*<<< orphan*/  mv_wdt_compat ; 
 int /*<<< orphan*/  mv_wdt_spec ; 
 TYPE_1__* ofw_bus_search_compatible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  watchdog_list ; 
 struct mv_wdt_softc* wdt_softc ; 

__attribute__((used)) static int
mv_wdt_attach(device_t dev)
{
	struct mv_wdt_softc *sc;
	int error;

	if (wdt_softc != NULL)
		return (ENXIO);

	sc = device_get_softc(dev);
	wdt_softc = sc;

	error = bus_alloc_resources(dev, mv_wdt_spec, &sc->wdt_res);
	if (error) {
		device_printf(dev, "could not allocate resources\n");
		return (ENXIO);
	}

	mtx_init(&sc->wdt_mtx, "watchdog", NULL, MTX_DEF);

	sc->wdt_config = (struct mv_wdt_config *)
	   ofw_bus_search_compatible(dev, mv_wdt_compat)->ocd_data;

	if (sc->wdt_config->wdt_clock_src == 0)
		sc->wdt_config->wdt_clock_src = get_tclk();

	if (wdt_softc->wdt_config->wdt_disable != NULL)
		wdt_softc->wdt_config->wdt_disable();
	EVENTHANDLER_REGISTER(watchdog_list, mv_watchdog_event, sc, 0);

	return (0);
}