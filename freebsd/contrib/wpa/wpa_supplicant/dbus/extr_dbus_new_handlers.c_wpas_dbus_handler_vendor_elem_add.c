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
struct ieee802_11_elems {int dummy; } ;
typedef  size_t dbus_int32_t ;
typedef  int /*<<< orphan*/  DBusMessageIter ;
typedef  int /*<<< orphan*/  DBusMessage ;

/* Variables and functions */
 int /*<<< orphan*/  DBUS_ERROR_INVALID_ARGS ; 
 size_t NUM_VENDOR_ELEM_FRAMES ; 
 scalar_t__ ParseFailed ; 
 int /*<<< orphan*/  dbus_message_iter_get_basic (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  dbus_message_iter_get_fixed_array (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/  dbus_message_iter_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_message_iter_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_message_iter_recurse (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dbus_message_new_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ieee802_11_parse_elems (int /*<<< orphan*/ *,int,struct ieee802_11_elems*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_alloc_copy (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wpabuf_put_data (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ wpabuf_resize (int /*<<< orphan*/ *,int) ; 
 struct wpa_supplicant* wpas_vendor_elem (struct wpa_supplicant*,size_t) ; 
 int /*<<< orphan*/  wpas_vendor_elem_update (struct wpa_supplicant*) ; 

DBusMessage * wpas_dbus_handler_vendor_elem_add(DBusMessage *message,
						struct wpa_supplicant *wpa_s)
{
	u8 *ielems;
	int len;
	struct ieee802_11_elems elems;
	dbus_int32_t frame_id;
	DBusMessageIter	iter, array;

	dbus_message_iter_init(message, &iter);
	dbus_message_iter_get_basic(&iter, &frame_id);
	if (frame_id < 0 || frame_id >= NUM_VENDOR_ELEM_FRAMES) {
		return dbus_message_new_error(message, DBUS_ERROR_INVALID_ARGS,
					      "Invalid ID");
	}

	dbus_message_iter_next(&iter);
	dbus_message_iter_recurse(&iter, &array);
	dbus_message_iter_get_fixed_array(&array, &ielems, &len);
	if (!ielems || len == 0) {
		return dbus_message_new_error(
			message, DBUS_ERROR_INVALID_ARGS, "Invalid value");
	}

	if (ieee802_11_parse_elems(ielems, len, &elems, 0) == ParseFailed) {
		return dbus_message_new_error(message, DBUS_ERROR_INVALID_ARGS,
					      "Parse error");
	}

	wpa_s = wpas_vendor_elem(wpa_s, frame_id);
	if (!wpa_s->vendor_elem[frame_id]) {
		wpa_s->vendor_elem[frame_id] = wpabuf_alloc_copy(ielems, len);
		wpas_vendor_elem_update(wpa_s);
		return NULL;
	}

	if (wpabuf_resize(&wpa_s->vendor_elem[frame_id], len) < 0) {
		return dbus_message_new_error(message, DBUS_ERROR_INVALID_ARGS,
					      "Resize error");
	}

	wpabuf_put_data(wpa_s->vendor_elem[frame_id], ielems, len);
	wpas_vendor_elem_update(wpa_s);
	return NULL;
}