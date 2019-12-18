#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint16_t ;
struct TYPE_3__ {scalar_t__ htcap_ie; } ;
struct ieee80211_scan_entry {int* se_rates; int* se_xrates; TYPE_1__ se_ies; } ;
struct ieee80211_ie_htcap {int* hc_mcsset; int /*<<< orphan*/  hc_cap; } ;
struct TYPE_4__ {int ht40_rate_400ns; int ht40_rate_800ns; int ht20_rate_400ns; int ht20_rate_800ns; } ;

/* Variables and functions */
 int IEEE80211_HTCAP_CHWIDTH40 ; 
 int IEEE80211_HTCAP_SHORTGI20 ; 
 int IEEE80211_HTCAP_SHORTGI40 ; 
 int IEEE80211_RATE_VAL ; 
 TYPE_2__* ieee80211_htrates ; 
 scalar_t__ isclr (int*,int) ; 
 int le16dec (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
maxrate(const struct ieee80211_scan_entry *se)
{
	const struct ieee80211_ie_htcap *htcap =
	    (const struct ieee80211_ie_htcap *) se->se_ies.htcap_ie;
	int rmax, r, i, txstream;
	uint16_t caps;
	uint8_t txparams;

	rmax = 0;
	if (htcap != NULL) {
		/*
		 * HT station; inspect supported MCS and then adjust
		 * rate by channel width.
		 */
		txparams = htcap->hc_mcsset[12];
		if (txparams & 0x3) {
			/*
			 * TX MCS parameters defined and not equal to RX,
			 * extract the number of spartial streams and
			 * map it to the highest MCS rate.
			 */
			txstream = ((txparams & 0xc) >> 2) + 1;
			i = txstream * 8 - 1;
		} else
			for (i = 31; i >= 0 && isclr(htcap->hc_mcsset, i); i--);
		if (i >= 0) {
			caps = le16dec(&htcap->hc_cap);
			if ((caps & IEEE80211_HTCAP_CHWIDTH40) &&
			    (caps & IEEE80211_HTCAP_SHORTGI40))
				rmax = ieee80211_htrates[i].ht40_rate_400ns;
			else if (caps & IEEE80211_HTCAP_CHWIDTH40)
				rmax = ieee80211_htrates[i].ht40_rate_800ns;
			else if (caps & IEEE80211_HTCAP_SHORTGI20)
				rmax = ieee80211_htrates[i].ht20_rate_400ns;
			else
				rmax = ieee80211_htrates[i].ht20_rate_800ns;
		}
	}
	for (i = 0; i < se->se_rates[1]; i++) {
		r = se->se_rates[2+i] & IEEE80211_RATE_VAL;
		if (r > rmax)
			rmax = r;
	}
	for (i = 0; i < se->se_xrates[1]; i++) {
		r = se->se_xrates[2+i] & IEEE80211_RATE_VAL;
		if (r > rmax)
			rmax = r;
	}
	return rmax;
}