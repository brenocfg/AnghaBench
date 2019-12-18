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
typedef  int /*<<< orphan*/  dbus_bool_t ;
typedef  int /*<<< orphan*/  DBusMessageIter ;

/* Variables and functions */
 int /*<<< orphan*/  DBUS_TYPE_VARIANT ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  _wpa_dbus_add_dict_entry_end (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _wpa_dbus_add_dict_entry_start (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int const) ; 
 int /*<<< orphan*/  dbus_message_iter_append_basic (int /*<<< orphan*/ *,int const,void const*) ; 
 int /*<<< orphan*/  dbus_message_iter_open_container (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 char* wpa_dbus_type_as_string (int const) ; 

__attribute__((used)) static dbus_bool_t _wpa_dbus_add_dict_entry_basic(DBusMessageIter *iter_dict,
						  const char *key,
						  const int value_type,
						  const void *value)
{
	DBusMessageIter iter_dict_entry, iter_dict_val;
	const char *type_as_string = NULL;

	if (key == NULL)
		return FALSE;

	type_as_string = wpa_dbus_type_as_string(value_type);
	if (!type_as_string)
		return FALSE;

	if (!_wpa_dbus_add_dict_entry_start(iter_dict, &iter_dict_entry,
					    key, value_type) ||
	    !dbus_message_iter_open_container(&iter_dict_entry,
					      DBUS_TYPE_VARIANT,
					      type_as_string, &iter_dict_val) ||
	    !dbus_message_iter_append_basic(&iter_dict_val, value_type, value))
		return FALSE;

	return _wpa_dbus_add_dict_entry_end(iter_dict, &iter_dict_entry,
					    &iter_dict_val);
}