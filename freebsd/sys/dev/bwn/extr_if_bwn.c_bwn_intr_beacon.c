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
typedef  int uint32_t ;
struct ieee80211com {scalar_t__ ic_opmode; } ;
struct bwn_softc {int sc_flags; struct ieee80211com sc_ic; } ;
struct bwn_mac {int mac_intr_mask; struct bwn_softc* mac_sc; } ;

/* Variables and functions */
 int BWN_FLAG_NEED_BEACON_TP ; 
 int BWN_INTR_BEACON ; 
 int /*<<< orphan*/  BWN_INTR_REASON ; 
 int /*<<< orphan*/  BWN_MACCMD ; 
 int BWN_MACCMD_BEACON0_VALID ; 
 int BWN_MACCMD_BEACON1_VALID ; 
 int BWN_READ_4 (struct bwn_mac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BWN_WRITE_4 (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ IEEE80211_M_HOSTAP ; 
 scalar_t__ IEEE80211_M_MBSS ; 
 int /*<<< orphan*/  bwn_load_beacon0 (struct bwn_mac*) ; 
 int /*<<< orphan*/  bwn_load_beacon1 (struct bwn_mac*) ; 

__attribute__((used)) static void
bwn_intr_beacon(struct bwn_mac *mac)
{
	struct bwn_softc *sc = mac->mac_sc;
	struct ieee80211com *ic = &sc->sc_ic;
	uint32_t cmd, beacon0, beacon1;

	if (ic->ic_opmode == IEEE80211_M_HOSTAP ||
	    ic->ic_opmode == IEEE80211_M_MBSS)
		return;

	mac->mac_intr_mask &= ~BWN_INTR_BEACON;

	cmd = BWN_READ_4(mac, BWN_MACCMD);
	beacon0 = (cmd & BWN_MACCMD_BEACON0_VALID);
	beacon1 = (cmd & BWN_MACCMD_BEACON1_VALID);

	if (beacon0 && beacon1) {
		BWN_WRITE_4(mac, BWN_INTR_REASON, BWN_INTR_BEACON);
		mac->mac_intr_mask |= BWN_INTR_BEACON;
		return;
	}

	if (sc->sc_flags & BWN_FLAG_NEED_BEACON_TP) {
		sc->sc_flags &= ~BWN_FLAG_NEED_BEACON_TP;
		bwn_load_beacon0(mac);
		bwn_load_beacon1(mac);
		cmd = BWN_READ_4(mac, BWN_MACCMD);
		cmd |= BWN_MACCMD_BEACON0_VALID;
		BWN_WRITE_4(mac, BWN_MACCMD, cmd);
	} else {
		if (!beacon0) {
			bwn_load_beacon0(mac);
			cmd = BWN_READ_4(mac, BWN_MACCMD);
			cmd |= BWN_MACCMD_BEACON0_VALID;
			BWN_WRITE_4(mac, BWN_MACCMD, cmd);
		} else if (!beacon1) {
			bwn_load_beacon1(mac);
			cmd = BWN_READ_4(mac, BWN_MACCMD);
			cmd |= BWN_MACCMD_BEACON1_VALID;
			BWN_WRITE_4(mac, BWN_MACCMD, cmd);
		}
	}
}