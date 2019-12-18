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
typedef  int uint16_t ;
struct ieee80211com {int ic_opmode; scalar_t__ ic_promisc; } ;
struct bwi_softc {scalar_t__ sc_bbp_id; int sc_bbp_rev; struct ieee80211com sc_ic; } ;
struct bwi_mac {int mac_rev; struct bwi_softc* mac_sc; } ;

/* Variables and functions */
 scalar_t__ BWI_BBPID_BCM4306 ; 
 int /*<<< orphan*/  BWI_COMM_MOBJ ; 
 int /*<<< orphan*/  BWI_COMM_MOBJ_PROBE_RESP_TO ; 
 int /*<<< orphan*/  BWI_MAC_PRE_TBTT ; 
 int /*<<< orphan*/  BWI_MAC_STATUS ; 
 int BWI_MAC_STATUS_INFRA ; 
 int BWI_MAC_STATUS_OPMODE_HOSTAP ; 
 int BWI_MAC_STATUS_PASS_BADFCS ; 
 int BWI_MAC_STATUS_PASS_BADPLCP ; 
 int BWI_MAC_STATUS_PASS_BCN ; 
 int BWI_MAC_STATUS_PASS_CTL ; 
 int BWI_MAC_STATUS_PROMISC ; 
 int /*<<< orphan*/  CSR_CLRBITS_4 (struct bwi_softc*,int /*<<< orphan*/ ,int) ; 
 int CSR_READ_4 (struct bwi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_SETBITS_4 (struct bwi_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CSR_WRITE_2 (struct bwi_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct bwi_softc*,int /*<<< orphan*/ ,int) ; 
#define  IEEE80211_M_HOSTAP 130 
#define  IEEE80211_M_IBSS 129 
#define  IEEE80211_M_MONITOR 128 
 int /*<<< orphan*/  MOBJ_WRITE_2 (struct bwi_mac*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bwi_mac_opmode_init(struct bwi_mac *mac)
{
	struct bwi_softc *sc = mac->mac_sc;
	struct ieee80211com *ic = &sc->sc_ic;
	uint32_t mac_status;
	uint16_t pre_tbtt;

	CSR_CLRBITS_4(sc, BWI_MAC_STATUS, BWI_MAC_STATUS_INFRA);
	CSR_SETBITS_4(sc, BWI_MAC_STATUS, BWI_MAC_STATUS_INFRA);

	/* Set probe resp timeout to infinite */
	MOBJ_WRITE_2(mac, BWI_COMM_MOBJ, BWI_COMM_MOBJ_PROBE_RESP_TO, 0);

	/*
	 * TODO: factor out following part
	 */

	mac_status = CSR_READ_4(sc, BWI_MAC_STATUS);
	mac_status &= ~(BWI_MAC_STATUS_OPMODE_HOSTAP |
			BWI_MAC_STATUS_PASS_CTL |
			BWI_MAC_STATUS_PASS_BCN |
			BWI_MAC_STATUS_PASS_BADPLCP |
			BWI_MAC_STATUS_PASS_BADFCS |
			BWI_MAC_STATUS_PROMISC);
	mac_status |= BWI_MAC_STATUS_INFRA;

	/* Always turn on PROMISC on old hardware */
	if (mac->mac_rev < 5)
		mac_status |= BWI_MAC_STATUS_PROMISC;

	switch (ic->ic_opmode) {
	case IEEE80211_M_IBSS:
		mac_status &= ~BWI_MAC_STATUS_INFRA;
		break;
	case IEEE80211_M_HOSTAP:
		mac_status |= BWI_MAC_STATUS_OPMODE_HOSTAP;
		break;
	case IEEE80211_M_MONITOR:
#if 0
		/* Do you want data from your microwave oven? */
		mac_status |= BWI_MAC_STATUS_PASS_CTL |
			      BWI_MAC_STATUS_PASS_BADPLCP |
			      BWI_MAC_STATUS_PASS_BADFCS;
#else
		mac_status |= BWI_MAC_STATUS_PASS_CTL;
#endif
		/* Promisc? */
		break;
	default:
		break;
	}

	if (ic->ic_promisc > 0)
		mac_status |= BWI_MAC_STATUS_PROMISC;

	CSR_WRITE_4(sc, BWI_MAC_STATUS, mac_status);

	if (ic->ic_opmode != IEEE80211_M_IBSS &&
	    ic->ic_opmode != IEEE80211_M_HOSTAP) {
		if (sc->sc_bbp_id == BWI_BBPID_BCM4306 && sc->sc_bbp_rev == 3)
			pre_tbtt = 100;
		else
			pre_tbtt = 50;
	} else {
		pre_tbtt = 2;
	}
	CSR_WRITE_2(sc, BWI_MAC_PRE_TBTT, pre_tbtt);
}