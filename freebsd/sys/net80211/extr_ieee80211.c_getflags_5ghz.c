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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int IEEE80211_CHAN_A ; 
 int IEEE80211_CHAN_HT20 ; 
 int IEEE80211_CHAN_HT40D ; 
 int IEEE80211_CHAN_HT40U ; 
 int IEEE80211_CHAN_VHT20 ; 
 int IEEE80211_CHAN_VHT40D ; 
 int IEEE80211_CHAN_VHT40U ; 
 int IEEE80211_CHAN_VHT80 ; 
 int /*<<< orphan*/  IEEE80211_MODE_11A ; 
 int /*<<< orphan*/  IEEE80211_MODE_11NA ; 
 int /*<<< orphan*/  IEEE80211_MODE_VHT_5GHZ ; 
 scalar_t__ isset (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
getflags_5ghz(const uint8_t bands[], uint32_t flags[], int ht40, int vht80)
{
	int nmodes;

	/*
	 * the addchan_list function seems to expect the flags array to
	 * be in channel width order, so the VHT bits are interspersed
	 * as appropriate to maintain said order.
	 *
	 * It also assumes HT40U is before HT40D.
	 */
	nmodes = 0;

	/* 20MHz */
	if (isset(bands, IEEE80211_MODE_11A))
		flags[nmodes++] = IEEE80211_CHAN_A;
	if (isset(bands, IEEE80211_MODE_11NA))
		flags[nmodes++] = IEEE80211_CHAN_A | IEEE80211_CHAN_HT20;
	if (isset(bands, IEEE80211_MODE_VHT_5GHZ)) {
		flags[nmodes++] = IEEE80211_CHAN_A | IEEE80211_CHAN_HT20 |
		    IEEE80211_CHAN_VHT20;
	}

	/* 40MHz */
	if (ht40) {
		flags[nmodes++] = IEEE80211_CHAN_A | IEEE80211_CHAN_HT40U;
	}
	if (ht40 && isset(bands, IEEE80211_MODE_VHT_5GHZ)) {
		flags[nmodes++] = IEEE80211_CHAN_A | IEEE80211_CHAN_HT40U
		    | IEEE80211_CHAN_VHT40U;
	}
	if (ht40) {
		flags[nmodes++] = IEEE80211_CHAN_A | IEEE80211_CHAN_HT40D;
	}
	if (ht40 && isset(bands, IEEE80211_MODE_VHT_5GHZ)) {
		flags[nmodes++] = IEEE80211_CHAN_A | IEEE80211_CHAN_HT40D
		    | IEEE80211_CHAN_VHT40D;
	}

	/* 80MHz */
	if (vht80 && isset(bands, IEEE80211_MODE_VHT_5GHZ)) {
		flags[nmodes++] = IEEE80211_CHAN_A |
		    IEEE80211_CHAN_HT40U | IEEE80211_CHAN_VHT80;
		flags[nmodes++] = IEEE80211_CHAN_A |
		    IEEE80211_CHAN_HT40D | IEEE80211_CHAN_VHT80;
	}

	/* XXX VHT80+80 */
	/* XXX VHT160 */
	flags[nmodes] = 0;
}