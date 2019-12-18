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
struct hostapd_data {int mbo_assoc_disallow; int /*<<< orphan*/  iface; int /*<<< orphan*/  parameter_set_count; TYPE_1__* conf; int /*<<< orphan*/  iconf; void* dpp_configurator_params; void* dpp_ignore_netaccesskey_mismatch; void* dpp_groups_override; void* dpp_discovery_override; void* dpp_config_obj_override; void* ext_eapol_frame_io; void* ext_mgmt_frame_handling; } ;
struct TYPE_2__ {int /*<<< orphan*/  mbo_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 void* atoi (char*) ; 
 void* dpp_test ; 
 int /*<<< orphan*/  hostapd_disassoc_accept_mac (struct hostapd_data*) ; 
 int /*<<< orphan*/  hostapd_disassoc_deny_mac (struct hostapd_data*) ; 
 int hostapd_set_iface (int /*<<< orphan*/ ,TYPE_1__*,char*,char*) ; 
 int /*<<< orphan*/  hostapd_wps_update_ie (struct hostapd_data*) ; 
 scalar_t__ ieee802_11_update_beacons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_free (void*) ; 
 scalar_t__ os_strcasecmp (char*,char*) ; 
 char* os_strchr (char*,char) ; 
 void* os_strdup (char*) ; 
 scalar_t__ os_strncmp (char*,char*,int) ; 
 long strtol (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wps_corrupt_pkhash ; 
 int /*<<< orphan*/  wps_testing_dummy_cred ; 
 int wps_version_number ; 

__attribute__((used)) static int hostapd_ctrl_iface_set(struct hostapd_data *hapd, char *cmd)
{
	char *value;
	int ret = 0;

	value = os_strchr(cmd, ' ');
	if (value == NULL)
		return -1;
	*value++ = '\0';

	wpa_printf(MSG_DEBUG, "CTRL_IFACE SET '%s'='%s'", cmd, value);
	if (0) {
#ifdef CONFIG_WPS_TESTING
	} else if (os_strcasecmp(cmd, "wps_version_number") == 0) {
		long int val;
		val = strtol(value, NULL, 0);
		if (val < 0 || val > 0xff) {
			ret = -1;
			wpa_printf(MSG_DEBUG, "WPS: Invalid "
				   "wps_version_number %ld", val);
		} else {
			wps_version_number = val;
			wpa_printf(MSG_DEBUG, "WPS: Testing - force WPS "
				   "version %u.%u",
				   (wps_version_number & 0xf0) >> 4,
				   wps_version_number & 0x0f);
			hostapd_wps_update_ie(hapd);
		}
	} else if (os_strcasecmp(cmd, "wps_testing_dummy_cred") == 0) {
		wps_testing_dummy_cred = atoi(value);
		wpa_printf(MSG_DEBUG, "WPS: Testing - dummy_cred=%d",
			   wps_testing_dummy_cred);
	} else if (os_strcasecmp(cmd, "wps_corrupt_pkhash") == 0) {
		wps_corrupt_pkhash = atoi(value);
		wpa_printf(MSG_DEBUG, "WPS: Testing - wps_corrupt_pkhash=%d",
			   wps_corrupt_pkhash);
#endif /* CONFIG_WPS_TESTING */
#ifdef CONFIG_TESTING_OPTIONS
	} else if (os_strcasecmp(cmd, "ext_mgmt_frame_handling") == 0) {
		hapd->ext_mgmt_frame_handling = atoi(value);
	} else if (os_strcasecmp(cmd, "ext_eapol_frame_io") == 0) {
		hapd->ext_eapol_frame_io = atoi(value);
#ifdef CONFIG_DPP
	} else if (os_strcasecmp(cmd, "dpp_config_obj_override") == 0) {
		os_free(hapd->dpp_config_obj_override);
		hapd->dpp_config_obj_override = os_strdup(value);
	} else if (os_strcasecmp(cmd, "dpp_discovery_override") == 0) {
		os_free(hapd->dpp_discovery_override);
		hapd->dpp_discovery_override = os_strdup(value);
	} else if (os_strcasecmp(cmd, "dpp_groups_override") == 0) {
		os_free(hapd->dpp_groups_override);
		hapd->dpp_groups_override = os_strdup(value);
	} else if (os_strcasecmp(cmd,
				 "dpp_ignore_netaccesskey_mismatch") == 0) {
		hapd->dpp_ignore_netaccesskey_mismatch = atoi(value);
	} else if (os_strcasecmp(cmd, "dpp_test") == 0) {
		dpp_test = atoi(value);
#endif /* CONFIG_DPP */
#endif /* CONFIG_TESTING_OPTIONS */
#ifdef CONFIG_MBO
	} else if (os_strcasecmp(cmd, "mbo_assoc_disallow") == 0) {
		int val;

		if (!hapd->conf->mbo_enabled)
			return -1;

		val = atoi(value);
		if (val < 0 || val > 1)
			return -1;

		hapd->mbo_assoc_disallow = val;
		ieee802_11_update_beacons(hapd->iface);

		/*
		 * TODO: Need to configure drivers that do AP MLME offload with
		 * disallowing station logic.
		 */
#endif /* CONFIG_MBO */
#ifdef CONFIG_DPP
	} else if (os_strcasecmp(cmd, "dpp_configurator_params") == 0) {
		os_free(hapd->dpp_configurator_params);
		hapd->dpp_configurator_params = os_strdup(value);
#endif /* CONFIG_DPP */
	} else {
		ret = hostapd_set_iface(hapd->iconf, hapd->conf, cmd, value);
		if (ret)
			return ret;

		if (os_strcasecmp(cmd, "deny_mac_file") == 0) {
			hostapd_disassoc_deny_mac(hapd);
		} else if (os_strcasecmp(cmd, "accept_mac_file") == 0) {
			hostapd_disassoc_accept_mac(hapd);
		} else if (os_strncmp(cmd, "wme_ac_", 7) == 0 ||
			   os_strncmp(cmd, "wmm_ac_", 7) == 0) {
			hapd->parameter_set_count++;
			if (ieee802_11_update_beacons(hapd->iface))
				wpa_printf(MSG_DEBUG,
					   "Failed to update beacons with WMM parameters");
		}
	}

	return ret;
}