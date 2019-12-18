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
struct lpt_data {int sc_state; uintptr_t sc_flags; int sc_irq; scalar_t__ sc_primed; int sc_control; int sc_backoff; int /*<<< orphan*/  sc_timer; scalar_t__ sc_xfercnt; int /*<<< orphan*/  sc_dev; } ;
struct cdev {scalar_t__ si_drv2; struct lpt_data* si_drv1; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int EBUSY ; 
 int ENXIO ; 
 scalar_t__ EWOULDBLOCK ; 
 int LPC_AUTOL ; 
 int LPC_ENA ; 
 int LPC_NINIT ; 
 int LPC_SEL ; 
 int LPINITRDY ; 
 int LPPRI ; 
 int LPS_NBSY ; 
 int LPS_NERR ; 
 int LPS_OUT ; 
 int LPS_SEL ; 
 int LPTINIT ; 
 int LPTOUTINITIAL ; 
 int LP_AUTOLF ; 
 int LP_BYPASS ; 
 int LP_ENABLE_IRQ ; 
 int LP_NO_PRIME ; 
 int LP_PRIMEOPEN ; 
 int LP_USE_IRQ ; 
 int OPEN ; 
 int PCATCH ; 
 int PPB_INTR ; 
 int PPB_WAIT ; 
 int TOUT ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct lpt_data*) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int hz ; 
 int /*<<< orphan*/  lprintf (char*) ; 
 int /*<<< orphan*/  lpt_release_ppbus (int /*<<< orphan*/ ) ; 
 int lpt_request_ppbus (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lptout ; 
 int /*<<< orphan*/  ppb_lock (int /*<<< orphan*/ ) ; 
 int ppb_rstr (int /*<<< orphan*/ ) ; 
 scalar_t__ ppb_sleep (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  ppb_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_wctr (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static	int
lptopen(struct cdev *dev, int flags, int fmt, struct thread *td)
{
	int trys, err;
	struct lpt_data *sc = dev->si_drv1;
	device_t lptdev;
	device_t ppbus;

	if (!sc)
		return (ENXIO);

	lptdev = sc->sc_dev;
	ppbus = device_get_parent(lptdev);

	ppb_lock(ppbus);
	if (sc->sc_state) {
		lprintf(("%s: still open %x\n", device_get_nameunit(lptdev),
		    sc->sc_state));
		ppb_unlock(ppbus);
		return(EBUSY);
	} else
		sc->sc_state |= LPTINIT;

	sc->sc_flags = (uintptr_t)dev->si_drv2;

	/* Check for open with BYPASS flag set. */
	if (sc->sc_flags & LP_BYPASS) {
		sc->sc_state = OPEN;
		ppb_unlock(ppbus);
		return(0);
	}

	/* request the ppbus only if we don't have it already */
	if ((err = lpt_request_ppbus(lptdev, PPB_WAIT|PPB_INTR)) != 0) {
		/* give it a chance to try later */
		sc->sc_state = 0;
		ppb_unlock(ppbus);
		return (err);
	}

	lprintf(("%s flags 0x%x\n", device_get_nameunit(lptdev),
	    sc->sc_flags));

	/* set IRQ status according to ENABLE_IRQ flag
	 */
	if (sc->sc_irq & LP_ENABLE_IRQ)
		sc->sc_irq |= LP_USE_IRQ;
	else
		sc->sc_irq &= ~LP_USE_IRQ;

	/* init printer */
	if ((sc->sc_flags & LP_NO_PRIME) == 0) {
		if ((sc->sc_flags & LP_PRIMEOPEN) || sc->sc_primed == 0) {
			ppb_wctr(ppbus, 0);
			sc->sc_primed++;
			DELAY(500);
		}
	}

	ppb_wctr(ppbus, LPC_SEL|LPC_NINIT);

	/* wait till ready (printer running diagnostics) */
	trys = 0;
	do {
		/* ran out of waiting for the printer */
		if (trys++ >= LPINITRDY*4) {
			lprintf(("status %x\n", ppb_rstr(ppbus)));

			lpt_release_ppbus(lptdev);
			sc->sc_state = 0;
			ppb_unlock(ppbus);
			return (EBUSY);
		}

		/* wait 1/4 second, give up if we get a signal */
		if (ppb_sleep(ppbus, lptdev, LPPRI | PCATCH, "lptinit",
		    hz / 4) != EWOULDBLOCK) {
			lpt_release_ppbus(lptdev);
			sc->sc_state = 0;
			ppb_unlock(ppbus);
			return (EBUSY);
		}

		/* is printer online and ready for output */
	} while ((ppb_rstr(ppbus) &
			(LPS_SEL|LPS_OUT|LPS_NBSY|LPS_NERR)) !=
					(LPS_SEL|LPS_NBSY|LPS_NERR));

	sc->sc_control = LPC_SEL|LPC_NINIT;
	if (sc->sc_flags & LP_AUTOLF)
		sc->sc_control |= LPC_AUTOL;

	/* enable interrupt if interrupt-driven */
	if (sc->sc_irq & LP_USE_IRQ)
		sc->sc_control |= LPC_ENA;

	ppb_wctr(ppbus, sc->sc_control);

	sc->sc_state &= ~LPTINIT;
	sc->sc_state |= OPEN;
	sc->sc_xfercnt = 0;

	/* only use timeout if using interrupt */
	lprintf(("irq %x\n", sc->sc_irq));
	if (sc->sc_irq & LP_USE_IRQ) {
		sc->sc_state |= TOUT;
		sc->sc_backoff = hz / LPTOUTINITIAL;
		callout_reset(&sc->sc_timer, sc->sc_backoff, lptout, sc);
	}

	/* release the ppbus */
	lpt_release_ppbus(lptdev);
	ppb_unlock(ppbus);

	lprintf(("opened.\n"));
	return(0);
}