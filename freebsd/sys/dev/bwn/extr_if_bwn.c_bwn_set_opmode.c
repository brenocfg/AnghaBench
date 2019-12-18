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
typedef  int uint32_t ;
typedef  int uint16_t ;
struct ieee80211com {scalar_t__ ic_opmode; } ;
struct TYPE_2__ {scalar_t__ chip_id; int chip_rev; } ;
struct bwn_softc {int sc_filters; TYPE_1__ sc_cid; int /*<<< orphan*/  sc_dev; struct ieee80211com sc_ic; } ;
struct bwn_mac {struct bwn_softc* mac_sc; } ;

/* Variables and functions */
 scalar_t__ BHND_CHIPID_BCM4306 ; 
 int /*<<< orphan*/  BWN_MACCTL ; 
 int BWN_MACCTL_BEACON_PROMISC ; 
 int BWN_MACCTL_HOSTAP ; 
 int BWN_MACCTL_PASS_BADFCS ; 
 int BWN_MACCTL_PASS_BADPLCP ; 
 int BWN_MACCTL_PASS_CTL ; 
 int BWN_MACCTL_PROMISC ; 
 int BWN_MACCTL_STA ; 
 int BWN_READ_4 (struct bwn_mac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BWN_WRITE_2 (struct bwn_mac*,int,int) ; 
 int /*<<< orphan*/  BWN_WRITE_4 (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ IEEE80211_M_HOSTAP ; 
 scalar_t__ IEEE80211_M_IBSS ; 
 scalar_t__ IEEE80211_M_MBSS ; 
 int bhnd_get_hwrev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bwn_set_opmode(struct bwn_mac *mac)
{
	struct bwn_softc *sc = mac->mac_sc;
	struct ieee80211com *ic = &sc->sc_ic;
	uint32_t ctl;
	uint16_t cfp_pretbtt;

	ctl = BWN_READ_4(mac, BWN_MACCTL);
	ctl &= ~(BWN_MACCTL_HOSTAP | BWN_MACCTL_PASS_CTL |
	    BWN_MACCTL_PASS_BADPLCP | BWN_MACCTL_PASS_BADFCS |
	    BWN_MACCTL_PROMISC | BWN_MACCTL_BEACON_PROMISC);
	ctl |= BWN_MACCTL_STA;

	if (ic->ic_opmode == IEEE80211_M_HOSTAP ||
	    ic->ic_opmode == IEEE80211_M_MBSS)
		ctl |= BWN_MACCTL_HOSTAP;
	else if (ic->ic_opmode == IEEE80211_M_IBSS)
		ctl &= ~BWN_MACCTL_STA;
	ctl |= sc->sc_filters;

	if (bhnd_get_hwrev(sc->sc_dev) <= 4)
		ctl |= BWN_MACCTL_PROMISC;

	BWN_WRITE_4(mac, BWN_MACCTL, ctl);

	cfp_pretbtt = 2;
	if ((ctl & BWN_MACCTL_STA) && !(ctl & BWN_MACCTL_HOSTAP)) {
		if (sc->sc_cid.chip_id == BHND_CHIPID_BCM4306 &&
		    sc->sc_cid.chip_rev == 3)
			cfp_pretbtt = 100;
		else
			cfp_pretbtt = 50;
	}
	BWN_WRITE_2(mac, 0x612, cfp_pretbtt);
}