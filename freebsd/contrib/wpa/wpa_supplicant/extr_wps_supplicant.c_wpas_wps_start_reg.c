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
typedef  int /*<<< orphan*/  val ;
typedef  int /*<<< orphan*/  u8 ;
struct wps_new_ap_settings {int /*<<< orphan*/  key_hex; int /*<<< orphan*/  encr; int /*<<< orphan*/  auth; int /*<<< orphan*/  ssid_hex; } ;
struct wpa_supplicant {scalar_t__ wps_fragment_size; scalar_t__ ap_iface; } ;
struct TYPE_2__ {scalar_t__ fragment_size; } ;
struct wpa_ssid {int temporary; TYPE_1__ eap; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  WPS_PBC_WALK_TIME ; 
 int /*<<< orphan*/  eloop_register_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wpa_supplicant*,int /*<<< orphan*/ *) ; 
 int os_snprintf (char*,int,char*,...) ; 
 scalar_t__ os_snprintf_error (int,int) ; 
 scalar_t__ wpa_config_set (struct wpa_ssid*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpas_clear_wps (struct wpa_supplicant*) ; 
 struct wpa_ssid* wpas_wps_add_network (struct wpa_supplicant*,int,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  wpas_wps_reassoc (struct wpa_supplicant*,struct wpa_ssid*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpas_wps_timeout ; 

int wpas_wps_start_reg(struct wpa_supplicant *wpa_s, const u8 *bssid,
		       const char *pin, struct wps_new_ap_settings *settings)
{
	struct wpa_ssid *ssid;
	char val[200];
	char *pos, *end;
	int res;

#ifdef CONFIG_AP
	if (wpa_s->ap_iface) {
		wpa_printf(MSG_DEBUG,
			   "WPS: Reject request to start Registrar(as station) operation while AP mode is enabled");
		return -1;
	}
#endif /* CONFIG_AP */
	if (!pin)
		return -1;
	wpas_clear_wps(wpa_s);
	ssid = wpas_wps_add_network(wpa_s, 1, NULL, bssid);
	if (ssid == NULL)
		return -1;
	ssid->temporary = 1;
	pos = val;
	end = pos + sizeof(val);
	res = os_snprintf(pos, end - pos, "\"pin=%s", pin);
	if (os_snprintf_error(end - pos, res))
		return -1;
	pos += res;
	if (settings) {
		res = os_snprintf(pos, end - pos, " new_ssid=%s new_auth=%s "
				  "new_encr=%s new_key=%s",
				  settings->ssid_hex, settings->auth,
				  settings->encr, settings->key_hex);
		if (os_snprintf_error(end - pos, res))
			return -1;
		pos += res;
	}
	res = os_snprintf(pos, end - pos, "\"");
	if (os_snprintf_error(end - pos, res))
		return -1;
	if (wpa_config_set(ssid, "phase1", val, 0) < 0)
		return -1;
	if (wpa_s->wps_fragment_size)
		ssid->eap.fragment_size = wpa_s->wps_fragment_size;
	eloop_register_timeout(WPS_PBC_WALK_TIME, 0, wpas_wps_timeout,
			       wpa_s, NULL);
	wpas_wps_reassoc(wpa_s, ssid, bssid, 0);
	return 0;
}