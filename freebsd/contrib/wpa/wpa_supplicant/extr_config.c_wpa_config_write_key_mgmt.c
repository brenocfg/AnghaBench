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
struct wpa_ssid {int key_mgmt; } ;
struct parse_data {int dummy; } ;

/* Variables and functions */
 int WPA_KEY_MGMT_DPP ; 
 int WPA_KEY_MGMT_FILS_SHA256 ; 
 int WPA_KEY_MGMT_FILS_SHA384 ; 
 int WPA_KEY_MGMT_FT_FILS_SHA256 ; 
 int WPA_KEY_MGMT_FT_FILS_SHA384 ; 
 int WPA_KEY_MGMT_FT_IEEE8021X ; 
 int WPA_KEY_MGMT_FT_IEEE8021X_SHA384 ; 
 int WPA_KEY_MGMT_FT_PSK ; 
 int WPA_KEY_MGMT_FT_SAE ; 
 int WPA_KEY_MGMT_IEEE8021X ; 
 int WPA_KEY_MGMT_IEEE8021X_NO_WPA ; 
 int WPA_KEY_MGMT_IEEE8021X_SHA256 ; 
 int WPA_KEY_MGMT_IEEE8021X_SUITE_B ; 
 int WPA_KEY_MGMT_IEEE8021X_SUITE_B_192 ; 
 int WPA_KEY_MGMT_NONE ; 
 int WPA_KEY_MGMT_OSEN ; 
 int WPA_KEY_MGMT_OWE ; 
 int WPA_KEY_MGMT_PSK ; 
 int WPA_KEY_MGMT_PSK_SHA256 ; 
 int WPA_KEY_MGMT_SAE ; 
 int WPA_KEY_MGMT_WPA_NONE ; 
 int WPA_KEY_MGMT_WPS ; 
 int /*<<< orphan*/  os_free (char*) ; 
 int os_snprintf (char*,int,char*,char*) ; 
 scalar_t__ os_snprintf_error (int,int) ; 
 char* os_zalloc (int) ; 

__attribute__((used)) static char * wpa_config_write_key_mgmt(const struct parse_data *data,
					struct wpa_ssid *ssid)
{
	char *buf, *pos, *end;
	int ret;

	pos = buf = os_zalloc(100);
	if (buf == NULL)
		return NULL;
	end = buf + 100;

	if (ssid->key_mgmt & WPA_KEY_MGMT_PSK) {
		ret = os_snprintf(pos, end - pos, "%sWPA-PSK",
				  pos == buf ? "" : " ");
		if (os_snprintf_error(end - pos, ret)) {
			end[-1] = '\0';
			return buf;
		}
		pos += ret;
	}

	if (ssid->key_mgmt & WPA_KEY_MGMT_IEEE8021X) {
		ret = os_snprintf(pos, end - pos, "%sWPA-EAP",
				  pos == buf ? "" : " ");
		if (os_snprintf_error(end - pos, ret)) {
			end[-1] = '\0';
			return buf;
		}
		pos += ret;
	}

	if (ssid->key_mgmt & WPA_KEY_MGMT_IEEE8021X_NO_WPA) {
		ret = os_snprintf(pos, end - pos, "%sIEEE8021X",
				  pos == buf ? "" : " ");
		if (os_snprintf_error(end - pos, ret)) {
			end[-1] = '\0';
			return buf;
		}
		pos += ret;
	}

	if (ssid->key_mgmt & WPA_KEY_MGMT_NONE) {
		ret = os_snprintf(pos, end - pos, "%sNONE",
				  pos == buf ? "" : " ");
		if (os_snprintf_error(end - pos, ret)) {
			end[-1] = '\0';
			return buf;
		}
		pos += ret;
	}

	if (ssid->key_mgmt & WPA_KEY_MGMT_WPA_NONE) {
		ret = os_snprintf(pos, end - pos, "%sWPA-NONE",
				  pos == buf ? "" : " ");
		if (os_snprintf_error(end - pos, ret)) {
			end[-1] = '\0';
			return buf;
		}
		pos += ret;
	}

#ifdef CONFIG_IEEE80211R
	if (ssid->key_mgmt & WPA_KEY_MGMT_FT_PSK) {
		ret = os_snprintf(pos, end - pos, "%sFT-PSK",
				  pos == buf ? "" : " ");
		if (os_snprintf_error(end - pos, ret)) {
			end[-1] = '\0';
			return buf;
		}
		pos += ret;
	}

	if (ssid->key_mgmt & WPA_KEY_MGMT_FT_IEEE8021X) {
		ret = os_snprintf(pos, end - pos, "%sFT-EAP",
				  pos == buf ? "" : " ");
		if (os_snprintf_error(end - pos, ret)) {
			end[-1] = '\0';
			return buf;
		}
		pos += ret;
	}

#ifdef CONFIG_SHA384
	if (ssid->key_mgmt & WPA_KEY_MGMT_FT_IEEE8021X_SHA384) {
		ret = os_snprintf(pos, end - pos, "%sFT-EAP-SHA384",
				  pos == buf ? "" : " ");
		if (os_snprintf_error(end - pos, ret)) {
			end[-1] = '\0';
			return buf;
		}
		pos += ret;
	}
#endif /* CONFIG_SHA384 */
#endif /* CONFIG_IEEE80211R */

#ifdef CONFIG_IEEE80211W
	if (ssid->key_mgmt & WPA_KEY_MGMT_PSK_SHA256) {
		ret = os_snprintf(pos, end - pos, "%sWPA-PSK-SHA256",
				  pos == buf ? "" : " ");
		if (os_snprintf_error(end - pos, ret)) {
			end[-1] = '\0';
			return buf;
		}
		pos += ret;
	}

	if (ssid->key_mgmt & WPA_KEY_MGMT_IEEE8021X_SHA256) {
		ret = os_snprintf(pos, end - pos, "%sWPA-EAP-SHA256",
				  pos == buf ? "" : " ");
		if (os_snprintf_error(end - pos, ret)) {
			end[-1] = '\0';
			return buf;
		}
		pos += ret;
	}
#endif /* CONFIG_IEEE80211W */

#ifdef CONFIG_WPS
	if (ssid->key_mgmt & WPA_KEY_MGMT_WPS) {
		ret = os_snprintf(pos, end - pos, "%sWPS",
				  pos == buf ? "" : " ");
		if (os_snprintf_error(end - pos, ret)) {
			end[-1] = '\0';
			return buf;
		}
		pos += ret;
	}
#endif /* CONFIG_WPS */

#ifdef CONFIG_SAE
	if (ssid->key_mgmt & WPA_KEY_MGMT_SAE) {
		ret = os_snprintf(pos, end - pos, "%sSAE",
				  pos == buf ? "" : " ");
		if (os_snprintf_error(end - pos, ret)) {
			end[-1] = '\0';
			return buf;
		}
		pos += ret;
	}

	if (ssid->key_mgmt & WPA_KEY_MGMT_FT_SAE) {
		ret = os_snprintf(pos, end - pos, "%sFT-SAE",
				  pos == buf ? "" : " ");
		if (os_snprintf_error(end - pos, ret)) {
			end[-1] = '\0';
			return buf;
		}
		pos += ret;
	}
#endif /* CONFIG_SAE */

#ifdef CONFIG_HS20
	if (ssid->key_mgmt & WPA_KEY_MGMT_OSEN) {
		ret = os_snprintf(pos, end - pos, "%sOSEN",
				  pos == buf ? "" : " ");
		if (os_snprintf_error(end - pos, ret)) {
			end[-1] = '\0';
			return buf;
		}
		pos += ret;
	}
#endif /* CONFIG_HS20 */

#ifdef CONFIG_SUITEB
	if (ssid->key_mgmt & WPA_KEY_MGMT_IEEE8021X_SUITE_B) {
		ret = os_snprintf(pos, end - pos, "%sWPA-EAP-SUITE-B",
				  pos == buf ? "" : " ");
		if (os_snprintf_error(end - pos, ret)) {
			end[-1] = '\0';
			return buf;
		}
		pos += ret;
	}
#endif /* CONFIG_SUITEB */

#ifdef CONFIG_SUITEB192
	if (ssid->key_mgmt & WPA_KEY_MGMT_IEEE8021X_SUITE_B_192) {
		ret = os_snprintf(pos, end - pos, "%sWPA-EAP-SUITE-B-192",
				  pos == buf ? "" : " ");
		if (os_snprintf_error(end - pos, ret)) {
			end[-1] = '\0';
			return buf;
		}
		pos += ret;
	}
#endif /* CONFIG_SUITEB192 */

#ifdef CONFIG_FILS
	if (ssid->key_mgmt & WPA_KEY_MGMT_FILS_SHA256) {
		ret = os_snprintf(pos, end - pos, "%sFILS-SHA256",
				  pos == buf ? "" : " ");
		if (os_snprintf_error(end - pos, ret)) {
			end[-1] = '\0';
			return buf;
		}
		pos += ret;
	}
	if (ssid->key_mgmt & WPA_KEY_MGMT_FILS_SHA384) {
		ret = os_snprintf(pos, end - pos, "%sFILS-SHA384",
				  pos == buf ? "" : " ");
		if (os_snprintf_error(end - pos, ret)) {
			end[-1] = '\0';
			return buf;
		}
		pos += ret;
	}
#ifdef CONFIG_IEEE80211R
	if (ssid->key_mgmt & WPA_KEY_MGMT_FT_FILS_SHA256) {
		ret = os_snprintf(pos, end - pos, "%sFT-FILS-SHA256",
				  pos == buf ? "" : " ");
		if (os_snprintf_error(end - pos, ret)) {
			end[-1] = '\0';
			return buf;
		}
		pos += ret;
	}
	if (ssid->key_mgmt & WPA_KEY_MGMT_FT_FILS_SHA384) {
		ret = os_snprintf(pos, end - pos, "%sFT-FILS-SHA384",
				  pos == buf ? "" : " ");
		if (os_snprintf_error(end - pos, ret)) {
			end[-1] = '\0';
			return buf;
		}
		pos += ret;
	}
#endif /* CONFIG_IEEE80211R */
#endif /* CONFIG_FILS */

#ifdef CONFIG_DPP
	if (ssid->key_mgmt & WPA_KEY_MGMT_DPP) {
		ret = os_snprintf(pos, end - pos, "%sDPP",
				  pos == buf ? "" : " ");
		if (os_snprintf_error(end - pos, ret)) {
			end[-1] = '\0';
			return buf;
		}
		pos += ret;
	}
#endif /* CONFIG_DPP */

#ifdef CONFIG_OWE
	if (ssid->key_mgmt & WPA_KEY_MGMT_OWE) {
		ret = os_snprintf(pos, end - pos, "%sOWE",
				  pos == buf ? "" : " ");
		if (os_snprintf_error(end - pos, ret)) {
			end[-1] = '\0';
			return buf;
		}
		pos += ret;
	}
#endif /* CONFIG_OWE */

	if (pos == buf) {
		os_free(buf);
		buf = NULL;
	}

	return buf;
}