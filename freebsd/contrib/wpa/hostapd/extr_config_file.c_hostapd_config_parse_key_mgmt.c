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

/* Variables and functions */
 int /*<<< orphan*/  MSG_ERROR ; 
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
 int WPA_KEY_MGMT_IEEE8021X_SHA256 ; 
 int WPA_KEY_MGMT_IEEE8021X_SUITE_B ; 
 int WPA_KEY_MGMT_IEEE8021X_SUITE_B_192 ; 
 int WPA_KEY_MGMT_OSEN ; 
 int WPA_KEY_MGMT_OWE ; 
 int WPA_KEY_MGMT_PSK ; 
 int WPA_KEY_MGMT_PSK_SHA256 ; 
 int WPA_KEY_MGMT_SAE ; 
 int /*<<< orphan*/  os_free (char*) ; 
 scalar_t__ os_strcmp (char*,char*) ; 
 char* os_strdup (char const*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int,...) ; 

__attribute__((used)) static int hostapd_config_parse_key_mgmt(int line, const char *value)
{
	int val = 0, last;
	char *start, *end, *buf;

	buf = os_strdup(value);
	if (buf == NULL)
		return -1;
	start = buf;

	while (*start != '\0') {
		while (*start == ' ' || *start == '\t')
			start++;
		if (*start == '\0')
			break;
		end = start;
		while (*end != ' ' && *end != '\t' && *end != '\0')
			end++;
		last = *end == '\0';
		*end = '\0';
		if (os_strcmp(start, "WPA-PSK") == 0)
			val |= WPA_KEY_MGMT_PSK;
		else if (os_strcmp(start, "WPA-EAP") == 0)
			val |= WPA_KEY_MGMT_IEEE8021X;
#ifdef CONFIG_IEEE80211R_AP
		else if (os_strcmp(start, "FT-PSK") == 0)
			val |= WPA_KEY_MGMT_FT_PSK;
		else if (os_strcmp(start, "FT-EAP") == 0)
			val |= WPA_KEY_MGMT_FT_IEEE8021X;
#ifdef CONFIG_SHA384
		else if (os_strcmp(start, "FT-EAP-SHA384") == 0)
			val |= WPA_KEY_MGMT_FT_IEEE8021X_SHA384;
#endif /* CONFIG_SHA384 */
#endif /* CONFIG_IEEE80211R_AP */
#ifdef CONFIG_IEEE80211W
		else if (os_strcmp(start, "WPA-PSK-SHA256") == 0)
			val |= WPA_KEY_MGMT_PSK_SHA256;
		else if (os_strcmp(start, "WPA-EAP-SHA256") == 0)
			val |= WPA_KEY_MGMT_IEEE8021X_SHA256;
#endif /* CONFIG_IEEE80211W */
#ifdef CONFIG_SAE
		else if (os_strcmp(start, "SAE") == 0)
			val |= WPA_KEY_MGMT_SAE;
		else if (os_strcmp(start, "FT-SAE") == 0)
			val |= WPA_KEY_MGMT_FT_SAE;
#endif /* CONFIG_SAE */
#ifdef CONFIG_SUITEB
		else if (os_strcmp(start, "WPA-EAP-SUITE-B") == 0)
			val |= WPA_KEY_MGMT_IEEE8021X_SUITE_B;
#endif /* CONFIG_SUITEB */
#ifdef CONFIG_SUITEB192
		else if (os_strcmp(start, "WPA-EAP-SUITE-B-192") == 0)
			val |= WPA_KEY_MGMT_IEEE8021X_SUITE_B_192;
#endif /* CONFIG_SUITEB192 */
#ifdef CONFIG_FILS
		else if (os_strcmp(start, "FILS-SHA256") == 0)
			val |= WPA_KEY_MGMT_FILS_SHA256;
		else if (os_strcmp(start, "FILS-SHA384") == 0)
			val |= WPA_KEY_MGMT_FILS_SHA384;
#ifdef CONFIG_IEEE80211R_AP
		else if (os_strcmp(start, "FT-FILS-SHA256") == 0)
			val |= WPA_KEY_MGMT_FT_FILS_SHA256;
		else if (os_strcmp(start, "FT-FILS-SHA384") == 0)
			val |= WPA_KEY_MGMT_FT_FILS_SHA384;
#endif /* CONFIG_IEEE80211R_AP */
#endif /* CONFIG_FILS */
#ifdef CONFIG_OWE
		else if (os_strcmp(start, "OWE") == 0)
			val |= WPA_KEY_MGMT_OWE;
#endif /* CONFIG_OWE */
#ifdef CONFIG_DPP
		else if (os_strcmp(start, "DPP") == 0)
			val |= WPA_KEY_MGMT_DPP;
#endif /* CONFIG_DPP */
#ifdef CONFIG_HS20
		else if (os_strcmp(start, "OSEN") == 0)
			val |= WPA_KEY_MGMT_OSEN;
#endif /* CONFIG_HS20 */
		else {
			wpa_printf(MSG_ERROR, "Line %d: invalid key_mgmt '%s'",
				   line, start);
			os_free(buf);
			return -1;
		}

		if (last)
			break;
		start = end + 1;
	}

	os_free(buf);
	if (val == 0) {
		wpa_printf(MSG_ERROR, "Line %d: no key_mgmt values "
			   "configured.", line);
		return -1;
	}

	return val;
}