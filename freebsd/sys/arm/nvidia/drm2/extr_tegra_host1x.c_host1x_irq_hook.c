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
struct host1x_softc {int drm_inited; int /*<<< orphan*/  dev; TYPE_1__* tegra_drm; int /*<<< orphan*/  irq_hook; } ;
struct TYPE_2__ {int /*<<< orphan*/  drm_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  config_intrhook_disestablish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int drm_get_platform_dev (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tegra_bo_driver_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tegra_drm_driver ; 

__attribute__((used)) static void
host1x_irq_hook(void *arg)
{
	struct host1x_softc *sc;
	int rv;

	sc = arg;
	config_intrhook_disestablish(&sc->irq_hook);

	tegra_bo_driver_register(&tegra_drm_driver);
	rv = drm_get_platform_dev(sc->dev, &sc->tegra_drm->drm_dev,
	    &tegra_drm_driver);
	if (rv != 0) {
		device_printf(sc->dev, "drm_get_platform_dev(): %d\n", rv);
		return;
	}

	sc->drm_inited = 1;
}