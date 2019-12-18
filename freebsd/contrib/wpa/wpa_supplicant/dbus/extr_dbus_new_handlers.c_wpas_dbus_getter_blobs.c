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
struct wpa_supplicant {TYPE_1__* conf; } ;
struct wpa_dbus_property_desc {int dummy; } ;
struct wpa_config_blob {struct wpa_config_blob* next; int /*<<< orphan*/  len; int /*<<< orphan*/  data; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  dbus_bool_t ;
struct TYPE_2__ {struct wpa_config_blob* blobs; } ;
typedef  int /*<<< orphan*/  DBusMessageIter ;
typedef  int /*<<< orphan*/  DBusError ;

/* Variables and functions */
 int /*<<< orphan*/  DBUS_ERROR_NO_MEMORY ; 
 int /*<<< orphan*/  DBUS_TYPE_ARRAY ; 
 int /*<<< orphan*/  DBUS_TYPE_BYTE ; 
 char* DBUS_TYPE_BYTE_AS_STRING ; 
 int /*<<< orphan*/  DBUS_TYPE_DICT_ENTRY ; 
 int /*<<< orphan*/  DBUS_TYPE_STRING ; 
 int /*<<< orphan*/  DBUS_TYPE_VARIANT ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  dbus_message_iter_append_basic (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_message_iter_append_fixed_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbus_message_iter_close_container (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_message_iter_open_container (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_set_error_const (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

dbus_bool_t wpas_dbus_getter_blobs(
	const struct wpa_dbus_property_desc *property_desc,
	DBusMessageIter *iter, DBusError *error, void *user_data)
{
	struct wpa_supplicant *wpa_s = user_data;
	DBusMessageIter variant_iter, dict_iter, entry_iter, array_iter;
	struct wpa_config_blob *blob;

	if (!dbus_message_iter_open_container(iter, DBUS_TYPE_VARIANT,
					      "a{say}", &variant_iter) ||
	    !dbus_message_iter_open_container(&variant_iter, DBUS_TYPE_ARRAY,
					      "{say}", &dict_iter)) {
		dbus_set_error_const(error, DBUS_ERROR_NO_MEMORY, "no memory");
		return FALSE;
	}

	blob = wpa_s->conf->blobs;
	while (blob) {
		if (!dbus_message_iter_open_container(&dict_iter,
						      DBUS_TYPE_DICT_ENTRY,
						      NULL, &entry_iter) ||
		    !dbus_message_iter_append_basic(&entry_iter,
						    DBUS_TYPE_STRING,
						    &(blob->name)) ||
		    !dbus_message_iter_open_container(&entry_iter,
						      DBUS_TYPE_ARRAY,
						      DBUS_TYPE_BYTE_AS_STRING,
						      &array_iter) ||
		    !dbus_message_iter_append_fixed_array(&array_iter,
							  DBUS_TYPE_BYTE,
							  &(blob->data),
							  blob->len) ||
		    !dbus_message_iter_close_container(&entry_iter,
						       &array_iter) ||
		    !dbus_message_iter_close_container(&dict_iter,
						       &entry_iter)) {
			dbus_set_error_const(error, DBUS_ERROR_NO_MEMORY,
					     "no memory");
			return FALSE;
		}

		blob = blob->next;
	}

	if (!dbus_message_iter_close_container(&variant_iter, &dict_iter) ||
	    !dbus_message_iter_close_container(iter, &variant_iter)) {
		dbus_set_error_const(error, DBUS_ERROR_NO_MEMORY, "no memory");
		return FALSE;
	}

	return TRUE;
}