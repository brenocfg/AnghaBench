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
struct wpa_driver_capa {int key_mgmt; } ;

/* Variables and functions */
 int WPA_DRIVER_CAPA_KEY_MGMT_DPP ; 
 int WPA_DRIVER_CAPA_KEY_MGMT_FILS_SHA256 ; 
 int WPA_DRIVER_CAPA_KEY_MGMT_FILS_SHA384 ; 
 int WPA_DRIVER_CAPA_KEY_MGMT_FT_FILS_SHA256 ; 
 int WPA_DRIVER_CAPA_KEY_MGMT_FT_FILS_SHA384 ; 
 int WPA_DRIVER_CAPA_KEY_MGMT_FT_PSK ; 
 int WPA_DRIVER_CAPA_KEY_MGMT_OWE ; 
 int WPA_DRIVER_CAPA_KEY_MGMT_SAE ; 
 int WPA_DRIVER_CAPA_KEY_MGMT_SUITE_B ; 
 int WPA_DRIVER_CAPA_KEY_MGMT_SUITE_B_192 ; 
 int WPA_DRIVER_CAPA_KEY_MGMT_WPA ; 
 int WPA_DRIVER_CAPA_KEY_MGMT_WPA2 ; 
 int WPA_DRIVER_CAPA_KEY_MGMT_WPA2_PSK ; 
 int WPA_DRIVER_CAPA_KEY_MGMT_WPA_NONE ; 
 int WPA_DRIVER_CAPA_KEY_MGMT_WPA_PSK ; 
 int os_snprintf (char*,int,char*) ; 
 scalar_t__ os_snprintf_error (int,int) ; 
 size_t os_strlcpy (char*,char*,size_t) ; 

__attribute__((used)) static int ctrl_iface_get_capability_key_mgmt(int res, char *strict,
					      struct wpa_driver_capa *capa,
					      char *buf, size_t buflen)
{
	int ret;
	char *pos, *end;
	size_t len;

	pos = buf;
	end = pos + buflen;

	if (res < 0) {
		if (strict)
			return 0;
		len = os_strlcpy(buf, "WPA-PSK WPA-EAP IEEE8021X WPA-NONE "
				 "NONE", buflen);
		if (len >= buflen)
			return -1;
		return len;
	}

	ret = os_snprintf(pos, end - pos, "NONE IEEE8021X");
	if (os_snprintf_error(end - pos, ret))
		return pos - buf;
	pos += ret;

	if (capa->key_mgmt & (WPA_DRIVER_CAPA_KEY_MGMT_WPA |
			      WPA_DRIVER_CAPA_KEY_MGMT_WPA2)) {
		ret = os_snprintf(pos, end - pos, " WPA-EAP");
		if (os_snprintf_error(end - pos, ret))
			return pos - buf;
		pos += ret;
	}

	if (capa->key_mgmt & (WPA_DRIVER_CAPA_KEY_MGMT_WPA_PSK |
			      WPA_DRIVER_CAPA_KEY_MGMT_WPA2_PSK)) {
		ret = os_snprintf(pos, end - pos, " WPA-PSK");
		if (os_snprintf_error(end - pos, ret))
			return pos - buf;
		pos += ret;
	}

	if (capa->key_mgmt & WPA_DRIVER_CAPA_KEY_MGMT_WPA_NONE) {
		ret = os_snprintf(pos, end - pos, " WPA-NONE");
		if (os_snprintf_error(end - pos, ret))
			return pos - buf;
		pos += ret;
	}

#ifdef CONFIG_SUITEB
	if (capa->key_mgmt & WPA_DRIVER_CAPA_KEY_MGMT_SUITE_B) {
		ret = os_snprintf(pos, end - pos, " WPA-EAP-SUITE-B");
		if (os_snprintf_error(end - pos, ret))
			return pos - buf;
		pos += ret;
	}
#endif /* CONFIG_SUITEB */
#ifdef CONFIG_SUITEB192
	if (capa->key_mgmt & WPA_DRIVER_CAPA_KEY_MGMT_SUITE_B_192) {
		ret = os_snprintf(pos, end - pos, " WPA-EAP-SUITE-B-192");
		if (os_snprintf_error(end - pos, ret))
			return pos - buf;
		pos += ret;
	}
#endif /* CONFIG_SUITEB192 */
#ifdef CONFIG_OWE
	if (capa->key_mgmt & WPA_DRIVER_CAPA_KEY_MGMT_OWE) {
		ret = os_snprintf(pos, end - pos, " OWE");
		if (os_snprintf_error(end - pos, ret))
			return pos - buf;
		pos += ret;
	}
#endif /* CONFIG_OWE */
#ifdef CONFIG_DPP
	if (capa->key_mgmt & WPA_DRIVER_CAPA_KEY_MGMT_DPP) {
		ret = os_snprintf(pos, end - pos, " DPP");
		if (os_snprintf_error(end - pos, ret))
			return pos - buf;
		pos += ret;
	}
#endif /* CONFIG_DPP */
#ifdef CONFIG_FILS
	if (capa->key_mgmt & WPA_DRIVER_CAPA_KEY_MGMT_FILS_SHA256) {
		ret = os_snprintf(pos, end - pos, " FILS-SHA256");
		if (os_snprintf_error(end - pos, ret))
			return pos - buf;
		pos += ret;
	}
	if (capa->key_mgmt & WPA_DRIVER_CAPA_KEY_MGMT_FILS_SHA384) {
		ret = os_snprintf(pos, end - pos, " FILS-SHA384");
		if (os_snprintf_error(end - pos, ret))
			return pos - buf;
		pos += ret;
	}
#ifdef CONFIG_IEEE80211R
	if (capa->key_mgmt & WPA_DRIVER_CAPA_KEY_MGMT_FT_FILS_SHA256) {
		ret = os_snprintf(pos, end - pos, " FT-FILS-SHA256");
		if (os_snprintf_error(end - pos, ret))
			return pos - buf;
		pos += ret;
	}
	if (capa->key_mgmt & WPA_DRIVER_CAPA_KEY_MGMT_FT_FILS_SHA384) {
		ret = os_snprintf(pos, end - pos, " FT-FILS-SHA384");
		if (os_snprintf_error(end - pos, ret))
			return pos - buf;
		pos += ret;
	}
#endif /* CONFIG_IEEE80211R */
#endif /* CONFIG_FILS */
#ifdef CONFIG_IEEE80211R
	if (capa->key_mgmt & WPA_DRIVER_CAPA_KEY_MGMT_FT_PSK) {
		ret = os_snprintf(pos, end - pos, " FT-PSK");
		if (os_snprintf_error(end - pos, ret))
			return pos - buf;
		pos += ret;
	}
#endif /* CONFIG_IEEE80211R */
#ifdef CONFIG_SAE
	if (capa->key_mgmt & WPA_DRIVER_CAPA_KEY_MGMT_SAE) {
		ret = os_snprintf(pos, end - pos, " SAE");
		if (os_snprintf_error(end - pos, ret))
			return pos - buf;
		pos += ret;
	}
#endif /* CONFIG_SAE */

	return pos - buf;
}