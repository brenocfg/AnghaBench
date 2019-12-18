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
struct wpabuf {int dummy; } ;
struct wpa_supplicant {TYPE_1__* global; } ;
struct wpa_dbus_dict_entry {scalar_t__ type; int uint32_value; scalar_t__ array_type; int /*<<< orphan*/  array_len; int /*<<< orphan*/  bytearray_value; int /*<<< orphan*/  key; int /*<<< orphan*/  str_value; } ;
struct TYPE_2__ {int /*<<< orphan*/  p2p; } ;
typedef  int /*<<< orphan*/  DBusMessageIter ;
typedef  int /*<<< orphan*/  DBusMessage ;

/* Variables and functions */
 scalar_t__ DBUS_TYPE_ARRAY ; 
 scalar_t__ DBUS_TYPE_BYTE ; 
 scalar_t__ DBUS_TYPE_INT32 ; 
 scalar_t__ DBUS_TYPE_OBJECT_PATH ; 
 scalar_t__ DBUS_TYPE_UINT32 ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  dbus_message_iter_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_free (char*) ; 
 scalar_t__ os_strcmp (int /*<<< orphan*/ ,char*) ; 
 char* os_strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p2p_peer_known (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ parse_peer_object_path (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_dbus_dict_entry_clear (struct wpa_dbus_dict_entry*) ; 
 int /*<<< orphan*/  wpa_dbus_dict_get_entry (int /*<<< orphan*/ *,struct wpa_dbus_dict_entry*) ; 
 scalar_t__ wpa_dbus_dict_has_dict_entry (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_dbus_dict_open_read (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct wpabuf* wpabuf_alloc_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 int /*<<< orphan*/ * wpas_dbus_error_invalid_args (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpas_p2p_sd_response (struct wpa_supplicant*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct wpabuf*) ; 

DBusMessage * wpas_dbus_handler_p2p_service_sd_res(
	DBusMessage *message, struct wpa_supplicant *wpa_s)
{
	DBusMessageIter iter_dict;
	DBusMessage *reply = NULL;
	DBusMessageIter iter;
	struct wpa_dbus_dict_entry entry;
	char *peer_object_path = NULL;
	struct wpabuf *tlv = NULL;
	int freq = 0;
	int dlg_tok = 0;
	u8 addr[ETH_ALEN];

	dbus_message_iter_init(message, &iter);

	if (!wpa_dbus_dict_open_read(&iter, &iter_dict, NULL))
		goto error;

	while (wpa_dbus_dict_has_dict_entry(&iter_dict)) {
		if (!wpa_dbus_dict_get_entry(&iter_dict, &entry))
			goto error;

		if (os_strcmp(entry.key, "peer_object") == 0 &&
		    entry.type == DBUS_TYPE_OBJECT_PATH) {
			peer_object_path = os_strdup(entry.str_value);
		} else if (os_strcmp(entry.key, "frequency") == 0 &&
			   entry.type == DBUS_TYPE_INT32) {
			freq = entry.uint32_value;
		} else if (os_strcmp(entry.key, "dialog_token") == 0 &&
			   (entry.type == DBUS_TYPE_UINT32 ||
			    entry.type == DBUS_TYPE_INT32)) {
			dlg_tok = entry.uint32_value;
		} else if (os_strcmp(entry.key, "tlvs") == 0) {
			if (entry.type != DBUS_TYPE_ARRAY ||
			    entry.array_type != DBUS_TYPE_BYTE)
				goto error_clear;
			tlv = wpabuf_alloc_copy(entry.bytearray_value,
						entry.array_len);
		} else
			goto error_clear;

		wpa_dbus_dict_entry_clear(&entry);
	}
	if (parse_peer_object_path(peer_object_path, addr) < 0 ||
	    !p2p_peer_known(wpa_s->global->p2p, addr) ||
	    tlv == NULL)
		goto error;

	wpas_p2p_sd_response(wpa_s, freq, addr, (u8) dlg_tok, tlv);
	wpabuf_free(tlv);
out:
	os_free(peer_object_path);
	return reply;
error_clear:
	wpa_dbus_dict_entry_clear(&entry);
error:
	reply = wpas_dbus_error_invalid_args(message, NULL);
	goto out;
}