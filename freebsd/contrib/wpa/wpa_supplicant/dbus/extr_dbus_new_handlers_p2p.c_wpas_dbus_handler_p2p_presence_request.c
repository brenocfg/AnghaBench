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
struct wpa_supplicant {int dummy; } ;
struct wpa_dbus_dict_entry {scalar_t__ type; unsigned int uint32_value; int /*<<< orphan*/ * key; } ;
typedef  int /*<<< orphan*/  DBusMessageIter ;
typedef  int /*<<< orphan*/  DBusMessage ;

/* Variables and functions */
 scalar_t__ DBUS_TYPE_INT32 ; 
 int /*<<< orphan*/  dbus_message_iter_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ os_strcmp (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  wpa_dbus_dict_entry_clear (struct wpa_dbus_dict_entry*) ; 
 int /*<<< orphan*/  wpa_dbus_dict_get_entry (int /*<<< orphan*/ *,struct wpa_dbus_dict_entry*) ; 
 scalar_t__ wpa_dbus_dict_has_dict_entry (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_dbus_dict_open_read (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * wpas_dbus_error_invalid_args (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * wpas_dbus_error_unknown_error (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ wpas_p2p_presence_req (struct wpa_supplicant*,unsigned int,unsigned int,unsigned int,unsigned int) ; 

DBusMessage * wpas_dbus_handler_p2p_presence_request(
	DBusMessage *message, struct wpa_supplicant *wpa_s)
{
	unsigned int dur1 = 0, int1 = 0, dur2 = 0, int2 = 0;
	struct wpa_dbus_dict_entry entry;
	DBusMessageIter iter;
	DBusMessageIter iter_dict;

	dbus_message_iter_init(message, &iter);
	entry.key = NULL;

	if (!wpa_dbus_dict_open_read(&iter, &iter_dict, NULL))
		goto error;

	while (wpa_dbus_dict_has_dict_entry(&iter_dict)) {
		if (!wpa_dbus_dict_get_entry(&iter_dict, &entry))
			goto error;

		if (os_strcmp(entry.key, "duration1") == 0 &&
		    entry.type == DBUS_TYPE_INT32)
			dur1 = entry.uint32_value;
		else if (os_strcmp(entry.key, "interval1") == 0 &&
			 entry.type == DBUS_TYPE_INT32)
			int1 = entry.uint32_value;
		else if (os_strcmp(entry.key, "duration2") == 0 &&
			 entry.type == DBUS_TYPE_INT32)
			dur2 = entry.uint32_value;
		else if (os_strcmp(entry.key, "interval2") == 0 &&
			 entry.type == DBUS_TYPE_INT32)
			int2 = entry.uint32_value;
		else
			goto error_clear;

		wpa_dbus_dict_entry_clear(&entry);
	}

	if (wpas_p2p_presence_req(wpa_s, dur1, int1, dur2, int2) < 0)
		return wpas_dbus_error_unknown_error(message,
				"Failed to invoke presence request.");

	return NULL;

error_clear:
	wpa_dbus_dict_entry_clear(&entry);
error:
	return wpas_dbus_error_invalid_args(message, entry.key);
}