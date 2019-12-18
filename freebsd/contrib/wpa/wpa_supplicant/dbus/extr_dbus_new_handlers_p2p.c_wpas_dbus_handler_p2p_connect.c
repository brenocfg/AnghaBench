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
typedef  int /*<<< orphan*/  u8 ;
struct wpa_supplicant {TYPE_1__* global; } ;
struct wpa_dbus_dict_entry {scalar_t__ type; int bool_value; int int32_value; int /*<<< orphan*/  str_value; int /*<<< orphan*/  key; } ;
typedef  int /*<<< orphan*/  npin ;
typedef  enum p2p_wps_method { ____Placeholder_p2p_wps_method } p2p_wps_method ;
struct TYPE_2__ {struct wpa_supplicant* p2p_init_wpa_s; int /*<<< orphan*/  p2p; } ;
typedef  int /*<<< orphan*/  DBusMessageIter ;
typedef  int /*<<< orphan*/  DBusMessage ;

/* Variables and functions */
 scalar_t__ DBUS_TYPE_BOOLEAN ; 
 scalar_t__ DBUS_TYPE_INT32 ; 
 int /*<<< orphan*/  DBUS_TYPE_INVALID ; 
 scalar_t__ DBUS_TYPE_OBJECT_PATH ; 
 scalar_t__ DBUS_TYPE_STRING ; 
 int ETH_ALEN ; 
 char* WPAS_DBUS_ERROR_CONNECT_CHANNEL_UNAVAILABLE ; 
 char* WPAS_DBUS_ERROR_CONNECT_CHANNEL_UNSUPPORTED ; 
 char* WPAS_DBUS_ERROR_CONNECT_UNSPECIFIED_ERROR ; 
 int WPS_NOT_READY ; 
 int WPS_PBC ; 
 int WPS_PIN_DISPLAY ; 
 int WPS_PIN_KEYPAD ; 
 int /*<<< orphan*/  dbus_message_append_args (int /*<<< orphan*/ *,scalar_t__,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbus_message_iter_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dbus_message_new_error (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/ * dbus_message_new_method_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_free (char*) ; 
 int os_snprintf (char*,int,char*,int) ; 
 scalar_t__ os_snprintf_error (int,int) ; 
 scalar_t__ os_strcmp (int /*<<< orphan*/ ,char*) ; 
 char* os_strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p2p_peer_known (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ parse_peer_object_path (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_dbus_dict_entry_clear (struct wpa_dbus_dict_entry*) ; 
 int /*<<< orphan*/  wpa_dbus_dict_get_entry (int /*<<< orphan*/ *,struct wpa_dbus_dict_entry*) ; 
 scalar_t__ wpa_dbus_dict_has_dict_entry (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_dbus_dict_open_read (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_dbus_p2p_check_enabled (struct wpa_supplicant*,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * wpas_dbus_error_invalid_args (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * wpas_dbus_error_unknown_error (int /*<<< orphan*/ *,char*) ; 
 int wpas_p2p_connect (struct wpa_supplicant*,int /*<<< orphan*/ *,char*,int,int,int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

DBusMessage * wpas_dbus_handler_p2p_connect(DBusMessage *message,
					    struct wpa_supplicant *wpa_s)
{
	DBusMessageIter iter_dict;
	DBusMessage *reply = NULL;
	DBusMessageIter iter;
	struct wpa_dbus_dict_entry entry;
	char *peer_object_path = NULL;
	int persistent_group = 0;
	int join = 0;
	int authorize_only = 0;
	int go_intent = -1;
	int freq = 0;
	u8 addr[ETH_ALEN];
	char *pin = NULL;
	enum p2p_wps_method wps_method = WPS_NOT_READY;
	int new_pin;
	char *err_msg = NULL;
	char *iface = NULL;
	int ret;

	if (!wpa_dbus_p2p_check_enabled(wpa_s, message, &reply, NULL))
		return reply;

	dbus_message_iter_init(message, &iter);

	if (!wpa_dbus_dict_open_read(&iter, &iter_dict, NULL))
		goto inv_args;

	while (wpa_dbus_dict_has_dict_entry(&iter_dict)) {
		if (!wpa_dbus_dict_get_entry(&iter_dict, &entry))
			goto inv_args;

		if (os_strcmp(entry.key, "peer") == 0 &&
		    entry.type == DBUS_TYPE_OBJECT_PATH) {
			peer_object_path = os_strdup(entry.str_value);
		} else if (os_strcmp(entry.key, "persistent") == 0 &&
			   entry.type == DBUS_TYPE_BOOLEAN) {
			persistent_group = entry.bool_value;
		} else if (os_strcmp(entry.key, "join") == 0 &&
			   entry.type == DBUS_TYPE_BOOLEAN) {
			join = entry.bool_value;
		} else if (os_strcmp(entry.key, "authorize_only") == 0 &&
			   entry.type == DBUS_TYPE_BOOLEAN) {
			authorize_only = entry.bool_value;
		} else if (os_strcmp(entry.key, "frequency") == 0 &&
			   entry.type == DBUS_TYPE_INT32) {
			freq = entry.int32_value;
			if (freq <= 0)
				goto inv_args_clear;
		} else if (os_strcmp(entry.key, "go_intent") == 0 &&
			   entry.type == DBUS_TYPE_INT32) {
			go_intent = entry.int32_value;
			if ((go_intent < 0) || (go_intent > 15))
				goto inv_args_clear;
		} else if (os_strcmp(entry.key, "wps_method") == 0 &&
			   entry.type == DBUS_TYPE_STRING) {
			if (os_strcmp(entry.str_value, "pbc") == 0)
				wps_method = WPS_PBC;
			else if (os_strcmp(entry.str_value, "pin") == 0)
				wps_method = WPS_PIN_DISPLAY;
			else if (os_strcmp(entry.str_value, "display") == 0)
				wps_method = WPS_PIN_DISPLAY;
			else if (os_strcmp(entry.str_value, "keypad") == 0)
				wps_method = WPS_PIN_KEYPAD;
			else
				goto inv_args_clear;
		} else if (os_strcmp(entry.key, "pin") == 0 &&
			   entry.type == DBUS_TYPE_STRING) {
			pin = os_strdup(entry.str_value);
		} else
			goto inv_args_clear;

		wpa_dbus_dict_entry_clear(&entry);
	}

	if (wps_method == WPS_NOT_READY ||
	    parse_peer_object_path(peer_object_path, addr) < 0 ||
	    !p2p_peer_known(wpa_s->global->p2p, addr))
		goto inv_args;

	/*
	 * Validate the wps_method specified and the pin value.
	 */
	if ((!pin || !pin[0]) && wps_method == WPS_PIN_KEYPAD)
		goto inv_args;

	wpa_s = wpa_s->global->p2p_init_wpa_s;

	new_pin = wpas_p2p_connect(wpa_s, addr, pin, wps_method,
				   persistent_group, 0, join, authorize_only,
				   go_intent, freq, 0, -1, 0, 0, 0, 0, 0,
				   NULL, 0);

	if (new_pin >= 0) {
		char npin[9];
		char *generated_pin;

		ret = os_snprintf(npin, sizeof(npin), "%08d", new_pin);
		if (os_snprintf_error(sizeof(npin), ret)) {
			reply = wpas_dbus_error_unknown_error(message,
							      "invalid PIN");
			goto out;
		}
		generated_pin = npin;
		reply = dbus_message_new_method_return(message);
		dbus_message_append_args(reply, DBUS_TYPE_STRING,
					 &generated_pin, DBUS_TYPE_INVALID);
	} else {
		switch (new_pin) {
		case -2:
			err_msg =
				"connect failed due to channel unavailability.";
			iface = WPAS_DBUS_ERROR_CONNECT_CHANNEL_UNAVAILABLE;
			break;

		case -3:
			err_msg = "connect failed due to unsupported channel.";
			iface = WPAS_DBUS_ERROR_CONNECT_CHANNEL_UNSUPPORTED;
			break;

		default:
			err_msg = "connect failed due to unspecified error.";
			iface = WPAS_DBUS_ERROR_CONNECT_UNSPECIFIED_ERROR;
			break;
		}

		/*
		 * TODO:
		 * Do we need specialized errors corresponding to above
		 * error conditions as against just returning a different
		 * error message?
		 */
		reply = dbus_message_new_error(message, iface, err_msg);
	}

out:
	os_free(peer_object_path);
	os_free(pin);
	return reply;
inv_args_clear:
	wpa_dbus_dict_entry_clear(&entry);
inv_args:
	reply = wpas_dbus_error_invalid_args(message, NULL);
	goto out;
}