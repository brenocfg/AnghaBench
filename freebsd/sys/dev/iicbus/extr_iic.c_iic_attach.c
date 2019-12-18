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
struct iic_softc {TYPE_1__* sc_devnode; int /*<<< orphan*/  sc_dev; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {struct iic_softc* si_drv1; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  GID_WHEEL ; 
 int /*<<< orphan*/  UID_ROOT ; 
 struct iic_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  iic_cdevsw ; 
 TYPE_1__* make_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
iic_attach(device_t dev)
{
	struct iic_softc *sc;

	sc = device_get_softc(dev);
	sc->sc_dev = dev;
	sc->sc_devnode = make_dev(&iic_cdevsw, device_get_unit(dev),
			UID_ROOT, GID_WHEEL,
			0600, "iic%d", device_get_unit(dev));
	if (sc->sc_devnode == NULL) {
		device_printf(dev, "failed to create character device\n");
		return (ENXIO);
	}
	sc->sc_devnode->si_drv1 = sc;

	return (0);
}