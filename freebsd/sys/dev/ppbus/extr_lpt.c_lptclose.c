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
struct lpt_data {int sc_flags; int sc_state; int sc_irq; scalar_t__ sc_xfercnt; int /*<<< orphan*/  sc_timer; int /*<<< orphan*/  sc_dev; } ;
struct cdev {struct lpt_data* si_drv1; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ EWOULDBLOCK ; 
 int INTERRUPTED ; 
 int /*<<< orphan*/  LPC_NINIT ; 
 int LPPRI ; 
 int LPS_NBSY ; 
 int LPS_NERR ; 
 int LPS_OUT ; 
 int LPS_SEL ; 
 int LP_BYPASS ; 
 int LP_USE_IRQ ; 
 int OPEN ; 
 int PCATCH ; 
 int PPB_INTR ; 
 int PPB_WAIT ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  lprintf (char*) ; 
 int /*<<< orphan*/  lpt_release_ppbus (int /*<<< orphan*/ ) ; 
 int lpt_request_ppbus (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ppb_lock (int /*<<< orphan*/ ) ; 
 int ppb_rstr (int /*<<< orphan*/ ) ; 
 scalar_t__ ppb_sleep (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_wctr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static	int
lptclose(struct cdev *dev, int flags, int fmt, struct thread *td)
{
	struct lpt_data *sc = dev->si_drv1;
	device_t lptdev = sc->sc_dev;
	device_t ppbus = device_get_parent(lptdev);
	int err;

	ppb_lock(ppbus);
	if (sc->sc_flags & LP_BYPASS)
		goto end_close;

	if ((err = lpt_request_ppbus(lptdev, PPB_WAIT|PPB_INTR)) != 0) {
		ppb_unlock(ppbus);
		return (err);
	}

	/* if the last write was interrupted, don't complete it */
	if ((!(sc->sc_state  & INTERRUPTED)) && (sc->sc_irq & LP_USE_IRQ))
		while ((ppb_rstr(ppbus) &
			(LPS_SEL|LPS_OUT|LPS_NBSY|LPS_NERR)) !=
			(LPS_SEL|LPS_NBSY|LPS_NERR) || sc->sc_xfercnt)
			/* wait 1 second, give up if we get a signal */
			if (ppb_sleep(ppbus, lptdev, LPPRI | PCATCH, "lpclose",
			    hz) != EWOULDBLOCK)
				break;

	sc->sc_state &= ~OPEN;
	callout_stop(&sc->sc_timer);
	ppb_wctr(ppbus, LPC_NINIT);

	/*
	 * unregistration of interrupt forced by release
	 */
	lpt_release_ppbus(lptdev);

end_close:
	sc->sc_state = 0;
	sc->sc_xfercnt = 0;
	ppb_unlock(ppbus);
	lprintf(("closed.\n"));
	return(0);
}