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
struct wpa_supplicant {TYPE_1__* global; } ;
struct wpa_dbus_dict_entry {scalar_t__ type; int /*<<< orphan*/  str_value; int /*<<< orphan*/  key; } ;
struct TYPE_2__ {int /*<<< orphan*/  p2p; } ;
typedef  int /*<<< orphan*/  DBusMessageIter ;
typedef  int /*<<< orphan*/  DBusMessage ;

/* Variables and functions */
 scalar_t__ DBUS_TYPE_OBJECT_PATH ; 
 scalar_t__ DBUS_TYPE_STRING ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  dbus_message_iter_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ hwaddr_aton (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_free (char*) ; 
 scalar_t__ os_strcmp (int /*<<< orphan*/ ,char*) ; 
 char* os_strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p2p_peer_known (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ parse_peer_object_path (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_dbus_dict_entry_clear (struct wpa_dbus_dict_entry*) ; 
 int /*<<< orphan*/  wpa_dbus_dict_get_entry (int /*<<< orphan*/ *,struct wpa_dbus_dict_entry*) ; 
 scalar_t__ wpa_dbus_dict_has_dict_entry (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_dbus_dict_open_read (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_dbus_p2p_check_enabled (struct wpa_supplicant*,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * wpas_dbus_error_invalid_args (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  wpas_p2p_remove_client (struct wpa_supplicant*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

DBusMessage * wpas_dbus_handler_p2p_remove_client(DBusMessage *message,
						  struct wpa_supplicant *wpa_s)
{
	DBusMessageIter iter_dict;
	DBusMessage *reply = NULL;
	DBusMessageIter iter;
	struct wpa_dbus_dict_entry entry;
	char *peer_object_path = NULL;
	char *interface_addr = NULL;
	u8 peer_addr[ETH_ALEN];

	if (!wpa_dbus_p2p_check_enabled(wpa_s, message, &reply, NULL))
		return reply;

	dbus_message_iter_init(message, &iter);

	if (!wpa_dbus_dict_open_read(&iter, &iter_dict, NULL))
		goto err;

	while (wpa_dbus_dict_has_dict_entry(&iter_dict)) {
		if (!wpa_dbus_dict_get_entry(&iter_dict, &entry))
			goto err;

		if (os_strcmp(entry.key, "peer") == 0 &&
		    entry.type == DBUS_TYPE_OBJECT_PATH) {
			os_free(peer_object_path);
			peer_object_path = os_strdup(entry.str_value);
			wpa_dbus_dict_entry_clear(&entry);
		} else if (os_strcmp(entry.key, "iface") == 0 &&
			   entry.type == DBUS_TYPE_STRING) {
			os_free(interface_addr);
			interface_addr = os_strdup(entry.str_value);
			wpa_dbus_dict_entry_clear(&entry);
		} else {
			wpa_dbus_dict_entry_clear(&entry);
			goto err;
		}
	}

	if ((!peer_object_path && !interface_addr) ||
	    (peer_object_path &&
	     (parse_peer_object_path(peer_object_path, peer_addr) < 0 ||
	      !p2p_peer_known(wpa_s->global->p2p, peer_addr))) ||
	    (interface_addr && hwaddr_aton(interface_addr, peer_addr) < 0))
		goto err;

	wpas_p2p_remove_client(wpa_s, peer_addr, interface_addr != NULL);
	reply = NULL;
out:
	os_free(peer_object_path);
	os_free(interface_addr);
	return reply;
err:
	reply = wpas_dbus_error_invalid_args(message, "Invalid address format");
	goto out;
}