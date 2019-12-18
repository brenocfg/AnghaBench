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
typedef  scalar_t__ u8 ;
struct wpa_supplicant {int owe_transition_search; scalar_t__ owe_transition_select; } ;
struct wpa_ssid {int key_mgmt; scalar_t__* wep_key_len; size_t wep_tx_keyidx; int proto; int pairwise_cipher; int group_cipher; int group_mgmt_cipher; scalar_t__ owe_transition_bss_select_count; scalar_t__ owe_only; } ;
struct wpa_ie_data {int pairwise_cipher; int group_cipher; int proto; int mgmt_group_cipher; int key_mgmt; int capabilities; int /*<<< orphan*/  has_group; int /*<<< orphan*/  has_pairwise; } ;
struct wpa_bss {int /*<<< orphan*/  freq; } ;

/* Variables and functions */
 scalar_t__ MAX_OWE_TRANSITION_BSS_SELECT_COUNT ; 
 int /*<<< orphan*/  MBO_ATTR_ID_AP_CAPA_IND ; 
 scalar_t__ MGMT_FRAME_PROTECTION_REQUIRED ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ NO_MGMT_FRAME_PROTECTION ; 
 int /*<<< orphan*/  OSEN_IE_VENDOR_TYPE ; 
 int /*<<< orphan*/  OWE_IE_VENDOR_TYPE ; 
 int /*<<< orphan*/  WLAN_EID_RSN ; 
 int WPA_CAPABILITY_MFPC ; 
 int WPA_CAPABILITY_MFPR ; 
 int WPA_CIPHER_WEP104 ; 
 int WPA_CIPHER_WEP40 ; 
 int /*<<< orphan*/  WPA_IE_VENDOR_TYPE ; 
 int WPA_KEY_MGMT_IEEE8021X_NO_WPA ; 
 int WPA_KEY_MGMT_NONE ; 
 int WPA_KEY_MGMT_OSEN ; 
 int WPA_KEY_MGMT_OWE ; 
 int WPA_PROTO_OSEN ; 
 int WPA_PROTO_RSN ; 
 int WPA_PROTO_WPA ; 
 scalar_t__* wpa_bss_get_ie (struct wpa_bss*,int /*<<< orphan*/ ) ; 
 scalar_t__* wpa_bss_get_vendor_ie (struct wpa_bss*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_dbg (struct wpa_supplicant*,int /*<<< orphan*/ ,char*,...) ; 
 void* wpa_default_rsn_cipher (int /*<<< orphan*/ ) ; 
 scalar_t__ wpa_key_mgmt_wpa (int) ; 
 scalar_t__ wpa_parse_wpa_ie (scalar_t__ const*,scalar_t__ const,struct wpa_ie_data*) ; 
 scalar_t__ wpas_get_ssid_pmf (struct wpa_supplicant*,struct wpa_ssid*) ; 
 scalar_t__ wpas_mbo_get_bss_attr (struct wpa_bss*,int /*<<< orphan*/ ) ; 
 int wpas_wps_ssid_bss_match (struct wpa_supplicant*,struct wpa_ssid*,struct wpa_bss*) ; 

__attribute__((used)) static int wpa_supplicant_ssid_bss_match(struct wpa_supplicant *wpa_s,
					 struct wpa_ssid *ssid,
					 struct wpa_bss *bss, int debug_print)
{
	struct wpa_ie_data ie;
	int proto_match = 0;
	const u8 *rsn_ie, *wpa_ie;
	int ret;
	int wep_ok;

	ret = wpas_wps_ssid_bss_match(wpa_s, ssid, bss);
	if (ret >= 0)
		return ret;

	/* Allow TSN if local configuration accepts WEP use without WPA/WPA2 */
	wep_ok = !wpa_key_mgmt_wpa(ssid->key_mgmt) &&
		(((ssid->key_mgmt & WPA_KEY_MGMT_NONE) &&
		  ssid->wep_key_len[ssid->wep_tx_keyidx] > 0) ||
		 (ssid->key_mgmt & WPA_KEY_MGMT_IEEE8021X_NO_WPA));

	rsn_ie = wpa_bss_get_ie(bss, WLAN_EID_RSN);
	while ((ssid->proto & (WPA_PROTO_RSN | WPA_PROTO_OSEN)) && rsn_ie) {
		proto_match++;

		if (wpa_parse_wpa_ie(rsn_ie, 2 + rsn_ie[1], &ie)) {
			if (debug_print)
				wpa_dbg(wpa_s, MSG_DEBUG,
					"   skip RSN IE - parse failed");
			break;
		}
		if (!ie.has_pairwise)
			ie.pairwise_cipher = wpa_default_rsn_cipher(bss->freq);
		if (!ie.has_group)
			ie.group_cipher = wpa_default_rsn_cipher(bss->freq);

		if (wep_ok &&
		    (ie.group_cipher & (WPA_CIPHER_WEP40 | WPA_CIPHER_WEP104)))
		{
			if (debug_print)
				wpa_dbg(wpa_s, MSG_DEBUG,
					"   selected based on TSN in RSN IE");
			return 1;
		}

		if (!(ie.proto & ssid->proto) &&
		    !(ssid->proto & WPA_PROTO_OSEN)) {
			if (debug_print)
				wpa_dbg(wpa_s, MSG_DEBUG,
					"   skip RSN IE - proto mismatch");
			break;
		}

		if (!(ie.pairwise_cipher & ssid->pairwise_cipher)) {
			if (debug_print)
				wpa_dbg(wpa_s, MSG_DEBUG,
					"   skip RSN IE - PTK cipher mismatch");
			break;
		}

		if (!(ie.group_cipher & ssid->group_cipher)) {
			if (debug_print)
				wpa_dbg(wpa_s, MSG_DEBUG,
					"   skip RSN IE - GTK cipher mismatch");
			break;
		}

		if (ssid->group_mgmt_cipher &&
		    !(ie.mgmt_group_cipher & ssid->group_mgmt_cipher)) {
			if (debug_print)
				wpa_dbg(wpa_s, MSG_DEBUG,
					"   skip RSN IE - group mgmt cipher mismatch");
			break;
		}

		if (!(ie.key_mgmt & ssid->key_mgmt)) {
			if (debug_print)
				wpa_dbg(wpa_s, MSG_DEBUG,
					"   skip RSN IE - key mgmt mismatch");
			break;
		}

#ifdef CONFIG_IEEE80211W
		if (!(ie.capabilities & WPA_CAPABILITY_MFPC) &&
		    wpas_get_ssid_pmf(wpa_s, ssid) ==
		    MGMT_FRAME_PROTECTION_REQUIRED) {
			if (debug_print)
				wpa_dbg(wpa_s, MSG_DEBUG,
					"   skip RSN IE - no mgmt frame protection");
			break;
		}
#endif /* CONFIG_IEEE80211W */
		if ((ie.capabilities & WPA_CAPABILITY_MFPR) &&
		    wpas_get_ssid_pmf(wpa_s, ssid) ==
		    NO_MGMT_FRAME_PROTECTION) {
			if (debug_print)
				wpa_dbg(wpa_s, MSG_DEBUG,
					"   skip RSN IE - no mgmt frame protection enabled but AP requires it");
			break;
		}
#ifdef CONFIG_MBO
		if (!(ie.capabilities & WPA_CAPABILITY_MFPC) &&
		    wpas_mbo_get_bss_attr(bss, MBO_ATTR_ID_AP_CAPA_IND) &&
		    wpas_get_ssid_pmf(wpa_s, ssid) !=
		    NO_MGMT_FRAME_PROTECTION) {
			if (debug_print)
				wpa_dbg(wpa_s, MSG_DEBUG,
					"   skip RSN IE - no mgmt frame protection enabled on MBO AP");
			break;
		}
#endif /* CONFIG_MBO */

		if (debug_print)
			wpa_dbg(wpa_s, MSG_DEBUG,
				"   selected based on RSN IE");
		return 1;
	}

#ifdef CONFIG_IEEE80211W
	if (wpas_get_ssid_pmf(wpa_s, ssid) == MGMT_FRAME_PROTECTION_REQUIRED &&
	    (!(ssid->key_mgmt & WPA_KEY_MGMT_OWE) || ssid->owe_only)) {
		if (debug_print)
			wpa_dbg(wpa_s, MSG_DEBUG,
				"   skip - MFP Required but network not MFP Capable");
		return 0;
	}
#endif /* CONFIG_IEEE80211W */

	wpa_ie = wpa_bss_get_vendor_ie(bss, WPA_IE_VENDOR_TYPE);
	while ((ssid->proto & WPA_PROTO_WPA) && wpa_ie) {
		proto_match++;

		if (wpa_parse_wpa_ie(wpa_ie, 2 + wpa_ie[1], &ie)) {
			if (debug_print)
				wpa_dbg(wpa_s, MSG_DEBUG,
					"   skip WPA IE - parse failed");
			break;
		}

		if (wep_ok &&
		    (ie.group_cipher & (WPA_CIPHER_WEP40 | WPA_CIPHER_WEP104)))
		{
			if (debug_print)
				wpa_dbg(wpa_s, MSG_DEBUG,
					"   selected based on TSN in WPA IE");
			return 1;
		}

		if (!(ie.proto & ssid->proto)) {
			if (debug_print)
				wpa_dbg(wpa_s, MSG_DEBUG,
					"   skip WPA IE - proto mismatch");
			break;
		}

		if (!(ie.pairwise_cipher & ssid->pairwise_cipher)) {
			if (debug_print)
				wpa_dbg(wpa_s, MSG_DEBUG,
					"   skip WPA IE - PTK cipher mismatch");
			break;
		}

		if (!(ie.group_cipher & ssid->group_cipher)) {
			if (debug_print)
				wpa_dbg(wpa_s, MSG_DEBUG,
					"   skip WPA IE - GTK cipher mismatch");
			break;
		}

		if (!(ie.key_mgmt & ssid->key_mgmt)) {
			if (debug_print)
				wpa_dbg(wpa_s, MSG_DEBUG,
					"   skip WPA IE - key mgmt mismatch");
			break;
		}

		if (debug_print)
			wpa_dbg(wpa_s, MSG_DEBUG,
				"   selected based on WPA IE");
		return 1;
	}

	if ((ssid->key_mgmt & WPA_KEY_MGMT_IEEE8021X_NO_WPA) && !wpa_ie &&
	    !rsn_ie) {
		if (debug_print)
			wpa_dbg(wpa_s, MSG_DEBUG,
				"   allow for non-WPA IEEE 802.1X");
		return 1;
	}

#ifdef CONFIG_OWE
	if ((ssid->key_mgmt & WPA_KEY_MGMT_OWE) && !ssid->owe_only &&
	    !wpa_ie && !rsn_ie) {
		if (wpa_s->owe_transition_select &&
		    wpa_bss_get_vendor_ie(bss, OWE_IE_VENDOR_TYPE) &&
		    ssid->owe_transition_bss_select_count + 1 <=
		    MAX_OWE_TRANSITION_BSS_SELECT_COUNT) {
			ssid->owe_transition_bss_select_count++;
			if (debug_print)
				wpa_dbg(wpa_s, MSG_DEBUG,
					"   skip OWE transition BSS (selection count %d does not exceed %d)",
					ssid->owe_transition_bss_select_count,
					MAX_OWE_TRANSITION_BSS_SELECT_COUNT);
			wpa_s->owe_transition_search = 1;
			return 0;
		}
		if (debug_print)
			wpa_dbg(wpa_s, MSG_DEBUG,
				"   allow in OWE transition mode");
		return 1;
	}
#endif /* CONFIG_OWE */

	if ((ssid->proto & (WPA_PROTO_WPA | WPA_PROTO_RSN)) &&
	    wpa_key_mgmt_wpa(ssid->key_mgmt) && proto_match == 0) {
		if (debug_print)
			wpa_dbg(wpa_s, MSG_DEBUG,
				"   skip - no WPA/RSN proto match");
		return 0;
	}

	if ((ssid->key_mgmt & WPA_KEY_MGMT_OSEN) &&
	    wpa_bss_get_vendor_ie(bss, OSEN_IE_VENDOR_TYPE)) {
		if (debug_print)
			wpa_dbg(wpa_s, MSG_DEBUG, "   allow in OSEN");
		return 1;
	}

	if (!wpa_key_mgmt_wpa(ssid->key_mgmt)) {
		if (debug_print)
			wpa_dbg(wpa_s, MSG_DEBUG, "   allow in non-WPA/WPA2");
		return 1;
	}

	if (debug_print)
		wpa_dbg(wpa_s, MSG_DEBUG,
			"   reject due to mismatch with WPA/WPA2");

	return 0;
}