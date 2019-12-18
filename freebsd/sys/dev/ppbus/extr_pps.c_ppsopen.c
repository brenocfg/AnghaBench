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
struct pps_data {int busy; int /*<<< orphan*/  lock; int /*<<< orphan*/  ppbus; int /*<<< orphan*/  lastdata; int /*<<< orphan*/  timeout; int /*<<< orphan*/  ppsdev; } ;
struct cdev {int /*<<< orphan*/  si_drv2; struct pps_data* si_drv1; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINTR ; 
 int IRQENABLE ; 
 int PCD ; 
 int PPB_INTR ; 
 int /*<<< orphan*/  PPB_IN_EPP_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PPB_PS2 ; 
 int PPB_WAIT ; 
 int /*<<< orphan*/  PRVERBOSE (char*,int,int /*<<< orphan*/ ) ; 
 int SELECTIN ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct pps_data*) ; 
 int nINIT ; 
 int /*<<< orphan*/  ppb_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_rdtr (int /*<<< orphan*/ ) ; 
 scalar_t__ ppb_request_bus (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int ppb_set_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_wctr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ppshcpoll ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static	int
ppsopen(struct cdev *dev, int flags, int fmt, struct thread *td)
{
	struct pps_data *sc = dev->si_drv1;
	device_t ppbus = sc->ppbus;
	int subdev = (intptr_t)dev->si_drv2;
	int i;

	/*
	 * The sx lock is here solely to serialize open()'s to close
	 * the race of concurrent open()'s when pps(4) doesn't own the
	 * ppbus.
	 */
	sx_xlock(&sc->lock);
	ppb_lock(ppbus);
	if (!sc->busy) {
		device_t ppsdev = sc->ppsdev;

		if (ppb_request_bus(ppbus, ppsdev, PPB_WAIT|PPB_INTR)) {
			ppb_unlock(ppbus);
			sx_xunlock(&sc->lock);
			return (EINTR);
		}

		i = ppb_set_mode(sc->ppbus, PPB_PS2);
		PRVERBOSE("EPP: %d %d\n", i, PPB_IN_EPP_MODE(sc->ppbus));

		i = IRQENABLE | PCD | nINIT | SELECTIN;
		ppb_wctr(ppbus, i);
	}
	if (subdev > 0 && !(sc->busy & ~1)) {
		/* XXX: Timeout of 1?  hz/100 instead perhaps? */
		callout_reset(&sc->timeout, 1, ppshcpoll, sc);
		sc->lastdata = ppb_rdtr(sc->ppbus);
	}
	sc->busy |= (1 << subdev);
	ppb_unlock(ppbus);
	sx_xunlock(&sc->lock);
	return(0);
}