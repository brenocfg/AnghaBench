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

/* Variables and functions */
#define  IEEE80211_HTCAP_MAXRXAMPDU_16K 131 
#define  IEEE80211_HTCAP_MAXRXAMPDU_32K 130 
#define  IEEE80211_HTCAP_MAXRXAMPDU_64K 129 
#define  IEEE80211_HTCAP_MAXRXAMPDU_8K 128 

__attribute__((used)) static int
ath_rx_ampdu_to_byte(char a)
{
	switch (a) {
	case IEEE80211_HTCAP_MAXRXAMPDU_16K:
		return 16384;
		break;
	case IEEE80211_HTCAP_MAXRXAMPDU_32K:
		return 32768;
		break;
	case IEEE80211_HTCAP_MAXRXAMPDU_64K:
		return 65536;
		break;
	case IEEE80211_HTCAP_MAXRXAMPDU_8K:
	default:
		return 8192;
		break;
	}
}