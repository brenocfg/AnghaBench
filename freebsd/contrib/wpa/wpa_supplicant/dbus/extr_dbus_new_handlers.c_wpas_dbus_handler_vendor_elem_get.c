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
typedef  int /*<<< orphan*/  u8 ;
struct wpa_supplicant {int /*<<< orphan*/ * vendor_elem; } ;
typedef  size_t dbus_int32_t ;
typedef  int /*<<< orphan*/  DBusMessageIter ;
typedef  int /*<<< orphan*/  DBusMessage ;

/* Variables and functions */
 int /*<<< orphan*/  DBUS_ERROR_INVALID_ARGS ; 
 int /*<<< orphan*/  DBUS_TYPE_ARRAY ; 
 int /*<<< orphan*/  DBUS_TYPE_BYTE ; 
 int /*<<< orphan*/  DBUS_TYPE_BYTE_AS_STRING ; 
 size_t NUM_VENDOR_ELEM_FRAMES ; 
 int /*<<< orphan*/  dbus_message_iter_append_fixed_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const**,size_t) ; 
 int /*<<< orphan*/  dbus_message_iter_close_container (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_message_iter_get_basic (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  dbus_message_iter_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_message_iter_init_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_message_iter_open_container (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dbus_message_new_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * dbus_message_new_method_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_message_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * wpabuf_head_u8 (int /*<<< orphan*/ ) ; 
 size_t wpabuf_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * wpas_dbus_error_no_memory (int /*<<< orphan*/ *) ; 
 struct wpa_supplicant* wpas_vendor_elem (struct wpa_supplicant*,size_t) ; 

DBusMessage * wpas_dbus_handler_vendor_elem_get(DBusMessage *message,
						struct wpa_supplicant *wpa_s)
{
	DBusMessage *reply;
	DBusMessageIter	iter, array_iter;
	dbus_int32_t frame_id;
	const u8 *elem;
	size_t elem_len;

	dbus_message_iter_init(message, &iter);
	dbus_message_iter_get_basic(&iter, &frame_id);

	if (frame_id < 0 || frame_id >= NUM_VENDOR_ELEM_FRAMES) {
		return dbus_message_new_error(message, DBUS_ERROR_INVALID_ARGS,
					      "Invalid ID");
	}

	wpa_s = wpas_vendor_elem(wpa_s, frame_id);
	if (!wpa_s->vendor_elem[frame_id]) {
		return dbus_message_new_error(message, DBUS_ERROR_INVALID_ARGS,
					      "ID value does not exist");
	}

	reply = dbus_message_new_method_return(message);
	if (!reply)
		return wpas_dbus_error_no_memory(message);

	dbus_message_iter_init_append(reply, &iter);

	elem = wpabuf_head_u8(wpa_s->vendor_elem[frame_id]);
	elem_len = wpabuf_len(wpa_s->vendor_elem[frame_id]);

	if (!dbus_message_iter_open_container(&iter, DBUS_TYPE_ARRAY,
					      DBUS_TYPE_BYTE_AS_STRING,
					      &array_iter) ||
	    !dbus_message_iter_append_fixed_array(&array_iter, DBUS_TYPE_BYTE,
						  &elem, elem_len) ||
	    !dbus_message_iter_close_container(&iter, &array_iter)) {
		dbus_message_unref(reply);
		reply = wpas_dbus_error_no_memory(message);
	}

	return reply;
}