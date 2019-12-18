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
struct wps_start_params {int dummy; } ;
typedef  int /*<<< orphan*/  DBusMessageIter ;
typedef  int /*<<< orphan*/  DBusMessage ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ os_strcmp (char*,char*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/ * wpas_dbus_error_invalid_args (int /*<<< orphan*/ *,char*) ; 
 int wpas_dbus_handler_wps_bssid (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct wps_start_params*,int /*<<< orphan*/ **) ; 
 int wpas_dbus_handler_wps_p2p_dev_addr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct wps_start_params*,int /*<<< orphan*/ **) ; 
 int wpas_dbus_handler_wps_pin (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct wps_start_params*,int /*<<< orphan*/ **) ; 
 int wpas_dbus_handler_wps_role (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct wps_start_params*,int /*<<< orphan*/ **) ; 
 int wpas_dbus_handler_wps_type (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct wps_start_params*,int /*<<< orphan*/ **) ; 

__attribute__((used)) static int wpas_dbus_handler_wps_start_entry(DBusMessage *message, char *key,
					     DBusMessageIter *entry_iter,
					     struct wps_start_params *params,
					     DBusMessage **reply)
{
	if (os_strcmp(key, "Role") == 0)
		return wpas_dbus_handler_wps_role(message, entry_iter,
						  params, reply);
	else if (os_strcmp(key, "Type") == 0)
		return wpas_dbus_handler_wps_type(message, entry_iter,
						  params, reply);
	else if (os_strcmp(key, "Bssid") == 0)
		return wpas_dbus_handler_wps_bssid(message, entry_iter,
						   params, reply);
	else if (os_strcmp(key, "Pin") == 0)
		return wpas_dbus_handler_wps_pin(message, entry_iter,
						 params, reply);
#ifdef CONFIG_P2P
	else if (os_strcmp(key, "P2PDeviceAddress") == 0)
		return wpas_dbus_handler_wps_p2p_dev_addr(message, entry_iter,
							  params, reply);
#endif /* CONFIG_P2P */

	wpa_printf(MSG_DEBUG, "dbus: WPS.Start - unknown key %s", key);
	*reply = wpas_dbus_error_invalid_args(message, key);
	return -1;
}