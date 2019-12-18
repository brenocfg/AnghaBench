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
struct wpa_supplicant {scalar_t__ wpa_state; scalar_t__ key_mgmt; TYPE_1__* current_ssid; } ;
struct wpa_dbus_property_desc {int dummy; } ;
typedef  int /*<<< orphan*/  dbus_bool_t ;
struct TYPE_2__ {int /*<<< orphan*/  proto; } ;
typedef  int /*<<< orphan*/  DBusMessageIter ;
typedef  int /*<<< orphan*/  DBusError ;

/* Variables and functions */
 int /*<<< orphan*/  DBUS_TYPE_STRING ; 
 int WPAS_DBUS_AUTH_MODE_MAX ; 
 scalar_t__ WPA_COMPLETED ; 
 scalar_t__ WPA_KEY_MGMT_IEEE8021X ; 
 scalar_t__ WPA_KEY_MGMT_IEEE8021X_NO_WPA ; 
 int /*<<< orphan*/  os_snprintf (char*,int,char*,char const*) ; 
 char* wpa_key_mgmt_txt (scalar_t__,int /*<<< orphan*/ ) ; 
 char* wpa_supplicant_get_eap_mode (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  wpas_dbus_simple_property_getter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const**,int /*<<< orphan*/ *) ; 

dbus_bool_t wpas_dbus_getter_current_auth_mode(
	const struct wpa_dbus_property_desc *property_desc,
	DBusMessageIter *iter, DBusError *error, void *user_data)
{
	struct wpa_supplicant *wpa_s = user_data;
	const char *eap_mode;
	const char *auth_mode;
	char eap_mode_buf[WPAS_DBUS_AUTH_MODE_MAX];

	if (wpa_s->wpa_state != WPA_COMPLETED) {
		auth_mode = "INACTIVE";
	} else if (wpa_s->key_mgmt == WPA_KEY_MGMT_IEEE8021X ||
	    wpa_s->key_mgmt == WPA_KEY_MGMT_IEEE8021X_NO_WPA) {
		eap_mode = wpa_supplicant_get_eap_mode(wpa_s);
		os_snprintf(eap_mode_buf, WPAS_DBUS_AUTH_MODE_MAX,
			    "EAP-%s", eap_mode);
		auth_mode = eap_mode_buf;

	} else if (wpa_s->current_ssid) {
		auth_mode = wpa_key_mgmt_txt(wpa_s->key_mgmt,
					     wpa_s->current_ssid->proto);
	} else {
		auth_mode = "UNKNOWN";
	}

	return wpas_dbus_simple_property_getter(iter, DBUS_TYPE_STRING,
						&auth_mode, error);
}