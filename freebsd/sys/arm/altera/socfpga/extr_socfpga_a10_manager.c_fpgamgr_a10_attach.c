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
struct fpgamgr_a10_softc {TYPE_1__* mgr_cdev; int /*<<< orphan*/  dev; int /*<<< orphan*/ * res; int /*<<< orphan*/  bsh_data; int /*<<< orphan*/  bst_data; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {struct fpgamgr_a10_softc* si_drv1; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  GID_WHEEL ; 
 int /*<<< orphan*/  UID_ROOT ; 
 scalar_t__ bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct fpgamgr_a10_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fpga_cdevsw ; 
 int /*<<< orphan*/  fpgamgr_a10_spec ; 
 TYPE_1__* make_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
fpgamgr_a10_attach(device_t dev)
{
	struct fpgamgr_a10_softc *sc;

	sc = device_get_softc(dev);
	sc->dev = dev;

	if (bus_alloc_resources(dev, fpgamgr_a10_spec, sc->res)) {
		device_printf(dev, "Could not allocate resources.\n");
		return (ENXIO);
	}

	/* Memory interface */
	sc->bst_data = rman_get_bustag(sc->res[1]);
	sc->bsh_data = rman_get_bushandle(sc->res[1]);

	sc->mgr_cdev = make_dev(&fpga_cdevsw, 0, UID_ROOT, GID_WHEEL,
	    0600, "fpga%d", device_get_unit(sc->dev));

	if (sc->mgr_cdev == NULL) {
		device_printf(dev, "Failed to create character device.\n");
		return (ENXIO);
	}

	sc->mgr_cdev->si_drv1 = sc;

	return (0);
}