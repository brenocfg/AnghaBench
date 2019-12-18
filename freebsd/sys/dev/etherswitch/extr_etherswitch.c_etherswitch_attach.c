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
struct make_dev_args {int mda_mode; struct etherswitch_softc* mda_si_drv1; int /*<<< orphan*/  mda_gid; int /*<<< orphan*/  mda_uid; int /*<<< orphan*/ * mda_devsw; } ;
struct etherswitch_softc {int /*<<< orphan*/  sc_devnode; int /*<<< orphan*/  sc_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  GID_WHEEL ; 
 int /*<<< orphan*/  UID_ROOT ; 
 struct etherswitch_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  etherswitch_cdevsw ; 
 int /*<<< orphan*/  make_dev_args_init (struct make_dev_args*) ; 
 int make_dev_s (struct make_dev_args*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
etherswitch_attach(device_t dev)
{
	int err;
	struct etherswitch_softc *sc;
	struct make_dev_args devargs;

	sc = device_get_softc(dev);
	sc->sc_dev = dev;
	make_dev_args_init(&devargs);
	devargs.mda_devsw = &etherswitch_cdevsw;
	devargs.mda_uid = UID_ROOT;
	devargs.mda_gid = GID_WHEEL;
	devargs.mda_mode = 0600;
	devargs.mda_si_drv1 = sc;
	err = make_dev_s(&devargs, &sc->sc_devnode, "etherswitch%d",
	    device_get_unit(dev));
	if (err != 0) {
		device_printf(dev, "failed to create character device\n");
		return (ENXIO);
	}

	return (0);
}