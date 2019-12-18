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
struct wpa_supplicant {int /*<<< orphan*/  conf; TYPE_2__* parent; TYPE_1__* global; } ;
struct wpa_ssid {int disabled; } ;
struct wpa_dbus_dict_entry {char* key; scalar_t__ type; int bool_value; int int32_value; int /*<<< orphan*/  str_value; } ;
struct TYPE_4__ {char* dbus_new_path; } ;
struct TYPE_3__ {struct wpa_supplicant* p2p_init_wpa_s; } ;
typedef  int /*<<< orphan*/  DBusMessageIter ;
typedef  int /*<<< orphan*/  DBusMessage ;

/* Variables and functions */
 scalar_t__ DBUS_TYPE_BOOLEAN ; 
 scalar_t__ DBUS_TYPE_INT32 ; 
 scalar_t__ DBUS_TYPE_OBJECT_PATH ; 
 scalar_t__ EINVAL ; 
 int /*<<< orphan*/  WPAS_DBUS_NEW_PERSISTENT_GROUPS_PART ; 
 int /*<<< orphan*/  dbus_message_iter_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  os_free (char*) ; 
 scalar_t__ os_strcmp (char*,char*) ; 
 char* os_strdup (int /*<<< orphan*/ ) ; 
 unsigned int strtoul (char*,int /*<<< orphan*/ *,int) ; 
 struct wpa_ssid* wpa_config_get_network (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  wpa_dbus_dict_entry_clear (struct wpa_dbus_dict_entry*) ; 
 int /*<<< orphan*/  wpa_dbus_dict_get_entry (int /*<<< orphan*/ *,struct wpa_dbus_dict_entry*) ; 
 scalar_t__ wpa_dbus_dict_has_dict_entry (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_dbus_dict_open_read (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * wpas_dbus_error_invalid_args (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * wpas_dbus_error_unknown_error (int /*<<< orphan*/ *,char*) ; 
 char* wpas_dbus_new_decompose_object_path (char*,int /*<<< orphan*/ ,char**) ; 
 scalar_t__ wpas_p2p_group_add (struct wpa_supplicant*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ wpas_p2p_group_add_persistent (struct wpa_supplicant*,struct wpa_ssid*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

DBusMessage * wpas_dbus_handler_p2p_group_add(DBusMessage *message,
					      struct wpa_supplicant *wpa_s)
{
	DBusMessageIter iter_dict;
	DBusMessage *reply = NULL;
	DBusMessageIter iter;
	struct wpa_dbus_dict_entry entry;
	char *pg_object_path = NULL;
	int persistent_group = 0;
	int freq = 0;
	char *iface = NULL;
	unsigned int group_id = 0;
	struct wpa_ssid *ssid;

	dbus_message_iter_init(message, &iter);

	if (!wpa_dbus_dict_open_read(&iter, &iter_dict, NULL))
		goto inv_args;

	while (wpa_dbus_dict_has_dict_entry(&iter_dict)) {
		if (!wpa_dbus_dict_get_entry(&iter_dict, &entry))
			goto inv_args;

		if (os_strcmp(entry.key, "persistent") == 0 &&
		    entry.type == DBUS_TYPE_BOOLEAN) {
			persistent_group = entry.bool_value;
		} else if (os_strcmp(entry.key, "frequency") == 0 &&
			   entry.type == DBUS_TYPE_INT32) {
			freq = entry.int32_value;
			if (freq <= 0)
				goto inv_args_clear;
		} else if (os_strcmp(entry.key, "persistent_group_object") ==
			   0 &&
			   entry.type == DBUS_TYPE_OBJECT_PATH)
			pg_object_path = os_strdup(entry.str_value);
		else
			goto inv_args_clear;

		wpa_dbus_dict_entry_clear(&entry);
	}

	wpa_s = wpa_s->global->p2p_init_wpa_s;

	if (pg_object_path != NULL) {
		char *net_id_str;

		/*
		 * A persistent group Object Path is defined meaning we want
		 * to re-invoke a persistent group.
		 */

		iface = wpas_dbus_new_decompose_object_path(
			pg_object_path, WPAS_DBUS_NEW_PERSISTENT_GROUPS_PART,
			&net_id_str);
		if (iface == NULL || net_id_str == NULL ||
		    !wpa_s->parent->dbus_new_path ||
		    os_strcmp(iface, wpa_s->parent->dbus_new_path) != 0) {
			reply =
			    wpas_dbus_error_invalid_args(message,
							 pg_object_path);
			goto out;
		}

		group_id = strtoul(net_id_str, NULL, 10);
		if (errno == EINVAL) {
			reply = wpas_dbus_error_invalid_args(
						message, pg_object_path);
			goto out;
		}

		/* Get the SSID structure from the persistent group id */
		ssid = wpa_config_get_network(wpa_s->conf, group_id);
		if (ssid == NULL || ssid->disabled != 2)
			goto inv_args;

		if (wpas_p2p_group_add_persistent(wpa_s, ssid, 0, freq, 0, 0, 0,
						  0, 0, 0, NULL, 0, 0)) {
			reply = wpas_dbus_error_unknown_error(
				message,
				"Failed to reinvoke a persistent group");
			goto out;
		}
	} else if (wpas_p2p_group_add(wpa_s, persistent_group, freq, 0, 0, 0,
				      0, 0))
		goto inv_args;

out:
	os_free(pg_object_path);
	os_free(iface);
	return reply;
inv_args_clear:
	wpa_dbus_dict_entry_clear(&entry);
inv_args:
	reply = wpas_dbus_error_invalid_args(message, NULL);
	goto out;
}