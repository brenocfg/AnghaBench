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
struct wpa_eapol_ie_parse {int const* rsn_ie; int rsn_ie_len; int const* mdie; int mdie_len; int const* ftie; int ftie_len; int const* reassoc_deadline; int const* key_lifetime; int const* lnkid; int lnkid_len; int const* ext_capab; int ext_capab_len; int const* supp_rates; int supp_rates_len; int const* ext_supp_rates; int ext_supp_rates_len; int const* ht_capabilities; int aid; int const* vht_capabilities; int qosinfo; int const* supp_channels; int supp_channels_len; int const* supp_oper_classes; int supp_oper_classes_len; } ;
struct rsn_mdie {int dummy; } ;
struct rsn_ftie {int dummy; } ;
struct ieee80211_vht_capabilities {int dummy; } ;
struct ieee80211_ht_capabilities {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int const WLAN_EID_EXT_CAPAB ; 
 int const WLAN_EID_EXT_SUPP_RATES ; 
 int const WLAN_EID_FAST_BSS_TRANSITION ; 
 int const WLAN_EID_HT_CAP ; 
 int const WLAN_EID_LINK_ID ; 
 int const WLAN_EID_MOBILITY_DOMAIN ; 
 int const WLAN_EID_QOS ; 
 int const WLAN_EID_RSN ; 
 int const WLAN_EID_SUPPORTED_CHANNELS ; 
 int const WLAN_EID_SUPPORTED_OPERATING_CLASSES ; 
 int const WLAN_EID_SUPP_RATES ; 
 int const WLAN_EID_TIMEOUT_INTERVAL ; 
 int const WLAN_EID_VENDOR_SPECIFIC ; 
 int const WLAN_EID_VHT_AID ; 
 int const WLAN_EID_VHT_CAP ; 
 int const WLAN_TIMEOUT_KEY_LIFETIME ; 
 int const WLAN_TIMEOUT_REASSOC_DEADLINE ; 
 int WPA_GET_LE16 (int const*) ; 
 int /*<<< orphan*/  os_memset (struct wpa_eapol_ie_parse*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int const*,int const) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,int const*,size_t) ; 
 int wpa_parse_generic (int const*,int const*,struct wpa_eapol_ie_parse*) ; 
 int wpa_parse_vendor_specific (int const*,int const*,struct wpa_eapol_ie_parse*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int const,int const,int) ; 

int wpa_supplicant_parse_ies(const u8 *buf, size_t len,
			     struct wpa_eapol_ie_parse *ie)
{
	const u8 *pos, *end;
	int ret = 0;

	os_memset(ie, 0, sizeof(*ie));
	for (pos = buf, end = pos + len; end - pos > 1; pos += 2 + pos[1]) {
		if (pos[0] == 0xdd &&
		    ((pos == buf + len - 1) || pos[1] == 0)) {
			/* Ignore padding */
			break;
		}
		if (2 + pos[1] > end - pos) {
			wpa_printf(MSG_DEBUG, "WPA: EAPOL-Key Key Data "
				   "underflow (ie=%d len=%d pos=%d)",
				   pos[0], pos[1], (int) (pos - buf));
			wpa_hexdump_key(MSG_DEBUG, "WPA: Key Data",
					buf, len);
			ret = -1;
			break;
		}
		if (*pos == WLAN_EID_RSN) {
			ie->rsn_ie = pos;
			ie->rsn_ie_len = pos[1] + 2;
			wpa_hexdump(MSG_DEBUG, "WPA: RSN IE in EAPOL-Key",
				    ie->rsn_ie, ie->rsn_ie_len);
		} else if (*pos == WLAN_EID_MOBILITY_DOMAIN &&
			   pos[1] >= sizeof(struct rsn_mdie)) {
			ie->mdie = pos;
			ie->mdie_len = pos[1] + 2;
			wpa_hexdump(MSG_DEBUG, "WPA: MDIE in EAPOL-Key",
				    ie->mdie, ie->mdie_len);
		} else if (*pos == WLAN_EID_FAST_BSS_TRANSITION &&
			   pos[1] >= sizeof(struct rsn_ftie)) {
			ie->ftie = pos;
			ie->ftie_len = pos[1] + 2;
			wpa_hexdump(MSG_DEBUG, "WPA: FTIE in EAPOL-Key",
				    ie->ftie, ie->ftie_len);
		} else if (*pos == WLAN_EID_TIMEOUT_INTERVAL && pos[1] >= 5) {
			if (pos[2] == WLAN_TIMEOUT_REASSOC_DEADLINE) {
				ie->reassoc_deadline = pos;
				wpa_hexdump(MSG_DEBUG, "WPA: Reassoc Deadline "
					    "in EAPOL-Key",
					    ie->reassoc_deadline, pos[1] + 2);
			} else if (pos[2] == WLAN_TIMEOUT_KEY_LIFETIME) {
				ie->key_lifetime = pos;
				wpa_hexdump(MSG_DEBUG, "WPA: KeyLifetime "
					    "in EAPOL-Key",
					    ie->key_lifetime, pos[1] + 2);
			} else {
				wpa_hexdump(MSG_DEBUG, "WPA: Unrecognized "
					    "EAPOL-Key Key Data IE",
					    pos, 2 + pos[1]);
			}
		} else if (*pos == WLAN_EID_LINK_ID) {
			if (pos[1] >= 18) {
				ie->lnkid = pos;
				ie->lnkid_len = pos[1] + 2;
			}
		} else if (*pos == WLAN_EID_EXT_CAPAB) {
			ie->ext_capab = pos;
			ie->ext_capab_len = pos[1] + 2;
		} else if (*pos == WLAN_EID_SUPP_RATES) {
			ie->supp_rates = pos;
			ie->supp_rates_len = pos[1] + 2;
		} else if (*pos == WLAN_EID_EXT_SUPP_RATES) {
			ie->ext_supp_rates = pos;
			ie->ext_supp_rates_len = pos[1] + 2;
		} else if (*pos == WLAN_EID_HT_CAP &&
			   pos[1] >= sizeof(struct ieee80211_ht_capabilities)) {
			ie->ht_capabilities = pos + 2;
		} else if (*pos == WLAN_EID_VHT_AID) {
			if (pos[1] >= 2)
				ie->aid = WPA_GET_LE16(pos + 2) & 0x3fff;
		} else if (*pos == WLAN_EID_VHT_CAP &&
			   pos[1] >= sizeof(struct ieee80211_vht_capabilities))
		{
			ie->vht_capabilities = pos + 2;
		} else if (*pos == WLAN_EID_QOS && pos[1] >= 1) {
			ie->qosinfo = pos[2];
		} else if (*pos == WLAN_EID_SUPPORTED_CHANNELS) {
			ie->supp_channels = pos + 2;
			ie->supp_channels_len = pos[1];
		} else if (*pos == WLAN_EID_SUPPORTED_OPERATING_CLASSES) {
			/*
			 * The value of the Length field of the Supported
			 * Operating Classes element is between 2 and 253.
			 * Silently skip invalid elements to avoid interop
			 * issues when trying to use the value.
			 */
			if (pos[1] >= 2 && pos[1] <= 253) {
				ie->supp_oper_classes = pos + 2;
				ie->supp_oper_classes_len = pos[1];
			}
		} else if (*pos == WLAN_EID_VENDOR_SPECIFIC) {
			ret = wpa_parse_generic(pos, end, ie);
			if (ret < 0)
				break;
			if (ret > 0) {
				ret = 0;
				break;
			}

			ret = wpa_parse_vendor_specific(pos, end, ie);
			if (ret < 0)
				break;
			if (ret > 0) {
				ret = 0;
				break;
			}
		} else {
			wpa_hexdump(MSG_DEBUG, "WPA: Unrecognized EAPOL-Key "
				    "Key Data IE", pos, 2 + pos[1]);
		}
	}

	return ret;
}