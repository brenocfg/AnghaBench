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
struct siosc {TYPE_2__* chardev; TYPE_1__* known_devices; int /*<<< orphan*/  devlist; int /*<<< orphan*/  conf_lock; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_4__ {struct siosc* si_drv1; } ;
struct TYPE_3__ {scalar_t__ type; int /*<<< orphan*/  ldn; } ;

/* Variables and functions */
 int /*<<< orphan*/  GID_WHEEL ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 scalar_t__ SUPERIO_DEV_NONE ; 
 int /*<<< orphan*/  UID_ROOT ; 
 int /*<<< orphan*/  bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_generic_probe (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct siosc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 TYPE_2__* make_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  superio_add_known_child (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  superio_cdevsw ; 

__attribute__((used)) static int
superio_attach(device_t dev)
{
	struct siosc *sc = device_get_softc(dev);
	int i;

	mtx_init(&sc->conf_lock, device_get_nameunit(dev), "superio", MTX_DEF);
	STAILQ_INIT(&sc->devlist);

	for (i = 0; sc->known_devices[i].type != SUPERIO_DEV_NONE; i++) {
		superio_add_known_child(dev, sc->known_devices[i].type,
		    sc->known_devices[i].ldn);
	}

	bus_generic_probe(dev);
	bus_generic_attach(dev);

	sc->chardev = make_dev(&superio_cdevsw, device_get_unit(dev),
	    UID_ROOT, GID_WHEEL, 0600, "superio%d", device_get_unit(dev));
	if (sc->chardev == NULL)
		device_printf(dev, "failed to create character device\n");
	else
		sc->chardev->si_drv1 = sc;
	return (0);
}