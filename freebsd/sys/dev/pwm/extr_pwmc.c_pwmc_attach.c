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
struct pwmc_softc {int /*<<< orphan*/  chan; int /*<<< orphan*/  cdev; int /*<<< orphan*/  dev; } ;
struct make_dev_args {int mda_flags; int mda_mode; struct pwmc_softc* mda_si_drv1; int /*<<< orphan*/  mda_gid; int /*<<< orphan*/  mda_uid; int /*<<< orphan*/ * mda_devsw; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  GID_OPERATOR ; 
 int MAKEDEV_CHECKNAME ; 
 int MAKEDEV_WAITOK ; 
 int /*<<< orphan*/  UID_ROOT ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct pwmc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  make_dev_args_init (struct make_dev_args*) ; 
 int make_dev_s (struct make_dev_args*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pwm_cdevsw ; 
 int pwmbus_get_channel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pwmc_setup_label (struct pwmc_softc*) ; 

__attribute__((used)) static int
pwmc_attach(device_t dev)
{
	struct pwmc_softc *sc;
	struct make_dev_args args;
	int error;

	sc = device_get_softc(dev);
	sc->dev = dev;

	if ((error = pwmbus_get_channel(dev, &sc->chan)) != 0)
		return (error);

	make_dev_args_init(&args);
	args.mda_flags = MAKEDEV_CHECKNAME | MAKEDEV_WAITOK;
	args.mda_devsw = &pwm_cdevsw;
	args.mda_uid = UID_ROOT;
	args.mda_gid = GID_OPERATOR;
	args.mda_mode = 0660;
	args.mda_si_drv1 = sc;
	error = make_dev_s(&args, &sc->cdev, "pwm/pwmc%d.%d",
	    device_get_unit(device_get_parent(dev)), sc->chan);
	if (error != 0) {
		device_printf(dev, "Failed to make PWM device\n");
		return (error);
	}

	pwmc_setup_label(sc);

	return (0);
}