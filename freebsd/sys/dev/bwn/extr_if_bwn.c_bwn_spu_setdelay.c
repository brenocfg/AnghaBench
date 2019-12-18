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
typedef  int uint16_t ;
struct ieee80211com {scalar_t__ ic_opmode; } ;
struct bwn_softc {struct ieee80211com sc_ic; } ;
struct TYPE_2__ {scalar_t__ type; int rf_ver; int rf_rev; } ;
struct bwn_mac {TYPE_1__ mac_phy; struct bwn_softc* mac_sc; } ;

/* Variables and functions */
 scalar_t__ BWN_PHYTYPE_A ; 
 int /*<<< orphan*/  BWN_SHARED ; 
 int /*<<< orphan*/  BWN_SHARED_SPU_WAKEUP ; 
 scalar_t__ IEEE80211_M_IBSS ; 
 int /*<<< orphan*/  bwn_shm_write_2 (struct bwn_mac*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int max (int,int) ; 

__attribute__((used)) static void
bwn_spu_setdelay(struct bwn_mac *mac, int idle)
{
	struct bwn_softc *sc = mac->mac_sc;
	struct ieee80211com *ic = &sc->sc_ic;
	uint16_t delay;	/* microsec */

	delay = (mac->mac_phy.type == BWN_PHYTYPE_A) ? 3700 : 1050;
	if (ic->ic_opmode == IEEE80211_M_IBSS || idle)
		delay = 500;
	if ((mac->mac_phy.rf_ver == 0x2050) && (mac->mac_phy.rf_rev == 8))
		delay = max(delay, (uint16_t)2400);

	bwn_shm_write_2(mac, BWN_SHARED, BWN_SHARED_SPU_WAKEUP, delay);
}