#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wpa_supplicant {int /*<<< orphan*/  dbus_new_path; TYPE_1__* global; TYPE_2__* conf; } ;
struct wpa_dbus_property_desc {int dummy; } ;
typedef  int dbus_bool_t ;
struct TYPE_4__ {int wps_cred_processing; } ;
struct TYPE_3__ {int /*<<< orphan*/  dbus; } ;
typedef  int /*<<< orphan*/  DBusMessageIter ;
typedef  int /*<<< orphan*/  DBusError ;

/* Variables and functions */
 int /*<<< orphan*/  DBUS_TYPE_BOOLEAN ; 
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  WPAS_DBUS_NEW_IFACE_WPS ; 
 int /*<<< orphan*/  wpa_dbus_mark_property_changed (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpas_dbus_simple_property_setter (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 

dbus_bool_t wpas_dbus_setter_process_credentials(
	const struct wpa_dbus_property_desc *property_desc,
	DBusMessageIter *iter, DBusError *error, void *user_data)
{
	struct wpa_supplicant *wpa_s = user_data;
	dbus_bool_t process_credentials, old_pc;

	if (!wpa_s->dbus_new_path)
		return FALSE;
	if (!wpas_dbus_simple_property_setter(iter, error, DBUS_TYPE_BOOLEAN,
					      &process_credentials))
		return FALSE;

	old_pc = wpa_s->conf->wps_cred_processing != 1;
	wpa_s->conf->wps_cred_processing = (process_credentials ? 2 : 1);

	if ((wpa_s->conf->wps_cred_processing != 1) != old_pc)
		wpa_dbus_mark_property_changed(wpa_s->global->dbus,
					       wpa_s->dbus_new_path,
					       WPAS_DBUS_NEW_IFACE_WPS,
					       "ProcessCredentials");

	return TRUE;
}