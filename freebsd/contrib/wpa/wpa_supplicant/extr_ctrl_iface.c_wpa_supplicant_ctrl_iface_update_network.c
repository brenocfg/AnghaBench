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
struct wpa_supplicant {int /*<<< orphan*/  conf; int /*<<< orphan*/  eapol; struct wpa_ssid* current_ssid; int /*<<< orphan*/  wpa; } ;
struct wpa_ssid {scalar_t__ passphrase; scalar_t__ ssid_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  eapol_sm_invalidate_cached_session (int /*<<< orphan*/ ) ; 
 scalar_t__ os_strcmp (char*,char*) ; 
 int wpa_config_set (struct wpa_ssid*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_config_update_prio_list (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_config_update_psk (struct wpa_ssid*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  wpa_sm_pmksa_cache_flush (int /*<<< orphan*/ ,struct wpa_ssid*) ; 

__attribute__((used)) static int wpa_supplicant_ctrl_iface_update_network(
	struct wpa_supplicant *wpa_s, struct wpa_ssid *ssid,
	char *name, char *value)
{
	int ret;

	ret = wpa_config_set(ssid, name, value, 0);
	if (ret < 0) {
		wpa_printf(MSG_DEBUG, "CTRL_IFACE: Failed to set network "
			   "variable '%s'", name);
		return -1;
	}
	if (ret == 1)
		return 0; /* No change to the previously configured value */

	if (os_strcmp(name, "bssid") != 0 &&
	    os_strcmp(name, "bssid_hint") != 0 &&
	    os_strcmp(name, "priority") != 0) {
		wpa_sm_pmksa_cache_flush(wpa_s->wpa, ssid);

		if (wpa_s->current_ssid == ssid ||
		    wpa_s->current_ssid == NULL) {
			/*
			 * Invalidate the EAP session cache if anything in the
			 * current or previously used configuration changes.
			 */
			eapol_sm_invalidate_cached_session(wpa_s->eapol);
		}
	}

	if ((os_strcmp(name, "psk") == 0 &&
	     value[0] == '"' && ssid->ssid_len) ||
	    (os_strcmp(name, "ssid") == 0 && ssid->passphrase))
		wpa_config_update_psk(ssid);
	else if (os_strcmp(name, "priority") == 0)
		wpa_config_update_prio_list(wpa_s->conf);

	return 0;
}