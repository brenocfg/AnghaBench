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
struct ieee80211com {scalar_t__ ic_opmode; } ;
struct bwi_softc {struct ieee80211com sc_ic; } ;
struct bwi_mac {int mac_flags; int mac_rev; struct bwi_softc* mac_sc; } ;

/* Variables and functions */
 int BWI_MAC_F_LOCKED ; 
 int /*<<< orphan*/  BWI_MAC_STATUS ; 
 int /*<<< orphan*/  BWI_MAC_STATUS_RFLOCK ; 
 int /*<<< orphan*/  BWI_PHYINFO ; 
 int /*<<< orphan*/  CSR_CLRBITS_4 (struct bwi_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_READ_2 (struct bwi_softc*,int /*<<< orphan*/ ) ; 
 scalar_t__ IEEE80211_M_HOSTAP ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  bwi_mac_config_ps (struct bwi_mac*) ; 
 int /*<<< orphan*/  bwi_mac_start (struct bwi_mac*) ; 

__attribute__((used)) static void
bwi_mac_unlock(struct bwi_mac *mac)
{
	struct bwi_softc *sc = mac->mac_sc;
	struct ieee80211com *ic = &sc->sc_ic;

	KASSERT(mac->mac_flags & BWI_MAC_F_LOCKED,
	    ("mac_flags 0x%x", mac->mac_flags));

	CSR_READ_2(sc, BWI_PHYINFO); /* dummy read */

	CSR_CLRBITS_4(sc, BWI_MAC_STATUS, BWI_MAC_STATUS_RFLOCK);

	if (mac->mac_rev < 3)
		bwi_mac_start(mac);
	else if (ic->ic_opmode != IEEE80211_M_HOSTAP)
		bwi_mac_config_ps(mac);

	mac->mac_flags &= ~BWI_MAC_F_LOCKED;
}