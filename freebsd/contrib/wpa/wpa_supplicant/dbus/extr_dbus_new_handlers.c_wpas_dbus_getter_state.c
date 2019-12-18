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
struct wpa_supplicant {int /*<<< orphan*/  wpa_state; } ;
struct wpa_dbus_property_desc {int dummy; } ;
typedef  int /*<<< orphan*/  dbus_bool_t ;
typedef  int /*<<< orphan*/  DBusMessageIter ;
typedef  int /*<<< orphan*/  DBusError ;

/* Variables and functions */
 int /*<<< orphan*/  DBUS_ERROR_NO_MEMORY ; 
 int /*<<< orphan*/  DBUS_TYPE_STRING ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  dbus_set_error_const (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  os_free (char*) ; 
 char* os_strdup (char const*) ; 
 char tolower (char) ; 
 char* wpa_supplicant_state_txt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpas_dbus_simple_property_getter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**,int /*<<< orphan*/ *) ; 

dbus_bool_t wpas_dbus_getter_state(
	const struct wpa_dbus_property_desc *property_desc,
	DBusMessageIter *iter, DBusError *error, void *user_data)
{
	struct wpa_supplicant *wpa_s = user_data;
	const char *str_state;
	char *state_ls, *tmp;
	dbus_bool_t success = FALSE;

	str_state = wpa_supplicant_state_txt(wpa_s->wpa_state);

	/* make state string lowercase to fit new DBus API convention
	 */
	state_ls = tmp = os_strdup(str_state);
	if (!tmp) {
		dbus_set_error_const(error, DBUS_ERROR_NO_MEMORY, "no memory");
		return FALSE;
	}
	while (*tmp) {
		*tmp = tolower(*tmp);
		tmp++;
	}

	success = wpas_dbus_simple_property_getter(iter, DBUS_TYPE_STRING,
						   &state_ls, error);

	os_free(state_ls);

	return success;
}