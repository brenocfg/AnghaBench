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
struct uhid_snes_softc {scalar_t__ sc_fflags; int /*<<< orphan*/  sc_watchdog; int /*<<< orphan*/ * sc_transfer; int /*<<< orphan*/  sc_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 size_t UHID_SNES_STATUS_DT_RD ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*),struct uhid_snes_softc*) ; 
 int /*<<< orphan*/  usbd_transfer_start (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
uhid_snes_watchdog(void *arg)
{
	struct uhid_snes_softc *sc = arg;

	mtx_assert(&sc->sc_mutex, MA_OWNED);

	if (sc->sc_fflags == 0)
		usbd_transfer_start(sc->sc_transfer[UHID_SNES_STATUS_DT_RD]);

	usb_callout_reset(&sc->sc_watchdog, hz, &uhid_snes_watchdog, sc);
}