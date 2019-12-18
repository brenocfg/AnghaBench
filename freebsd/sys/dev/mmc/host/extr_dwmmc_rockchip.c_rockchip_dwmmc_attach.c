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
struct dwmmc_softc {int use_pio; int pwren_inverted; int /*<<< orphan*/ * update_ios; int /*<<< orphan*/  hwtype; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int ocd_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  HWTYPE_ROCKCHIP ; 
#define  RK2928 128 
 int /*<<< orphan*/  compat_data ; 
 struct dwmmc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int dwmmc_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwmmc_rockchip_update_ios ; 
 TYPE_1__* ofw_bus_search_compatible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
rockchip_dwmmc_attach(device_t dev)
{
	struct dwmmc_softc *sc;
	int type;

	sc = device_get_softc(dev);
	sc->hwtype = HWTYPE_ROCKCHIP;
	type = ofw_bus_search_compatible(dev, compat_data)->ocd_data;

	switch (type) {
	case RK2928:
		sc->use_pio = 1;
		break;
	}

	sc->pwren_inverted = 1;

#ifdef EXT_RESOURCES
	sc->update_ios = &dwmmc_rockchip_update_ios;
#endif

	return (dwmmc_attach(dev));
}