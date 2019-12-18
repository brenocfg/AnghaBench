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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u64 ;
struct wpabuf {int dummy; } ;
struct wpa_supplicant {TYPE_1__* global; } ;
struct wpa_dbus_dict_entry {scalar_t__ type; scalar_t__ uint32_value; scalar_t__ array_type; int /*<<< orphan*/  array_len; int /*<<< orphan*/  bytearray_value; int /*<<< orphan*/  key; int /*<<< orphan*/  str_value; } ;
struct TYPE_2__ {int /*<<< orphan*/  p2p; } ;
typedef  int /*<<< orphan*/  DBusMessageIter ;
typedef  int /*<<< orphan*/  DBusMessage ;

/* Variables and functions */
 scalar_t__ DBUS_TYPE_ARRAY ; 
 scalar_t__ DBUS_TYPE_BYTE ; 
 scalar_t__ DBUS_TYPE_INT32 ; 
 int /*<<< orphan*/  DBUS_TYPE_INVALID ; 
 scalar_t__ DBUS_TYPE_OBJECT_PATH ; 
 scalar_t__ DBUS_TYPE_STRING ; 
 int /*<<< orphan*/  DBUS_TYPE_UINT64 ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  dbus_message_append_args (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbus_message_iter_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dbus_message_new_method_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_free (char*) ; 
 scalar_t__ os_strcmp (int /*<<< orphan*/ ,char*) ; 
 char* os_strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p2p_peer_known (int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ parse_peer_object_path (char*,scalar_t__*) ; 
 int /*<<< orphan*/  wpa_dbus_dict_entry_clear (struct wpa_dbus_dict_entry*) ; 
 int /*<<< orphan*/  wpa_dbus_dict_get_entry (int /*<<< orphan*/ *,struct wpa_dbus_dict_entry*) ; 
 scalar_t__ wpa_dbus_dict_has_dict_entry (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_dbus_dict_open_read (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct wpabuf* wpabuf_alloc_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 int /*<<< orphan*/ * wpas_dbus_error_invalid_args (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * wpas_dbus_error_unknown_error (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ wpas_p2p_sd_request (struct wpa_supplicant*,scalar_t__*,struct wpabuf*) ; 
 scalar_t__ wpas_p2p_sd_request_upnp (struct wpa_supplicant*,scalar_t__*,scalar_t__,char*) ; 

DBusMessage * wpas_dbus_handler_p2p_service_sd_req(
	DBusMessage *message, struct wpa_supplicant *wpa_s)
{
	DBusMessageIter iter_dict;
	DBusMessage *reply = NULL;
	DBusMessageIter iter;
	struct wpa_dbus_dict_entry entry;
	int upnp = 0;
	char *service = NULL;
	char *peer_object_path = NULL;
	struct wpabuf *tlv = NULL;
	u8 version = 0;
	u64 ref = 0;
	u8 addr_buf[ETH_ALEN], *addr;

	dbus_message_iter_init(message, &iter);

	if (!wpa_dbus_dict_open_read(&iter, &iter_dict, NULL))
		goto error;

	while (wpa_dbus_dict_has_dict_entry(&iter_dict)) {
		if (!wpa_dbus_dict_get_entry(&iter_dict, &entry))
			goto error;
		if (os_strcmp(entry.key, "peer_object") == 0 &&
		    entry.type == DBUS_TYPE_OBJECT_PATH) {
			peer_object_path = os_strdup(entry.str_value);
		} else if (os_strcmp(entry.key, "service_type") == 0 &&
			   entry.type == DBUS_TYPE_STRING) {
			if (os_strcmp(entry.str_value, "upnp") == 0)
				upnp = 1;
			else
				goto error_clear;
		} else if (os_strcmp(entry.key, "version") == 0 &&
			   entry.type == DBUS_TYPE_INT32) {
			version = entry.uint32_value;
		} else if (os_strcmp(entry.key, "service") == 0 &&
			   entry.type == DBUS_TYPE_STRING) {
			service = os_strdup(entry.str_value);
		} else if (os_strcmp(entry.key, "tlv") == 0) {
			if (entry.type != DBUS_TYPE_ARRAY ||
			    entry.array_type != DBUS_TYPE_BYTE)
				goto error_clear;
			tlv = wpabuf_alloc_copy(entry.bytearray_value,
						entry.array_len);
		} else
			goto error_clear;

		wpa_dbus_dict_entry_clear(&entry);
	}

	if (!peer_object_path) {
		addr = NULL;
	} else {
		if (parse_peer_object_path(peer_object_path, addr_buf) < 0 ||
		    !p2p_peer_known(wpa_s->global->p2p, addr_buf))
			goto error;

		addr = addr_buf;
	}

	if (upnp == 1) {
		if (version <= 0 || service == NULL)
			goto error;

		ref = wpas_p2p_sd_request_upnp(wpa_s, addr, version, service);
	} else {
		if (tlv == NULL)
			goto error;
		ref = wpas_p2p_sd_request(wpa_s, addr, tlv);
		wpabuf_free(tlv);
	}

	if (ref != 0) {
		reply = dbus_message_new_method_return(message);
		dbus_message_append_args(reply, DBUS_TYPE_UINT64,
					 &ref, DBUS_TYPE_INVALID);
	} else {
		reply = wpas_dbus_error_unknown_error(
			message, "Unable to send SD request");
	}
out:
	os_free(service);
	os_free(peer_object_path);
	return reply;
error_clear:
	wpa_dbus_dict_entry_clear(&entry);
error:
	if (tlv)
		wpabuf_free(tlv);
	reply = wpas_dbus_error_invalid_args(message, NULL);
	goto out;
}