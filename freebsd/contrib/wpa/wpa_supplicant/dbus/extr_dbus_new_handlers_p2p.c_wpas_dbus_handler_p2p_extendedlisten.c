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
struct wpa_supplicant {TYPE_1__* global; } ;
struct wpa_dbus_dict_entry {scalar_t__ type; unsigned int uint32_value; int /*<<< orphan*/ * key; } ;
struct TYPE_2__ {struct wpa_supplicant* p2p_init_wpa_s; } ;
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
 scalar_t__ wpas_p2p_ext_listen (struct wpa_supplicant*,unsigned int,unsigned int) ; 

DBusMessage * wpas_dbus_handler_p2p_extendedlisten(
	DBusMessage *message, struct wpa_supplicant *wpa_s)
{
	unsigned int period = 0, interval = 0;
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

		if (os_strcmp(entry.key, "period") == 0 &&
		    entry.type == DBUS_TYPE_INT32)
			period = entry.uint32_value;
		else if (os_strcmp(entry.key, "interval") == 0 &&
			 entry.type == DBUS_TYPE_INT32)
			interval = entry.uint32_value;
		else
			goto error_clear;
		wpa_dbus_dict_entry_clear(&entry);
	}

	wpa_s = wpa_s->global->p2p_init_wpa_s;

	if (wpas_p2p_ext_listen(wpa_s, period, interval))
		return wpas_dbus_error_unknown_error(
			message, "failed to initiate a p2p_ext_listen.");

	return NULL;

error_clear:
	wpa_dbus_dict_entry_clear(&entry);
error:
	return wpas_dbus_error_invalid_args(message, entry.key);
}