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
typedef  int /*<<< orphan*/  u8 ;
struct hostapd_data {TYPE_1__* conf; } ;
struct TYPE_2__ {int /*<<< orphan*/  owe_transition_ssid_len; int /*<<< orphan*/  owe_transition_ssid; int /*<<< orphan*/  owe_transition_bssid; scalar_t__* owe_transition_ifname; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  OUI_WFA ; 
 int /*<<< orphan*/  OWE_OUI_TYPE ; 
 int /*<<< orphan*/  WLAN_EID_VENDOR_SPECIFIC ; 
 int /*<<< orphan*/  WPA_PUT_BE24 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hostapd_eid_owe_trans_enabled (struct hostapd_data*) ; 
 size_t hostapd_eid_owe_trans_len (struct hostapd_data*) ; 
 int /*<<< orphan*/  hostapd_owe_trans_get_info (struct hostapd_data*) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

u8 * hostapd_eid_owe_trans(struct hostapd_data *hapd, u8 *eid,
				  size_t len)
{
#ifdef CONFIG_OWE
	u8 *pos = eid;
	size_t elen;

	if (hapd->conf->owe_transition_ifname[0] &&
	    !hostapd_eid_owe_trans_enabled(hapd))
		hostapd_owe_trans_get_info(hapd);

	if (!hostapd_eid_owe_trans_enabled(hapd))
		return pos;

	elen = hostapd_eid_owe_trans_len(hapd);
	if (len < elen) {
		wpa_printf(MSG_DEBUG,
			   "OWE: Not enough room in the buffer for OWE IE");
		return pos;
	}

	*pos++ = WLAN_EID_VENDOR_SPECIFIC;
	*pos++ = elen - 2;
	WPA_PUT_BE24(pos, OUI_WFA);
	pos += 3;
	*pos++ = OWE_OUI_TYPE;
	os_memcpy(pos, hapd->conf->owe_transition_bssid, ETH_ALEN);
	pos += ETH_ALEN;
	*pos++ = hapd->conf->owe_transition_ssid_len;
	os_memcpy(pos, hapd->conf->owe_transition_ssid,
		  hapd->conf->owe_transition_ssid_len);
	pos += hapd->conf->owe_transition_ssid_len;

	return pos;
#else /* CONFIG_OWE */
	return eid;
#endif /* CONFIG_OWE */
}