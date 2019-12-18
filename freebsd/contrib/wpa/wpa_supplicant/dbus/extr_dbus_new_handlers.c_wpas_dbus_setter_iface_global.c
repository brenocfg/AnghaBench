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
struct wpa_supplicant {int /*<<< orphan*/  conf; } ;
struct wpa_dbus_property_desc {char const* data; int /*<<< orphan*/  dbus_property; } ;
typedef  int /*<<< orphan*/  dbus_bool_t ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  DBusMessageIter ;
typedef  int /*<<< orphan*/  DBusError ;

/* Variables and functions */
 int /*<<< orphan*/  DBUS_ERROR_INVALID_ARGS ; 
 int /*<<< orphan*/  DBUS_TYPE_STRING ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WPAS_DBUS_ERROR_UNKNOWN_ERROR ; 
 int /*<<< orphan*/  dbus_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int os_snprintf (char*,size_t,char*,char const*,char const*) ; 
 scalar_t__ os_snprintf_error (size_t,int) ; 
 int os_strlen (char const*) ; 
 scalar_t__ wpa_config_process_global (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  wpa_supplicant_update_config (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  wpas_dbus_simple_property_setter (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const**) ; 

dbus_bool_t wpas_dbus_setter_iface_global(
	const struct wpa_dbus_property_desc *property_desc,
	DBusMessageIter *iter, DBusError *error, void *user_data)
{
	struct wpa_supplicant *wpa_s = user_data;
	const char *new_value = NULL;
	char buf[250];
	size_t combined_len;
	int ret;

	if (!wpas_dbus_simple_property_setter(iter, error, DBUS_TYPE_STRING,
					      &new_value))
		return FALSE;

	combined_len = os_strlen(property_desc->data) + os_strlen(new_value) +
		3;
	if (combined_len >= sizeof(buf)) {
		dbus_set_error(error, DBUS_ERROR_INVALID_ARGS,
			       "Interface property %s value too large",
			       property_desc->dbus_property);
		return FALSE;
	}

	if (!new_value[0])
		new_value = "NULL";

	ret = os_snprintf(buf, combined_len, "%s=%s", property_desc->data,
			  new_value);
	if (os_snprintf_error(combined_len, ret)) {
		dbus_set_error(error,  WPAS_DBUS_ERROR_UNKNOWN_ERROR,
			       "Failed to construct new interface property %s",
			       property_desc->dbus_property);
		return FALSE;
	}

	if (wpa_config_process_global(wpa_s->conf, buf, -1)) {
		dbus_set_error(error, DBUS_ERROR_INVALID_ARGS,
			       "Failed to set interface property %s",
			       property_desc->dbus_property);
		return FALSE;
	}

	wpa_supplicant_update_config(wpa_s);
	return TRUE;
}