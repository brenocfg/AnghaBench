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
struct thread {int dummy; } ;
struct psm_softc {int state; int /*<<< orphan*/  unit; int /*<<< orphan*/ * async; } ;
struct cdev {struct psm_softc* si_drv1; } ;

/* Variables and functions */
 int ENXIO ; 
 int PSM_EV_OPEN_A ; 
 int PSM_EV_OPEN_R ; 
 int PSM_OPEN ; 
 int PSM_VALID ; 
 int /*<<< orphan*/  devclass_get_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_unbusy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  funsetown (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  psm_devclass ; 
 int psmclose (struct psm_softc*) ; 

__attribute__((used)) static int
psm_cdev_close(struct cdev *dev, int flag, int fmt, struct thread *td)
{
	struct psm_softc *sc;
	int err = 0;

	/* Get device data */
	sc = dev->si_drv1;
	if ((sc == NULL) || (sc->state & PSM_VALID) == 0) {
		/* the device is no longer valid/functioning */
		return (ENXIO);
	}

#ifdef EVDEV_SUPPORT
	/* Still opened by evdev */
	if (!(sc->state & (PSM_EV_OPEN_R | PSM_EV_OPEN_A)))
#endif
		err = psmclose(sc);

	if (err == 0) {
		sc->state &= ~PSM_OPEN;
		/* clean up and sigio requests */
		if (sc->async != NULL) {
			funsetown(&sc->async);
			sc->async = NULL;
		}
		device_unbusy(devclass_get_device(psm_devclass, sc->unit));
	}

	return (err);
}