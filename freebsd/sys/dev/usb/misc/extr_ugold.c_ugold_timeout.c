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
struct ugold_softc {int /*<<< orphan*/  sc_callout; int /*<<< orphan*/  sc_udev; int /*<<< orphan*/ * sc_readout_msg; } ;

/* Variables and functions */
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,void (*) (void*),struct ugold_softc*) ; 
 int hz ; 
 int /*<<< orphan*/  usb_proc_explore_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_proc_explore_msignal (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_proc_explore_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ugold_timeout(void *arg)
{
	struct ugold_softc *sc = arg;

	usb_proc_explore_lock(sc->sc_udev);
	(void)usb_proc_explore_msignal(sc->sc_udev,
	    &sc->sc_readout_msg[0], &sc->sc_readout_msg[1]);
	usb_proc_explore_unlock(sc->sc_udev);

	callout_reset(&sc->sc_callout, 6 * hz, &ugold_timeout, sc);
}