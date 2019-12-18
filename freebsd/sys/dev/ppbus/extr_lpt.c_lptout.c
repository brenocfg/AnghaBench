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
struct lpt_data {int sc_state; int sc_backoff; scalar_t__ sc_xfercnt; int /*<<< orphan*/  sc_timer; int /*<<< orphan*/  sc_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EERROR ; 
 int LPTOUTMAX ; 
 int OBUSY ; 
 int OPEN ; 
 int TOUT ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,void (*) (void*),struct lpt_data*) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int hz ; 
 int /*<<< orphan*/  lprintf (char*) ; 
 int /*<<< orphan*/  lptintr (struct lpt_data*) ; 
 int /*<<< orphan*/  ppb_assert_locked (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_rstr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
lptout(void *arg)
{
	struct lpt_data *sc = arg;
	device_t dev = sc->sc_dev;
	device_t ppbus;

	ppbus = device_get_parent(dev);
	ppb_assert_locked(ppbus);
	lprintf(("T %x ", ppb_rstr(ppbus)));
	if (sc->sc_state & OPEN) {
		sc->sc_backoff++;
		if (sc->sc_backoff > hz/LPTOUTMAX)
			sc->sc_backoff = hz/LPTOUTMAX;
		callout_reset(&sc->sc_timer, sc->sc_backoff, lptout, sc);
	} else
		sc->sc_state &= ~TOUT;

	if (sc->sc_state & EERROR)
		sc->sc_state &= ~EERROR;

	/*
	 * Avoid possible hangs due to missed interrupts
	 */
	if (sc->sc_xfercnt) {
		lptintr(sc);
	} else {
		sc->sc_state &= ~OBUSY;
		wakeup(dev);
	}
}