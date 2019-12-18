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
typedef  int /*<<< orphan*/  u8 ;
struct wpa_supplicant {int /*<<< orphan*/  ifname; int /*<<< orphan*/  conf; TYPE_2__* parent; TYPE_1__* global; } ;
struct wpa_ssid {int disabled; } ;
struct wpa_dbus_dict_entry {char* key; scalar_t__ type; int /*<<< orphan*/  str_value; } ;
struct TYPE_4__ {char* dbus_new_path; } ;
struct TYPE_3__ {struct wpa_supplicant* p2p_init_wpa_s; int /*<<< orphan*/  p2p; } ;
typedef  int /*<<< orphan*/  DBusMessageIter ;
typedef  int /*<<< orphan*/  DBusMessage ;

/* Variables and functions */
 scalar_t__ DBUS_TYPE_OBJECT_PATH ; 
 scalar_t__ EINVAL ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  WPAS_DBUS_NEW_PERSISTENT_GROUPS_PART ; 
 int /*<<< orphan*/  dbus_message_iter_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  os_free (char*) ; 
 scalar_t__ os_strcmp (char*,char*) ; 
 char* os_strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p2p_peer_known (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ parse_peer_object_path (char*,int /*<<< orphan*/ *) ; 
 unsigned int strtoul (char*,int /*<<< orphan*/ *,int) ; 
 struct wpa_ssid* wpa_config_get_network (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  wpa_dbus_dict_entry_clear (struct wpa_dbus_dict_entry*) ; 
 int /*<<< orphan*/  wpa_dbus_dict_get_entry (int /*<<< orphan*/ *,struct wpa_dbus_dict_entry*) ; 
 scalar_t__ wpa_dbus_dict_has_dict_entry (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_dbus_dict_open_read (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_dbus_p2p_check_enabled (struct wpa_supplicant*,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * wpas_dbus_error_invalid_args (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * wpas_dbus_error_unknown_error (int /*<<< orphan*/ *,char*) ; 
 char* wpas_dbus_new_decompose_object_path (char*,int /*<<< orphan*/ ,char**) ; 
 scalar_t__ wpas_p2p_invite (struct wpa_supplicant*,int /*<<< orphan*/ *,struct wpa_ssid*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ wpas_p2p_invite_group (struct wpa_supplicant*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

DBusMessage * wpas_dbus_handler_p2p_invite(DBusMessage *message,
					   struct wpa_supplicant *wpa_s)
{
	DBusMessageIter iter_dict;
	DBusMessage *reply = NULL;
	DBusMessageIter iter;
	struct wpa_dbus_dict_entry entry;
	char *peer_object_path = NULL;
	char *pg_object_path = NULL;
	char *iface = NULL;
	u8 peer_addr[ETH_ALEN];
	unsigned int group_id = 0;
	int persistent = 0;
	struct wpa_ssid *ssid;

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
			peer_object_path = os_strdup(entry.str_value);
			wpa_dbus_dict_entry_clear(&entry);
		} else if (os_strcmp(entry.key, "persistent_group_object") ==
			   0 &&
			   entry.type == DBUS_TYPE_OBJECT_PATH) {
			pg_object_path = os_strdup(entry.str_value);
			persistent = 1;
			wpa_dbus_dict_entry_clear(&entry);
		} else {
			wpa_dbus_dict_entry_clear(&entry);
			goto err;
		}
	}

	if (parse_peer_object_path(peer_object_path, peer_addr) < 0 ||
	    !p2p_peer_known(wpa_s->global->p2p, peer_addr))
		goto err;

	wpa_s = wpa_s->global->p2p_init_wpa_s;

	if (persistent) {
		char *net_id_str;
		/*
		 * A group ID is defined meaning we want to re-invoke a
		 * persistent group
		 */

		iface = wpas_dbus_new_decompose_object_path(
			pg_object_path,
			WPAS_DBUS_NEW_PERSISTENT_GROUPS_PART,
			&net_id_str);
		if (iface == NULL || net_id_str == NULL ||
		    !wpa_s->parent->dbus_new_path ||
		    os_strcmp(iface, wpa_s->parent->dbus_new_path) != 0) {
			reply = wpas_dbus_error_invalid_args(message,
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
			goto err;

		if (wpas_p2p_invite(wpa_s, peer_addr, ssid, NULL, 0, 0, 0, 0, 0,
				    0, 0) < 0) {
			reply = wpas_dbus_error_unknown_error(
				message,
				"Failed to reinvoke a persistent group");
			goto out;
		}
	} else {
		/*
		 * No group ID means propose to a peer to join my active group
		 */
		if (wpas_p2p_invite_group(wpa_s, wpa_s->ifname,
					  peer_addr, NULL)) {
			reply = wpas_dbus_error_unknown_error(
				message, "Failed to join to an active group");
			goto out;
		}
	}

out:
	os_free(iface);
	os_free(pg_object_path);
	os_free(peer_object_path);
	return reply;

err:
	reply = wpas_dbus_error_invalid_args(message, NULL);
	goto out;
}