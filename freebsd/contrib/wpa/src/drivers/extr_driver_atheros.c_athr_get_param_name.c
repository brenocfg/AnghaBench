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
#define  IEEE80211_IOC_MCASTCIPHER 136 
#define  IEEE80211_PARAM_AUTHMODE 135 
#define  IEEE80211_PARAM_COUNTERMEASURES 134 
#define  IEEE80211_PARAM_KEYMGTALGS 133 
#define  IEEE80211_PARAM_MCASTKEYLEN 132 
#define  IEEE80211_PARAM_PRIVACY 131 
#define  IEEE80211_PARAM_RSNCAPS 130 
#define  IEEE80211_PARAM_UCASTCIPHERS 129 
#define  IEEE80211_PARAM_WPA 128 

__attribute__((used)) static const char * athr_get_param_name(int op)
{
	switch (op) {
	case IEEE80211_IOC_MCASTCIPHER:
		return "MCASTCIPHER";
	case IEEE80211_PARAM_MCASTKEYLEN:
		return "MCASTKEYLEN";
	case IEEE80211_PARAM_UCASTCIPHERS:
		return "UCASTCIPHERS";
	case IEEE80211_PARAM_KEYMGTALGS:
		return "KEYMGTALGS";
	case IEEE80211_PARAM_RSNCAPS:
		return "RSNCAPS";
	case IEEE80211_PARAM_WPA:
		return "WPA";
	case IEEE80211_PARAM_AUTHMODE:
		return "AUTHMODE";
	case IEEE80211_PARAM_PRIVACY:
		return "PRIVACY";
	case IEEE80211_PARAM_COUNTERMEASURES:
		return "COUNTERMEASURES";
	default:
		return "??";
	}
}