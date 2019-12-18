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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct ieee80211_mgmt {int dummy; } ;
struct hostapd_data {int /*<<< orphan*/  msg_ctx; scalar_t__ ext_mgmt_frame_handling; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_EXCESSIVE ; 
 int /*<<< orphan*/  MSG_INFO ; 
#define  WLAN_FC_STYPE_ACTION 134 
#define  WLAN_FC_STYPE_ASSOC_RESP 133 
#define  WLAN_FC_STYPE_AUTH 132 
#define  WLAN_FC_STYPE_DEAUTH 131 
#define  WLAN_FC_STYPE_DISASSOC 130 
#define  WLAN_FC_STYPE_PROBE_RESP 129 
#define  WLAN_FC_STYPE_REASSOC_RESP 128 
 int /*<<< orphan*/  handle_action_cb (struct hostapd_data*,struct ieee80211_mgmt const*,size_t,int) ; 
 int /*<<< orphan*/  handle_assoc_cb (struct hostapd_data*,struct ieee80211_mgmt const*,size_t,int,int) ; 
 int /*<<< orphan*/  handle_auth_cb (struct hostapd_data*,struct ieee80211_mgmt const*,size_t,int) ; 
 int /*<<< orphan*/  handle_deauth_cb (struct hostapd_data*,struct ieee80211_mgmt const*,size_t,int) ; 
 int /*<<< orphan*/  handle_disassoc_cb (struct hostapd_data*,struct ieee80211_mgmt const*,size_t,int) ; 
 int /*<<< orphan*/  os_free (char*) ; 
 char* os_malloc (size_t) ; 
 int /*<<< orphan*/  wpa_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int,char*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wpa_snprintf_hex (char*,size_t,int /*<<< orphan*/  const*,size_t) ; 

void ieee802_11_mgmt_cb(struct hostapd_data *hapd, const u8 *buf, size_t len,
			u16 stype, int ok)
{
	const struct ieee80211_mgmt *mgmt;
	mgmt = (const struct ieee80211_mgmt *) buf;

#ifdef CONFIG_TESTING_OPTIONS
	if (hapd->ext_mgmt_frame_handling) {
		size_t hex_len = 2 * len + 1;
		char *hex = os_malloc(hex_len);

		if (hex) {
			wpa_snprintf_hex(hex, hex_len, buf, len);
			wpa_msg(hapd->msg_ctx, MSG_INFO,
				"MGMT-TX-STATUS stype=%u ok=%d buf=%s",
				stype, ok, hex);
			os_free(hex);
		}
		return;
	}
#endif /* CONFIG_TESTING_OPTIONS */

	switch (stype) {
	case WLAN_FC_STYPE_AUTH:
		wpa_printf(MSG_DEBUG, "mgmt::auth cb");
		handle_auth_cb(hapd, mgmt, len, ok);
		break;
	case WLAN_FC_STYPE_ASSOC_RESP:
		wpa_printf(MSG_DEBUG, "mgmt::assoc_resp cb");
		handle_assoc_cb(hapd, mgmt, len, 0, ok);
		break;
	case WLAN_FC_STYPE_REASSOC_RESP:
		wpa_printf(MSG_DEBUG, "mgmt::reassoc_resp cb");
		handle_assoc_cb(hapd, mgmt, len, 1, ok);
		break;
	case WLAN_FC_STYPE_PROBE_RESP:
		wpa_printf(MSG_EXCESSIVE, "mgmt::proberesp cb ok=%d", ok);
		break;
	case WLAN_FC_STYPE_DEAUTH:
		wpa_printf(MSG_DEBUG, "mgmt::deauth cb");
		handle_deauth_cb(hapd, mgmt, len, ok);
		break;
	case WLAN_FC_STYPE_DISASSOC:
		wpa_printf(MSG_DEBUG, "mgmt::disassoc cb");
		handle_disassoc_cb(hapd, mgmt, len, ok);
		break;
	case WLAN_FC_STYPE_ACTION:
		wpa_printf(MSG_DEBUG, "mgmt::action cb ok=%d", ok);
		handle_action_cb(hapd, mgmt, len, ok);
		break;
	default:
		wpa_printf(MSG_INFO, "unknown mgmt cb frame subtype %d", stype);
		break;
	}
}