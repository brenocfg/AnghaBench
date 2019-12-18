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
struct wpa_supplicant {char* dbus_new_path; } ;
struct wpa_interface {char* driver; char* ifname; char* confname; char* bridge_ifname; } ;
struct wpa_global {int dummy; } ;
struct wpa_dbus_dict_entry {scalar_t__ type; int /*<<< orphan*/  str_value; int /*<<< orphan*/  key; } ;
typedef  int /*<<< orphan*/  iface ;
typedef  int /*<<< orphan*/  DBusMessageIter ;
typedef  int /*<<< orphan*/  DBusMessage ;

/* Variables and functions */
 int /*<<< orphan*/  DBUS_TYPE_INVALID ; 
 int /*<<< orphan*/  DBUS_TYPE_OBJECT_PATH ; 
 scalar_t__ DBUS_TYPE_STRING ; 
 int /*<<< orphan*/  WPAS_DBUS_ERROR_IFACE_EXISTS ; 
 int /*<<< orphan*/  dbus_message_append_args (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbus_message_iter_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dbus_message_new_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * dbus_message_new_method_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_free (char*) ; 
 int /*<<< orphan*/  os_memset (struct wpa_interface*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ os_strcmp (int /*<<< orphan*/ ,char*) ; 
 char* os_strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_dbus_dict_entry_clear (struct wpa_dbus_dict_entry*) ; 
 int /*<<< orphan*/  wpa_dbus_dict_get_entry (int /*<<< orphan*/ *,struct wpa_dbus_dict_entry*) ; 
 scalar_t__ wpa_dbus_dict_has_dict_entry (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_dbus_dict_open_read (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct wpa_supplicant* wpa_supplicant_add_iface (struct wpa_global*,struct wpa_interface*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * wpa_supplicant_get_iface (struct wpa_global*,char*) ; 
 int /*<<< orphan*/ * wpas_dbus_error_invalid_args (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * wpas_dbus_error_no_memory (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * wpas_dbus_error_unknown_error (int /*<<< orphan*/ *,char*) ; 

DBusMessage * wpas_dbus_handler_create_interface(DBusMessage *message,
						 struct wpa_global *global)
{
	DBusMessageIter iter_dict;
	DBusMessage *reply = NULL;
	DBusMessageIter iter;
	struct wpa_dbus_dict_entry entry;
	char *driver = NULL;
	char *ifname = NULL;
	char *confname = NULL;
	char *bridge_ifname = NULL;

	dbus_message_iter_init(message, &iter);

	if (!wpa_dbus_dict_open_read(&iter, &iter_dict, NULL))
		goto error;
	while (wpa_dbus_dict_has_dict_entry(&iter_dict)) {
		if (!wpa_dbus_dict_get_entry(&iter_dict, &entry))
			goto error;
		if (os_strcmp(entry.key, "Driver") == 0 &&
		    entry.type == DBUS_TYPE_STRING) {
			os_free(driver);
			driver = os_strdup(entry.str_value);
			wpa_dbus_dict_entry_clear(&entry);
			if (driver == NULL)
				goto oom;
		} else if (os_strcmp(entry.key, "Ifname") == 0 &&
			   entry.type == DBUS_TYPE_STRING) {
			os_free(ifname);
			ifname = os_strdup(entry.str_value);
			wpa_dbus_dict_entry_clear(&entry);
			if (ifname == NULL)
				goto oom;
		} else if (os_strcmp(entry.key, "ConfigFile") == 0 &&
			   entry.type == DBUS_TYPE_STRING) {
			os_free(confname);
			confname = os_strdup(entry.str_value);
			wpa_dbus_dict_entry_clear(&entry);
			if (confname == NULL)
				goto oom;
		} else if (os_strcmp(entry.key, "BridgeIfname") == 0 &&
			   entry.type == DBUS_TYPE_STRING) {
			os_free(bridge_ifname);
			bridge_ifname = os_strdup(entry.str_value);
			wpa_dbus_dict_entry_clear(&entry);
			if (bridge_ifname == NULL)
				goto oom;
		} else {
			wpa_dbus_dict_entry_clear(&entry);
			goto error;
		}
	}

	if (ifname == NULL)
		goto error; /* Required Ifname argument missing */

	/*
	 * Try to get the wpa_supplicant record for this iface, return
	 * an error if we already control it.
	 */
	if (wpa_supplicant_get_iface(global, ifname) != NULL) {
		reply = dbus_message_new_error(
			message, WPAS_DBUS_ERROR_IFACE_EXISTS,
			"wpa_supplicant already controls this interface.");
	} else {
		struct wpa_supplicant *wpa_s;
		struct wpa_interface iface;

		os_memset(&iface, 0, sizeof(iface));
		iface.driver = driver;
		iface.ifname = ifname;
		iface.confname = confname;
		iface.bridge_ifname = bridge_ifname;
		/* Otherwise, have wpa_supplicant attach to it. */
		wpa_s = wpa_supplicant_add_iface(global, &iface, NULL);
		if (wpa_s && wpa_s->dbus_new_path) {
			const char *path = wpa_s->dbus_new_path;

			reply = dbus_message_new_method_return(message);
			dbus_message_append_args(reply, DBUS_TYPE_OBJECT_PATH,
						 &path, DBUS_TYPE_INVALID);
		} else {
			reply = wpas_dbus_error_unknown_error(
				message,
				"wpa_supplicant couldn't grab this interface.");
		}
	}

out:
	os_free(driver);
	os_free(ifname);
	os_free(confname);
	os_free(bridge_ifname);
	return reply;

error:
	reply = wpas_dbus_error_invalid_args(message, NULL);
	goto out;
oom:
	reply = wpas_dbus_error_no_memory(message);
	goto out;
}