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
struct bwn_softc {scalar_t__ sc_watchdog_timer; int /*<<< orphan*/  sc_watchdog_ch; int /*<<< orphan*/  sc_task_ch; int /*<<< orphan*/  sc_rfswitch_ch; } ;
struct bwn_mac {scalar_t__ mac_status; struct bwn_softc* mac_sc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BWN_ASSERT_LOCKED (struct bwn_softc*) ; 
 int /*<<< orphan*/  BWN_INTR_MASK ; 
 scalar_t__ BWN_MAC_STATUS_INITED ; 
 scalar_t__ BWN_MAC_STATUS_STARTED ; 
 int /*<<< orphan*/  BWN_READ_4 (struct bwn_mac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BWN_WRITE_4 (struct bwn_mac*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bwn_mac_suspend (struct bwn_mac*) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bwn_core_stop(struct bwn_mac *mac)
{
	struct bwn_softc *sc = mac->mac_sc;

	BWN_ASSERT_LOCKED(sc);

	if (mac->mac_status < BWN_MAC_STATUS_STARTED)
		return;

	callout_stop(&sc->sc_rfswitch_ch);
	callout_stop(&sc->sc_task_ch);
	callout_stop(&sc->sc_watchdog_ch);
	sc->sc_watchdog_timer = 0;
	BWN_WRITE_4(mac, BWN_INTR_MASK, 0);
	BWN_READ_4(mac, BWN_INTR_MASK);
	bwn_mac_suspend(mac);

	mac->mac_status = BWN_MAC_STATUS_INITED;
}