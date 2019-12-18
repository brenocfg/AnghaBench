#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ ic_state; int /*<<< orphan*/  ic_if; } ;
struct otus_softc {int /*<<< orphan*/  sc_udev; TYPE_1__ sc_ic; } ;

/* Variables and functions */
 scalar_t__ IEEE80211_S_SCAN ; 
 int /*<<< orphan*/  ieee80211_next_scan (int /*<<< orphan*/ *) ; 
 scalar_t__ usbd_is_dying (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_ref_decr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_ref_incr (int /*<<< orphan*/ ) ; 

void
otus_next_scan(void *arg, int pending)
{
#if 0
	struct otus_softc *sc = arg;

	if (usbd_is_dying(sc->sc_udev))
		return;

	usbd_ref_incr(sc->sc_udev);

	if (sc->sc_ic.ic_state == IEEE80211_S_SCAN)
		ieee80211_next_scan(&sc->sc_ic.ic_if);

	usbd_ref_decr(sc->sc_udev);
#endif
}