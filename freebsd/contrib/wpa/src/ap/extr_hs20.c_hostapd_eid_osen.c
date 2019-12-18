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
typedef  int u8 ;
typedef  int u16 ;
struct hostapd_data {TYPE_1__* conf; } ;
struct TYPE_2__ {scalar_t__ ieee80211w; scalar_t__ ocv; scalar_t__ wmm_enabled; int /*<<< orphan*/  osen; } ;

/* Variables and functions */
 int /*<<< orphan*/  HS20_OSEN_OUI_TYPE ; 
 scalar_t__ MGMT_FRAME_PROTECTION_REQUIRED ; 
 scalar_t__ NO_MGMT_FRAME_PROTECTION ; 
 int /*<<< orphan*/  OUI_WFA ; 
 int /*<<< orphan*/  RSN_AUTH_KEY_MGMT_OSEN ; 
 int /*<<< orphan*/  RSN_CIPHER_SUITE_CCMP ; 
 int /*<<< orphan*/  RSN_CIPHER_SUITE_NO_GROUP_ADDRESSED ; 
 int RSN_NUM_REPLAY_COUNTERS_16 ; 
 int /*<<< orphan*/  RSN_SELECTOR_LEN ; 
 int /*<<< orphan*/  RSN_SELECTOR_PUT (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WLAN_EID_VENDOR_SPECIFIC ; 
 int WPA_CAPABILITY_MFPC ; 
 int WPA_CAPABILITY_MFPR ; 
 int WPA_CAPABILITY_OCVC ; 
 int /*<<< orphan*/  WPA_PUT_BE24 (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WPA_PUT_LE16 (int*,int) ; 

u8 * hostapd_eid_osen(struct hostapd_data *hapd, u8 *eid)
{
	u8 *len;
	u16 capab;

	if (!hapd->conf->osen)
		return eid;

	*eid++ = WLAN_EID_VENDOR_SPECIFIC;
	len = eid++; /* to be filled */
	WPA_PUT_BE24(eid, OUI_WFA);
	eid += 3;
	*eid++ = HS20_OSEN_OUI_TYPE;

	/* Group Data Cipher Suite */
	RSN_SELECTOR_PUT(eid, RSN_CIPHER_SUITE_NO_GROUP_ADDRESSED);
	eid += RSN_SELECTOR_LEN;

	/* Pairwise Cipher Suite Count and List */
	WPA_PUT_LE16(eid, 1);
	eid += 2;
	RSN_SELECTOR_PUT(eid, RSN_CIPHER_SUITE_CCMP);
	eid += RSN_SELECTOR_LEN;

	/* AKM Suite Count and List */
	WPA_PUT_LE16(eid, 1);
	eid += 2;
	RSN_SELECTOR_PUT(eid, RSN_AUTH_KEY_MGMT_OSEN);
	eid += RSN_SELECTOR_LEN;

	/* RSN Capabilities */
	capab = 0;
	if (hapd->conf->wmm_enabled) {
		/* 4 PTKSA replay counters when using WMM */
		capab |= (RSN_NUM_REPLAY_COUNTERS_16 << 2);
	}
#ifdef CONFIG_IEEE80211W
	if (hapd->conf->ieee80211w != NO_MGMT_FRAME_PROTECTION) {
		capab |= WPA_CAPABILITY_MFPC;
		if (hapd->conf->ieee80211w == MGMT_FRAME_PROTECTION_REQUIRED)
			capab |= WPA_CAPABILITY_MFPR;
	}
#endif /* CONFIG_IEEE80211W */
#ifdef CONFIG_OCV
	if (hapd->conf->ocv)
		capab |= WPA_CAPABILITY_OCVC;
#endif /* CONFIG_OCV */
	WPA_PUT_LE16(eid, capab);
	eid += 2;

	*len = eid - len - 1;

	return eid;
}