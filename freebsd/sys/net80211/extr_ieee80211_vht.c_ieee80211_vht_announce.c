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
struct TYPE_2__ {int tx_mcs_map; int rx_mcs_map; } ;
struct ieee80211com {TYPE_1__ ic_vht_mcsinfo; int /*<<< orphan*/  ic_vhtcaps; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_CONF_VHT (struct ieee80211com*) ; 
 int /*<<< orphan*/  IEEE80211_VHTCAP_BITS ; 
 int /*<<< orphan*/  IEEE80211_VHTCAP_SUPP_CHAN_WIDTH_MASK ; 
 int MS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ic_printf (struct ieee80211com*,char*,...) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  vht_mcs_to_num (int) ; 

void
ieee80211_vht_announce(struct ieee80211com *ic)
{
	int i, tx, rx;

	if (! IEEE80211_CONF_VHT(ic))
		return;

	/* Channel width */
	ic_printf(ic, "[VHT] Channel Widths: 20MHz, 40MHz, 80MHz");
	if (MS(ic->ic_vhtcaps, IEEE80211_VHTCAP_SUPP_CHAN_WIDTH_MASK) == 2)
		printf(" 80+80MHz");
	if (MS(ic->ic_vhtcaps, IEEE80211_VHTCAP_SUPP_CHAN_WIDTH_MASK) >= 1)
		printf(" 160MHz");
	printf("\n");

	/* Features */
	ic_printf(ic, "[VHT] Features: %b\n", ic->ic_vhtcaps,
	    IEEE80211_VHTCAP_BITS);

	/* For now, just 5GHz VHT.  Worry about 2GHz VHT later */
	for (i = 0; i < 7; i++) {
		/* Each stream is 2 bits */
		tx = (ic->ic_vht_mcsinfo.tx_mcs_map >> (2*i)) & 0x3;
		rx = (ic->ic_vht_mcsinfo.rx_mcs_map >> (2*i)) & 0x3;
		if (tx == 3 && rx == 3)
			continue;
		ic_printf(ic, "[VHT] NSS %d: TX MCS 0..%d, RX MCS 0..%d\n",
		    i + 1,
		    vht_mcs_to_num(tx),
		    vht_mcs_to_num(rx));
	}
}