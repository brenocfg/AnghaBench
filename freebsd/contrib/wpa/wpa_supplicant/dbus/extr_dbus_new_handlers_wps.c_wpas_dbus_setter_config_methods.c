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
struct wpa_supplicant {TYPE_1__* conf; } ;
struct wpa_dbus_property_desc {int dummy; } ;
typedef  int /*<<< orphan*/  dbus_bool_t ;
struct TYPE_2__ {char* config_methods; int /*<<< orphan*/  changed_parameters; } ;
typedef  int /*<<< orphan*/  DBusMessageIter ;
typedef  int /*<<< orphan*/  DBusError ;

/* Variables and functions */
 int /*<<< orphan*/  CFG_CHANGED_CONFIG_METHODS ; 
 int /*<<< orphan*/  DBUS_TYPE_STRING ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  os_free (char*) ; 
 char* os_strdup (char*) ; 
 int /*<<< orphan*/  wpa_supplicant_update_config (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  wpas_dbus_simple_property_setter (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 

dbus_bool_t wpas_dbus_setter_config_methods(
	const struct wpa_dbus_property_desc *property_desc,
	DBusMessageIter *iter, DBusError *error, void *user_data)
{
	struct wpa_supplicant *wpa_s = user_data;
	char *methods, *new_methods;

	if (!wpas_dbus_simple_property_setter(iter, error, DBUS_TYPE_STRING,
					      &methods))
		return FALSE;

	new_methods = os_strdup(methods);
	if (!new_methods)
		return FALSE;

	os_free(wpa_s->conf->config_methods);
	wpa_s->conf->config_methods = new_methods;

	wpa_s->conf->changed_parameters |= CFG_CHANGED_CONFIG_METHODS;
	wpa_supplicant_update_config(wpa_s);

	return TRUE;
}