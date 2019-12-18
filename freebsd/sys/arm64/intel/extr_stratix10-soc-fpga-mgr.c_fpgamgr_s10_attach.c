#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct fpgamgr_s10_softc {TYPE_2__* mgr_cdev_partial; TYPE_1__* mgr_cdev; int /*<<< orphan*/  sx; int /*<<< orphan*/  dev; int /*<<< orphan*/ * s10_svc_dev; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/ * devclass_t ;
struct TYPE_4__ {struct fpgamgr_s10_softc* si_drv1; } ;
struct TYPE_3__ {struct fpgamgr_s10_softc* si_drv1; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  GID_WHEEL ; 
 int /*<<< orphan*/  UID_ROOT ; 
 int /*<<< orphan*/ * devclass_find (char*) ; 
 int /*<<< orphan*/ * devclass_get_device (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct fpgamgr_s10_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fpga_cdevsw ; 
 void* make_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_init (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int
fpgamgr_s10_attach(device_t dev)
{
	struct fpgamgr_s10_softc *sc;
	devclass_t dc;

	sc = device_get_softc(dev);
	sc->dev = dev;

	dc = devclass_find("s10_svc");
	if (dc == NULL)
		return (ENXIO);

	sc->s10_svc_dev = devclass_get_device(dc, 0);
	if (sc->s10_svc_dev == NULL)
		return (ENXIO);

	sc->mgr_cdev = make_dev(&fpga_cdevsw, 0, UID_ROOT, GID_WHEEL,
	    0600, "fpga%d", device_get_unit(sc->dev));
	if (sc->mgr_cdev == NULL) {
		device_printf(dev, "Failed to create character device.\n");
		return (ENXIO);
	}

	sc->mgr_cdev_partial = make_dev(&fpga_cdevsw, 0, UID_ROOT, GID_WHEEL,
	    0600, "fpga_partial%d", device_get_unit(sc->dev));
	if (sc->mgr_cdev_partial == NULL) {
		device_printf(dev, "Failed to create character device.\n");
		return (ENXIO);
	}

	sx_init(&sc->sx, "s10 fpga");

	sc->mgr_cdev->si_drv1 = sc;
	sc->mgr_cdev_partial->si_drv1 = sc;

	return (0);
}