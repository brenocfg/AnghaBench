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
typedef  union sec_param {int dummy; } sec_param ;
typedef  int /*<<< orphan*/  uint8_t ;
struct ieee80211com {int dummy; } ;
struct rum_softc {struct ieee80211com sc_ic; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IEEE80211_GET_SLOTTIME (struct ieee80211com*) ; 
 int /*<<< orphan*/  RT2573_MAC_CSR9 ; 
 int /*<<< orphan*/  rum_modbits (struct rum_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
rum_update_slot_cb(struct rum_softc *sc, union sec_param *data, uint8_t rvp_id)
{
	struct ieee80211com *ic = &sc->sc_ic;
	uint8_t slottime;

	slottime = IEEE80211_GET_SLOTTIME(ic);

	rum_modbits(sc, RT2573_MAC_CSR9, slottime, 0xff);

	DPRINTF("setting slot time to %uus\n", slottime);
}