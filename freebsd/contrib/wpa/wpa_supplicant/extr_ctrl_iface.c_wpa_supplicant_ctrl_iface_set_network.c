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
struct wpa_supplicant {int /*<<< orphan*/  conf; } ;
struct wpa_ssid {int bssid_set; int disabled; int /*<<< orphan*/  bssid; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int atoi (char*) ; 
 scalar_t__ os_memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 char* os_strchr (char*,char) ; 
 int /*<<< orphan*/  os_strlen (char*) ; 
 struct wpa_ssid* wpa_config_get_network (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_hexdump_ascii_key (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int,...) ; 
 int wpa_supplicant_ctrl_iface_update_network (struct wpa_supplicant*,struct wpa_ssid*,char*,char*) ; 
 int /*<<< orphan*/  wpas_notify_network_bssid_set_changed (struct wpa_supplicant*,struct wpa_ssid*) ; 
 int /*<<< orphan*/  wpas_notify_network_type_changed (struct wpa_supplicant*,struct wpa_ssid*) ; 

__attribute__((used)) static int wpa_supplicant_ctrl_iface_set_network(
	struct wpa_supplicant *wpa_s, char *cmd)
{
	int id, ret, prev_bssid_set, prev_disabled;
	struct wpa_ssid *ssid;
	char *name, *value;
	u8 prev_bssid[ETH_ALEN];

	/* cmd: "<network id> <variable name> <value>" */
	name = os_strchr(cmd, ' ');
	if (name == NULL)
		return -1;
	*name++ = '\0';

	value = os_strchr(name, ' ');
	if (value == NULL)
		return -1;
	*value++ = '\0';

	id = atoi(cmd);
	wpa_printf(MSG_DEBUG, "CTRL_IFACE: SET_NETWORK id=%d name='%s'",
		   id, name);
	wpa_hexdump_ascii_key(MSG_DEBUG, "CTRL_IFACE: value",
			      (u8 *) value, os_strlen(value));

	ssid = wpa_config_get_network(wpa_s->conf, id);
	if (ssid == NULL) {
		wpa_printf(MSG_DEBUG, "CTRL_IFACE: Could not find network "
			   "id=%d", id);
		return -1;
	}

	prev_bssid_set = ssid->bssid_set;
	prev_disabled = ssid->disabled;
	os_memcpy(prev_bssid, ssid->bssid, ETH_ALEN);
	ret = wpa_supplicant_ctrl_iface_update_network(wpa_s, ssid, name,
						       value);
	if (ret == 0 &&
	    (ssid->bssid_set != prev_bssid_set ||
	     os_memcmp(ssid->bssid, prev_bssid, ETH_ALEN) != 0))
		wpas_notify_network_bssid_set_changed(wpa_s, ssid);

	if (prev_disabled != ssid->disabled &&
	    (prev_disabled == 2 || ssid->disabled == 2))
		wpas_notify_network_type_changed(wpa_s, ssid);

	return ret;
}