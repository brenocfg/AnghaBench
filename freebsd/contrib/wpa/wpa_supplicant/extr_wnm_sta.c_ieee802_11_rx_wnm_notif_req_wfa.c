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
typedef  int /*<<< orphan*/  u16 ;
struct wpa_supplicant {int dummy; } ;

/* Variables and functions */
 int const HS20_WNM_DEAUTH_IMMINENT_NOTICE ; 
 int const HS20_WNM_SUB_REM_NEEDED ; 
 int const HS20_WNM_T_C_ACCEPTANCE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ OUI_WFA ; 
 int WLAN_EID_VENDOR_SPECIFIC ; 
 scalar_t__ WPA_GET_BE24 (int const*) ; 
 int /*<<< orphan*/  WPA_GET_LE16 (int const*) ; 
 int /*<<< orphan*/  hs20_rx_deauth_imminent_notice (struct wpa_supplicant*,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hs20_rx_subscription_remediation (struct wpa_supplicant*,char*,int) ; 
 int /*<<< orphan*/  hs20_rx_t_c_acceptance (struct wpa_supplicant*,char*) ; 
 int /*<<< orphan*/  os_free (char*) ; 
 char* os_malloc (int) ; 
 int /*<<< orphan*/  os_memcpy (char*,int const*,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void ieee802_11_rx_wnm_notif_req_wfa(struct wpa_supplicant *wpa_s,
					    const u8 *sa, const u8 *data,
					    int len)
{
	const u8 *pos, *end, *next;
	u8 ie, ie_len;

	pos = data;
	end = data + len;

	while (end - pos > 1) {
		ie = *pos++;
		ie_len = *pos++;
		wpa_printf(MSG_DEBUG, "WNM: WFA subelement %u len %u",
			   ie, ie_len);
		if (ie_len > end - pos) {
			wpa_printf(MSG_DEBUG, "WNM: Not enough room for "
				   "subelement");
			break;
		}
		next = pos + ie_len;
		if (ie_len < 4) {
			pos = next;
			continue;
		}
		wpa_printf(MSG_DEBUG, "WNM: Subelement OUI %06x type %u",
			   WPA_GET_BE24(pos), pos[3]);

#ifdef CONFIG_HS20
		if (ie == WLAN_EID_VENDOR_SPECIFIC && ie_len >= 5 &&
		    WPA_GET_BE24(pos) == OUI_WFA &&
		    pos[3] == HS20_WNM_SUB_REM_NEEDED) {
			/* Subscription Remediation subelement */
			const u8 *ie_end;
			u8 url_len;
			char *url;
			u8 osu_method;

			wpa_printf(MSG_DEBUG, "WNM: Subscription Remediation "
				   "subelement");
			ie_end = pos + ie_len;
			pos += 4;
			url_len = *pos++;
			if (url_len == 0) {
				wpa_printf(MSG_DEBUG, "WNM: No Server URL included");
				url = NULL;
				osu_method = 1;
			} else {
				if (url_len + 1 > ie_end - pos) {
					wpa_printf(MSG_DEBUG, "WNM: Not enough room for Server URL (len=%u) and Server Method (left %d)",
						   url_len,
						   (int) (ie_end - pos));
					break;
				}
				url = os_malloc(url_len + 1);
				if (url == NULL)
					break;
				os_memcpy(url, pos, url_len);
				url[url_len] = '\0';
				osu_method = pos[url_len];
			}
			hs20_rx_subscription_remediation(wpa_s, url,
							 osu_method);
			os_free(url);
			pos = next;
			continue;
		}

		if (ie == WLAN_EID_VENDOR_SPECIFIC && ie_len >= 8 &&
		    WPA_GET_BE24(pos) == OUI_WFA &&
		    pos[3] == HS20_WNM_DEAUTH_IMMINENT_NOTICE) {
			const u8 *ie_end;
			u8 url_len;
			char *url;
			u8 code;
			u16 reauth_delay;

			ie_end = pos + ie_len;
			pos += 4;
			code = *pos++;
			reauth_delay = WPA_GET_LE16(pos);
			pos += 2;
			url_len = *pos++;
			wpa_printf(MSG_DEBUG, "WNM: HS 2.0 Deauthentication "
				   "Imminent - Reason Code %u   "
				   "Re-Auth Delay %u  URL Length %u",
				   code, reauth_delay, url_len);
			if (url_len > ie_end - pos)
				break;
			url = os_malloc(url_len + 1);
			if (url == NULL)
				break;
			os_memcpy(url, pos, url_len);
			url[url_len] = '\0';
			hs20_rx_deauth_imminent_notice(wpa_s, code,
						       reauth_delay, url);
			os_free(url);
			pos = next;
			continue;
		}

		if (ie == WLAN_EID_VENDOR_SPECIFIC && ie_len >= 5 &&
		    WPA_GET_BE24(pos) == OUI_WFA &&
		    pos[3] == HS20_WNM_T_C_ACCEPTANCE) {
			const u8 *ie_end;
			u8 url_len;
			char *url;

			ie_end = pos + ie_len;
			pos += 4;
			url_len = *pos++;
			wpa_printf(MSG_DEBUG,
				   "WNM: HS 2.0 Terms and Conditions Acceptance (URL Length %u)",
				   url_len);
			if (url_len > ie_end - pos)
				break;
			url = os_malloc(url_len + 1);
			if (!url)
				break;
			os_memcpy(url, pos, url_len);
			url[url_len] = '\0';
			hs20_rx_t_c_acceptance(wpa_s, url);
			os_free(url);
			pos = next;
			continue;
		}
#endif /* CONFIG_HS20 */

		pos = next;
	}
}