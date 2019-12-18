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
struct upgt_softc {int sc_flags; int /*<<< orphan*/  sc_watchdog_ch; int /*<<< orphan*/ * sc_xfer; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_S_SCAN ; 
 int /*<<< orphan*/  UPGT_ASSERT_LOCKED (struct upgt_softc*) ; 
 size_t UPGT_BULK_RX ; 
 int UPGT_FLAG_INITDONE ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct upgt_softc*) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  upgt_set_macfilter (struct upgt_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  upgt_stop (struct upgt_softc*) ; 
 int /*<<< orphan*/  upgt_watchdog ; 
 int /*<<< orphan*/  usbd_transfer_start (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
upgt_init(struct upgt_softc *sc)
{

	UPGT_ASSERT_LOCKED(sc);

	if (sc->sc_flags & UPGT_FLAG_INITDONE)
		upgt_stop(sc);

	usbd_transfer_start(sc->sc_xfer[UPGT_BULK_RX]);

	(void)upgt_set_macfilter(sc, IEEE80211_S_SCAN);

	sc->sc_flags |= UPGT_FLAG_INITDONE;

	callout_reset(&sc->sc_watchdog_ch, hz, upgt_watchdog, sc);
}