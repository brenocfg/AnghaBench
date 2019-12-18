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
struct wps_start_params {int /*<<< orphan*/  bssid; } ;
typedef  int /*<<< orphan*/  DBusMessageIter ;
typedef  int /*<<< orphan*/  DBusMessage ;

/* Variables and functions */
 scalar_t__ DBUS_TYPE_ARRAY ; 
 scalar_t__ DBUS_TYPE_BYTE ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ dbus_message_iter_get_arg_type (int /*<<< orphan*/ *) ; 
 scalar_t__ dbus_message_iter_get_element_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_message_iter_get_fixed_array (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  dbus_message_iter_recurse (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * wpas_dbus_error_invalid_args (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int wpas_dbus_handler_wps_bssid(DBusMessage *message,
				       DBusMessageIter *entry_iter,
				       struct wps_start_params *params,
				       DBusMessage **reply)
{
	DBusMessageIter variant_iter, array_iter;
	int len;

	dbus_message_iter_recurse(entry_iter, &variant_iter);
	if (dbus_message_iter_get_arg_type(&variant_iter) != DBUS_TYPE_ARRAY ||
	    dbus_message_iter_get_element_type(&variant_iter) !=
	    DBUS_TYPE_BYTE) {
		wpa_printf(MSG_DEBUG,
			   "dbus: WPS.Start - Wrong Bssid type, byte array required");
		*reply = wpas_dbus_error_invalid_args(
			message, "Bssid must be a byte array");
		return -1;
	}
	dbus_message_iter_recurse(&variant_iter, &array_iter);
	dbus_message_iter_get_fixed_array(&array_iter, &params->bssid, &len);
	if (len != ETH_ALEN) {
		wpa_printf(MSG_DEBUG, "dbus: WPS.Start - Wrong Bssid length %d",
			   len);
		*reply = wpas_dbus_error_invalid_args(message,
						      "Bssid is wrong length");
		return -1;
	}
	return 0;
}