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
struct psm_softc {int state; int /*<<< orphan*/  softcallout; int /*<<< orphan*/  callout; int /*<<< orphan*/  bdev; int /*<<< orphan*/  dev; int /*<<< orphan*/  intr; int /*<<< orphan*/  ih; int /*<<< orphan*/  evdev_a; int /*<<< orphan*/  evdev_r; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EBUSY ; 
 int KBDC_RID_AUX ; 
 int PSM_OPEN ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_dev (int /*<<< orphan*/ ) ; 
 struct psm_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evdev_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
psmdetach(device_t dev)
{
	struct psm_softc *sc;
	int rid;

	sc = device_get_softc(dev);
	if (sc->state & PSM_OPEN)
		return (EBUSY);

#ifdef EVDEV_SUPPORT
	evdev_free(sc->evdev_r);
	evdev_free(sc->evdev_a);
#endif

	rid = KBDC_RID_AUX;
	bus_teardown_intr(dev, sc->intr, sc->ih);
	bus_release_resource(dev, SYS_RES_IRQ, rid, sc->intr);

	destroy_dev(sc->dev);
	destroy_dev(sc->bdev);

	callout_drain(&sc->callout);
	callout_drain(&sc->softcallout);

	return (0);
}