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
struct wpa_supplicant {int enabled_4addr_mode; TYPE_1__* current_ssid; } ;
struct ieee802_11_elems {int* multi_ap; int multi_ap_len; } ;
struct TYPE_2__ {int key_mgmt; int /*<<< orphan*/  multi_ap_backhaul_sta; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int const MULTI_AP_BACKHAUL_BSS ; 
 int const MULTI_AP_FRONTHAUL_BSS ; 
 int /*<<< orphan*/  MULTI_AP_SUB_ELEM_TYPE ; 
 scalar_t__ ParseFailed ; 
 int /*<<< orphan*/  WLAN_REASON_DEAUTH_LEAVING ; 
 int WPA_KEY_MGMT_WPS ; 
 int* get_ie (int const*,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ ieee802_11_parse_elems (int const*,size_t,struct ieee802_11_elems*,int) ; 
 scalar_t__ wpa_drv_set_4addr_mode (struct wpa_supplicant*,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpa_supplicant_deauthenticate (struct wpa_supplicant*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void multi_ap_process_assoc_resp(struct wpa_supplicant *wpa_s,
					const u8 *ies, size_t ies_len)
{
	struct ieee802_11_elems elems;
	const u8 *map_sub_elem, *pos;
	size_t len;

	if (!wpa_s->current_ssid ||
	    !wpa_s->current_ssid->multi_ap_backhaul_sta ||
	    !ies ||
	    ieee802_11_parse_elems(ies, ies_len, &elems, 1) == ParseFailed)
		return;

	if (!elems.multi_ap || elems.multi_ap_len < 7) {
		wpa_printf(MSG_INFO, "AP doesn't support Multi-AP protocol");
		goto fail;
	}

	pos = elems.multi_ap + 4;
	len = elems.multi_ap_len - 4;

	map_sub_elem = get_ie(pos, len, MULTI_AP_SUB_ELEM_TYPE);
	if (!map_sub_elem || map_sub_elem[1] < 1) {
		wpa_printf(MSG_INFO, "invalid Multi-AP sub elem type");
		goto fail;
	}

	if (!(map_sub_elem[2] & MULTI_AP_BACKHAUL_BSS)) {
		if ((map_sub_elem[2] & MULTI_AP_FRONTHAUL_BSS) &&
		    wpa_s->current_ssid->key_mgmt & WPA_KEY_MGMT_WPS) {
			wpa_printf(MSG_INFO,
				   "WPS active, accepting fronthaul-only BSS");
			/* Don't set 4addr mode in this case, so just return */
			return;
		}
		wpa_printf(MSG_INFO, "AP doesn't support backhaul BSS");
		goto fail;
	}

	if (wpa_drv_set_4addr_mode(wpa_s, 1) < 0) {
		wpa_printf(MSG_ERROR, "Failed to set 4addr mode");
		goto fail;
	}
	wpa_s->enabled_4addr_mode = 1;
	return;

fail:
	wpa_supplicant_deauthenticate(wpa_s, WLAN_REASON_DEAUTH_LEAVING);
}