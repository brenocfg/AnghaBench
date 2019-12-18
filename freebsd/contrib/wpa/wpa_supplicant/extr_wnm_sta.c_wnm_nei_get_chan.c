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
typedef  int u8 ;
struct wpa_supplicant {struct wpa_bss* current_bss; } ;
struct wpa_bss {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WLAN_EID_COUNTRY ; 
 int ieee80211_chan_to_freq (char const*,int,int) ; 
 int* wpa_bss_get_ie (struct wpa_bss*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wnm_nei_get_chan(struct wpa_supplicant *wpa_s, u8 op_class, u8 chan)
{
	struct wpa_bss *bss = wpa_s->current_bss;
	const char *country = NULL;
	int freq;

	if (bss) {
		const u8 *elem = wpa_bss_get_ie(bss, WLAN_EID_COUNTRY);

		if (elem && elem[1] >= 2)
			country = (const char *) (elem + 2);
	}

	freq = ieee80211_chan_to_freq(country, op_class, chan);
	if (freq <= 0 && op_class == 0) {
		/*
		 * Some APs do not advertise correct operating class
		 * information. Try to determine the most likely operating
		 * frequency based on the channel number.
		 */
		if (chan >= 1 && chan <= 13)
			freq = 2407 + chan * 5;
		else if (chan == 14)
			freq = 2484;
		else if (chan >= 36 && chan <= 169)
			freq = 5000 + chan * 5;
	}
	return freq;
}