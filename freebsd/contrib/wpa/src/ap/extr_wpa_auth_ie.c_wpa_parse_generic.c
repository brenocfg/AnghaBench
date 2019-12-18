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
struct wpa_eapol_ie_parse {int const* wpa_ie; int wpa_ie_len; int const* osen; int osen_len; int const* pmkid; int const* gtk; int gtk_len; int const* mac_addr; int mac_addr_len; int const* igtk; int igtk_len; int const* ip_addr_req; int const* ip_addr_alloc; int const* oci; int oci_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ OSEN_IE_VENDOR_TYPE ; 
 int PMKID_LEN ; 
 scalar_t__ RSN_KEY_DATA_GROUPKEY ; 
 scalar_t__ RSN_KEY_DATA_IGTK ; 
 scalar_t__ RSN_KEY_DATA_MAC_ADDR ; 
 scalar_t__ RSN_KEY_DATA_OCI ; 
 scalar_t__ RSN_KEY_DATA_PMKID ; 
 scalar_t__ RSN_SELECTOR_GET (int const*) ; 
 int RSN_SELECTOR_LEN ; 
 scalar_t__ WFA_KEY_DATA_IP_ADDR_ALLOC ; 
 scalar_t__ WFA_KEY_DATA_IP_ADDR_REQ ; 
 scalar_t__ WPA_GET_BE32 (int const*) ; 
 scalar_t__ WPA_OUI_TYPE ; 
 int WPA_SELECTOR_LEN ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int const*,int const) ; 

__attribute__((used)) static int wpa_parse_generic(const u8 *pos, const u8 *end,
			     struct wpa_eapol_ie_parse *ie)
{
	if (pos[1] == 0)
		return 1;

	if (pos[1] >= 6 &&
	    RSN_SELECTOR_GET(pos + 2) == WPA_OUI_TYPE &&
	    pos[2 + WPA_SELECTOR_LEN] == 1 &&
	    pos[2 + WPA_SELECTOR_LEN + 1] == 0) {
		ie->wpa_ie = pos;
		ie->wpa_ie_len = pos[1] + 2;
		return 0;
	}

	if (pos[1] >= 4 && WPA_GET_BE32(pos + 2) == OSEN_IE_VENDOR_TYPE) {
		ie->osen = pos;
		ie->osen_len = pos[1] + 2;
		return 0;
	}

	if (1 + RSN_SELECTOR_LEN < end - pos &&
	    pos[1] >= RSN_SELECTOR_LEN + PMKID_LEN &&
	    RSN_SELECTOR_GET(pos + 2) == RSN_KEY_DATA_PMKID) {
		ie->pmkid = pos + 2 + RSN_SELECTOR_LEN;
		return 0;
	}

	if (pos[1] > RSN_SELECTOR_LEN + 2 &&
	    RSN_SELECTOR_GET(pos + 2) == RSN_KEY_DATA_GROUPKEY) {
		ie->gtk = pos + 2 + RSN_SELECTOR_LEN;
		ie->gtk_len = pos[1] - RSN_SELECTOR_LEN;
		return 0;
	}

	if (pos[1] > RSN_SELECTOR_LEN + 2 &&
	    RSN_SELECTOR_GET(pos + 2) == RSN_KEY_DATA_MAC_ADDR) {
		ie->mac_addr = pos + 2 + RSN_SELECTOR_LEN;
		ie->mac_addr_len = pos[1] - RSN_SELECTOR_LEN;
		return 0;
	}

#ifdef CONFIG_IEEE80211W
	if (pos[1] > RSN_SELECTOR_LEN + 2 &&
	    RSN_SELECTOR_GET(pos + 2) == RSN_KEY_DATA_IGTK) {
		ie->igtk = pos + 2 + RSN_SELECTOR_LEN;
		ie->igtk_len = pos[1] - RSN_SELECTOR_LEN;
		return 0;
	}
#endif /* CONFIG_IEEE80211W */

#ifdef CONFIG_P2P
	if (pos[1] >= RSN_SELECTOR_LEN + 1 &&
	    RSN_SELECTOR_GET(pos + 2) == WFA_KEY_DATA_IP_ADDR_REQ) {
		ie->ip_addr_req = pos + 2 + RSN_SELECTOR_LEN;
		wpa_hexdump(MSG_DEBUG, "WPA: IP Address Request in EAPOL-Key",
			    ie->ip_addr_req, pos[1] - RSN_SELECTOR_LEN);
		return 0;
	}

	if (pos[1] >= RSN_SELECTOR_LEN + 3 * 4 &&
	    RSN_SELECTOR_GET(pos + 2) == WFA_KEY_DATA_IP_ADDR_ALLOC) {
		ie->ip_addr_alloc = pos + 2 + RSN_SELECTOR_LEN;
		wpa_hexdump(MSG_DEBUG,
			    "WPA: IP Address Allocation in EAPOL-Key",
			    ie->ip_addr_alloc, pos[1] - RSN_SELECTOR_LEN);
		return 0;
	}
#endif /* CONFIG_P2P */

#ifdef CONFIG_OCV
	if (pos[1] > RSN_SELECTOR_LEN + 2 &&
	    RSN_SELECTOR_GET(pos + 2) == RSN_KEY_DATA_OCI) {
		ie->oci = pos + 2 + RSN_SELECTOR_LEN;
		ie->oci_len = pos[1] - RSN_SELECTOR_LEN;
		return 0;
	}
#endif /* CONFIG_OCV */

	return 0;
}