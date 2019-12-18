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
struct uslcom_softc {int /*<<< orphan*/  sc_watchdog; int /*<<< orphan*/ * sc_xfer; int /*<<< orphan*/  sc_mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 size_t USLCOM_CTRL_DT_RD ; 
 int hz ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_callout_reset (int /*<<< orphan*/ *,int,void (*) (void*),struct uslcom_softc*) ; 
 int /*<<< orphan*/  usbd_transfer_start (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
uslcom_watchdog(void *arg)
{
	struct uslcom_softc *sc = arg;

	mtx_assert(&sc->sc_mtx, MA_OWNED);

	usbd_transfer_start(sc->sc_xfer[USLCOM_CTRL_DT_RD]);

	usb_callout_reset(&sc->sc_watchdog,
	    hz / 4, &uslcom_watchdog, sc);
}