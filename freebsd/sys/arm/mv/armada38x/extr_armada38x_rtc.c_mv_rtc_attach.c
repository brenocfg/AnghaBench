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
struct mv_rtc_softc {int /*<<< orphan*/  mutex; int /*<<< orphan*/  res; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  MTX_SPIN ; 
 int /*<<< orphan*/  RTC_RES_US ; 
 int bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clock_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct mv_rtc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mv_rtc_configure_bus (struct mv_rtc_softc*) ; 
 int /*<<< orphan*/  res_spec ; 

__attribute__((used)) static int
mv_rtc_attach(device_t dev)
{
	struct mv_rtc_softc *sc;
	int unit, ret;

	unit = device_get_unit(dev);

	sc = device_get_softc(dev);
	sc->dev = dev;

	clock_register(dev, RTC_RES_US);

	mtx_init(&sc->mutex, device_get_nameunit(dev), NULL, MTX_SPIN);

	ret = bus_alloc_resources(dev, res_spec, sc->res);

	if (ret != 0) {
		device_printf(dev, "could not allocate resources\n");
		mtx_destroy(&sc->mutex);
		return (ENXIO);
	}
	mv_rtc_configure_bus(sc);

	return (0);
}