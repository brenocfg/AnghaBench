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
struct hostapd_iface {size_t num_bss; int wait_channel_update; struct hostapd_data** bss; int /*<<< orphan*/ * phy; scalar_t__ driver_ap_teardown; } ;
struct hostapd_data {TYPE_1__* iconf; int /*<<< orphan*/  drv_priv; int /*<<< orphan*/  driver; } ;
struct TYPE_2__ {scalar_t__* country; } ;

/* Variables and functions */
 int /*<<< orphan*/  HAPD_IFACE_COUNTRY_UPDATE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  channel_list_update_timeout ; 
 int /*<<< orphan*/  eloop_register_timeout (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hostapd_iface*,int /*<<< orphan*/ *) ; 
 char* hostapd_drv_get_radio_name (struct hostapd_data*) ; 
 scalar_t__ hostapd_get_country (struct hostapd_data*,char*) ; 
 scalar_t__ hostapd_set_country (struct hostapd_data*,char*) ; 
 int /*<<< orphan*/  hostapd_set_state (struct hostapd_iface*,int /*<<< orphan*/ ) ; 
 scalar_t__ hostapd_validate_bssid_configuration (struct hostapd_iface*) ; 
 int /*<<< orphan*/  os_memcpy (char*,scalar_t__*,int) ; 
 int /*<<< orphan*/  os_strlcpy (int /*<<< orphan*/ *,char const*,int) ; 
 scalar_t__ os_strncmp (char*,char*,int) ; 
 int setup_interface2 (struct hostapd_iface*) ; 
 scalar_t__ start_ctrl_iface (struct hostapd_iface*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int setup_interface(struct hostapd_iface *iface)
{
	struct hostapd_data *hapd = iface->bss[0];
	size_t i;

	/*
	 * It is possible that setup_interface() is called after the interface
	 * was disabled etc., in which case driver_ap_teardown is possibly set
	 * to 1. Clear it here so any other key/station deletion, which is not
	 * part of a teardown flow, would also call the relevant driver
	 * callbacks.
	 */
	iface->driver_ap_teardown = 0;

	if (!iface->phy[0]) {
		const char *phy = hostapd_drv_get_radio_name(hapd);
		if (phy) {
			wpa_printf(MSG_DEBUG, "phy: %s", phy);
			os_strlcpy(iface->phy, phy, sizeof(iface->phy));
		}
	}

	/*
	 * Make sure that all BSSes get configured with a pointer to the same
	 * driver interface.
	 */
	for (i = 1; i < iface->num_bss; i++) {
		iface->bss[i]->driver = hapd->driver;
		iface->bss[i]->drv_priv = hapd->drv_priv;
	}

	if (hostapd_validate_bssid_configuration(iface))
		return -1;

	/*
	 * Initialize control interfaces early to allow external monitoring of
	 * channel setup operations that may take considerable amount of time
	 * especially for DFS cases.
	 */
	if (start_ctrl_iface(iface))
		return -1;

	if (hapd->iconf->country[0] && hapd->iconf->country[1]) {
		char country[4], previous_country[4];

		hostapd_set_state(iface, HAPD_IFACE_COUNTRY_UPDATE);
		if (hostapd_get_country(hapd, previous_country) < 0)
			previous_country[0] = '\0';

		os_memcpy(country, hapd->iconf->country, 3);
		country[3] = '\0';
		if (hostapd_set_country(hapd, country) < 0) {
			wpa_printf(MSG_ERROR, "Failed to set country code");
			return -1;
		}

		wpa_printf(MSG_DEBUG, "Previous country code %s, new country code %s",
			   previous_country, country);

		if (os_strncmp(previous_country, country, 2) != 0) {
			wpa_printf(MSG_DEBUG, "Continue interface setup after channel list update");
			iface->wait_channel_update = 1;
			eloop_register_timeout(5, 0,
					       channel_list_update_timeout,
					       iface, NULL);
			return 0;
		}
	}

	return setup_interface2(iface);
}