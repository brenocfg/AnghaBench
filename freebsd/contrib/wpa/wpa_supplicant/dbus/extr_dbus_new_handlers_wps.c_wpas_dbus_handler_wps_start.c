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
struct wps_start_params {int type; int role; int /*<<< orphan*/  bssid; int /*<<< orphan*/ * pin; int /*<<< orphan*/  p2p_dev_addr; } ;
struct wpa_supplicant {scalar_t__ ap_iface; } ;
typedef  int /*<<< orphan*/  params ;
typedef  int /*<<< orphan*/  npin ;
typedef  int /*<<< orphan*/  DBusMessageIter ;
typedef  int /*<<< orphan*/  DBusMessage ;

/* Variables and functions */
 scalar_t__ DBUS_TYPE_DICT_ENTRY ; 
 int /*<<< orphan*/  DEV_PW_DEFAULT ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ dbus_message_iter_get_arg_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_message_iter_get_basic (int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  dbus_message_iter_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_message_iter_init_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_message_iter_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_message_iter_recurse (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dbus_message_new_method_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_message_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_memset (struct wps_start_params*,int /*<<< orphan*/ ,int) ; 
 int os_snprintf (char*,int,char*,int) ; 
 scalar_t__ os_snprintf_error (int,int) ; 
 scalar_t__ os_strlen (char*) ; 
 int /*<<< orphan*/  wpa_dbus_dict_append_string (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  wpa_dbus_dict_close_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_dbus_dict_open_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int wpa_supplicant_ap_wps_pbc (struct wpa_supplicant*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wpa_supplicant_ap_wps_pin (struct wpa_supplicant*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * wpas_dbus_error_invalid_args (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * wpas_dbus_error_no_memory (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * wpas_dbus_error_unknown_error (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ wpas_dbus_handler_wps_start_entry (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,struct wps_start_params*,int /*<<< orphan*/ **) ; 
 int wpas_wps_start_pbc (struct wpa_supplicant*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wpas_wps_start_pin (struct wpa_supplicant*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wpas_wps_start_reg (struct wpa_supplicant*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

DBusMessage * wpas_dbus_handler_wps_start(DBusMessage *message,
					  struct wpa_supplicant *wpa_s)
{
	DBusMessage *reply = NULL;
	DBusMessageIter iter, dict_iter, entry_iter;
	struct wps_start_params params;
	char *key;
	char npin[9] = { '\0' };
	int ret;

	os_memset(&params, 0, sizeof(params));
	dbus_message_iter_init(message, &iter);

	dbus_message_iter_recurse(&iter, &dict_iter);
	while (dbus_message_iter_get_arg_type(&dict_iter) ==
	       DBUS_TYPE_DICT_ENTRY) {
		dbus_message_iter_recurse(&dict_iter, &entry_iter);

		dbus_message_iter_get_basic(&entry_iter, &key);
		dbus_message_iter_next(&entry_iter);

		if (wpas_dbus_handler_wps_start_entry(message, key,
						      &entry_iter,
						      &params, &reply))
			return reply;

		dbus_message_iter_next(&dict_iter);
	}

#ifdef CONFIG_AP
	if (wpa_s->ap_iface && params.type == 1) {
		if (params.pin == NULL) {
			wpa_printf(MSG_DEBUG,
				   "dbus: WPS.Start - Pin required for registrar role");
			return wpas_dbus_error_invalid_args(
				message, "Pin required for registrar role.");
		}
		ret = wpa_supplicant_ap_wps_pin(wpa_s,
						params.bssid,
						params.pin,
						npin, sizeof(npin), 0);
	} else if (wpa_s->ap_iface) {
		ret = wpa_supplicant_ap_wps_pbc(wpa_s,
						params.bssid,
						params.p2p_dev_addr);
	} else
#endif /* CONFIG_AP */
	if (params.role == 0) {
		wpa_printf(MSG_DEBUG, "dbus: WPS.Start - Role not specified");
		return wpas_dbus_error_invalid_args(message,
						    "Role not specified");
	} else if (params.role == 2) {
		if (params.pin == NULL) {
			wpa_printf(MSG_DEBUG,
				   "dbus: WPS.Start - Pin required for registrar role");
			return wpas_dbus_error_invalid_args(
				message, "Pin required for registrar role.");
		}
		ret = wpas_wps_start_reg(wpa_s, params.bssid, params.pin,
					 NULL);
	} else if (params.type == 0) {
		wpa_printf(MSG_DEBUG, "dbus: WPS.Start - Type not specified");
		return wpas_dbus_error_invalid_args(message,
						    "Type not specified");
	} else if (params.type == 1) {
		ret = wpas_wps_start_pin(wpa_s, params.bssid,
					 params.pin, 0,
					 DEV_PW_DEFAULT);
		if (ret > 0) {
			ret = os_snprintf(npin, sizeof(npin), "%08d", ret);
			if (os_snprintf_error(sizeof(npin), ret))
				return wpas_dbus_error_unknown_error(
					message, "invalid PIN");
		}
	} else {
		ret = wpas_wps_start_pbc(wpa_s, params.bssid, 0, 0);
	}

	if (ret < 0) {
		wpa_printf(MSG_DEBUG,
			   "dbus: WPS.Start wpas_wps_failed in role %s and key %s",
			   (params.role == 1 ? "enrollee" : "registrar"),
			   (params.type == 0 ? "" :
			    (params.type == 1 ? "pin" : "pbc")));
		return wpas_dbus_error_unknown_error(message,
						     "WPS start failed");
	}

	reply = dbus_message_new_method_return(message);
	if (!reply)
		return wpas_dbus_error_no_memory(message);

	dbus_message_iter_init_append(reply, &iter);
	if (!wpa_dbus_dict_open_write(&iter, &dict_iter) ||
	    (os_strlen(npin) > 0 &&
	     !wpa_dbus_dict_append_string(&dict_iter, "Pin", npin)) ||
	    !wpa_dbus_dict_close_write(&iter, &dict_iter)) {
		dbus_message_unref(reply);
		return wpas_dbus_error_no_memory(message);
	}

	return reply;
}