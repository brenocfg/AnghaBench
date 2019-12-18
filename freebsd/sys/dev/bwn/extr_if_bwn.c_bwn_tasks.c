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
struct bwn_softc {int /*<<< orphan*/  sc_task_ch; } ;
struct bwn_mac {scalar_t__ mac_status; int mac_task_state; struct bwn_softc* mac_sc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BWN_ASSERT_LOCKED (struct bwn_softc*) ; 
 scalar_t__ BWN_MAC_STATUS_STARTED ; 
 int /*<<< orphan*/  bwn_task_15s (struct bwn_mac*) ; 
 int /*<<< orphan*/  bwn_task_30s (struct bwn_mac*) ; 
 int /*<<< orphan*/  bwn_task_60s (struct bwn_mac*) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,void (*) (void*),struct bwn_mac*) ; 
 int hz ; 

__attribute__((used)) static void
bwn_tasks(void *arg)
{
	struct bwn_mac *mac = arg;
	struct bwn_softc *sc = mac->mac_sc;

	BWN_ASSERT_LOCKED(sc);
	if (mac->mac_status != BWN_MAC_STATUS_STARTED)
		return;

	if (mac->mac_task_state % 4 == 0)
		bwn_task_60s(mac);
	if (mac->mac_task_state % 2 == 0)
		bwn_task_30s(mac);
	bwn_task_15s(mac);

	mac->mac_task_state++;
	callout_reset(&sc->sc_task_ch, hz * 15, bwn_tasks, mac);
}