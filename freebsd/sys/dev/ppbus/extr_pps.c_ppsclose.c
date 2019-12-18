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
struct thread {int dummy; } ;
struct pps_data {int busy; int /*<<< orphan*/  lock; int /*<<< orphan*/  ppbus; int /*<<< orphan*/  ppsdev; int /*<<< orphan*/  timeout; TYPE_2__* pps; } ;
struct cdev {int /*<<< orphan*/  si_drv2; struct pps_data* si_drv1; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_3__ {scalar_t__ mode; } ;
struct TYPE_4__ {TYPE_1__ ppsparam; } ;

/* Variables and functions */
 int /*<<< orphan*/  PPB_COMPATIBLE ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ppb_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_release_bus (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_set_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_wctr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_wdtr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static	int
ppsclose(struct cdev *dev, int flags, int fmt, struct thread *td)
{
	struct pps_data *sc = dev->si_drv1;
	int subdev = (intptr_t)dev->si_drv2;

	sx_xlock(&sc->lock);
	sc->pps[subdev].ppsparam.mode = 0;	/* PHK ??? */
	ppb_lock(sc->ppbus);
	sc->busy &= ~(1 << subdev);
	if (subdev > 0 && !(sc->busy & ~1))
		callout_stop(&sc->timeout);
	if (!sc->busy) {
		device_t ppsdev = sc->ppsdev;
		device_t ppbus = sc->ppbus;

		ppb_wdtr(ppbus, 0);
		ppb_wctr(ppbus, 0);

		ppb_set_mode(ppbus, PPB_COMPATIBLE);
		ppb_release_bus(ppbus, ppsdev);
	}
	ppb_unlock(sc->ppbus);
	sx_xunlock(&sc->lock);
	return(0);
}