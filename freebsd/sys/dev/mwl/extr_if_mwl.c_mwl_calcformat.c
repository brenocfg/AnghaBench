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
typedef  int uint8_t ;
typedef  int uint16_t ;
struct ieee80211_node {int ni_htcap; int ni_capinfo; int /*<<< orphan*/  ni_chan; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAGLE_TXD_ANTENNA ; 
 int EAGLE_TXD_CHW_20 ; 
 int EAGLE_TXD_CHW_40 ; 
 int EAGLE_TXD_EXTCHAN_HI ; 
 int EAGLE_TXD_EXTCHAN_LO ; 
 int EAGLE_TXD_FORMAT_HT ; 
 int EAGLE_TXD_FORMAT_LEGACY ; 
 int EAGLE_TXD_GI_LONG ; 
 int EAGLE_TXD_GI_SHORT ; 
 int EAGLE_TXD_PREAMBLE_LONG ; 
 int EAGLE_TXD_PREAMBLE_SHORT ; 
 int /*<<< orphan*/  EAGLE_TXD_RATE ; 
 int IEEE80211_CAPINFO_SHORT_PREAMBLE ; 
 int IEEE80211_HTCAP_SHORTGI20 ; 
 int IEEE80211_HTCAP_SHORTGI40 ; 
 scalar_t__ IEEE80211_IS_CHAN_HT40 (int /*<<< orphan*/ ) ; 
 scalar_t__ IEEE80211_IS_CHAN_HT40D (int /*<<< orphan*/ ) ; 
 int IEEE80211_RATE_MCS ; 
 int SM (int,int /*<<< orphan*/ ) ; 
 int mwl_cvtlegacyrate (int) ; 

__attribute__((used)) static uint16_t
mwl_calcformat(uint8_t rate, const struct ieee80211_node *ni)
{
	uint16_t fmt;

	fmt = SM(3, EAGLE_TXD_ANTENNA)
	    | (IEEE80211_IS_CHAN_HT40D(ni->ni_chan) ?
		EAGLE_TXD_EXTCHAN_LO : EAGLE_TXD_EXTCHAN_HI);
	if (rate & IEEE80211_RATE_MCS) {	/* HT MCS */
		fmt |= EAGLE_TXD_FORMAT_HT
		    /* NB: 0x80 implicitly stripped from ucastrate */
		    | SM(rate, EAGLE_TXD_RATE);
		/* XXX short/long GI may be wrong; re-check */
		if (IEEE80211_IS_CHAN_HT40(ni->ni_chan)) {
			fmt |= EAGLE_TXD_CHW_40
			    | (ni->ni_htcap & IEEE80211_HTCAP_SHORTGI40 ?
			        EAGLE_TXD_GI_SHORT : EAGLE_TXD_GI_LONG);
		} else {
			fmt |= EAGLE_TXD_CHW_20
			    | (ni->ni_htcap & IEEE80211_HTCAP_SHORTGI20 ?
			        EAGLE_TXD_GI_SHORT : EAGLE_TXD_GI_LONG);
		}
	} else {			/* legacy rate */
		fmt |= EAGLE_TXD_FORMAT_LEGACY
		    | SM(mwl_cvtlegacyrate(rate), EAGLE_TXD_RATE)
		    | EAGLE_TXD_CHW_20
		    /* XXX iv_flags & IEEE80211_F_SHPREAMBLE? */
		    | (ni->ni_capinfo & IEEE80211_CAPINFO_SHORT_PREAMBLE ?
			EAGLE_TXD_PREAMBLE_SHORT : EAGLE_TXD_PREAMBLE_LONG);
	}
	return fmt;
}