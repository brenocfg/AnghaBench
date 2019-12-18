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
struct wpa_supplicant {int /*<<< orphan*/  eapol; int /*<<< orphan*/  conf; int /*<<< orphan*/  dbus_new_path; } ;
struct wpa_ssid {int dummy; } ;
typedef  int /*<<< orphan*/  DBusMessage ;

/* Variables and functions */
 int /*<<< orphan*/  DBUS_TYPE_INVALID ; 
 int /*<<< orphan*/  DBUS_TYPE_OBJECT_PATH ; 
 int /*<<< orphan*/  DBUS_TYPE_STRING ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  WPAS_DBUS_NEW_NETWORKS_PART ; 
 int /*<<< orphan*/  dbus_message_get_args (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const**,int /*<<< orphan*/ ,char const**,int /*<<< orphan*/ ,char const**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eapol_sm_notify_ctrl_response (int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  os_free (char*) ; 
 scalar_t__ os_strcmp (char*,int /*<<< orphan*/ ) ; 
 int strtoul (char*,int /*<<< orphan*/ *,int) ; 
 struct wpa_ssid* wpa_config_get_network (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ wpa_supplicant_ctrl_iface_ctrl_rsp_handle (struct wpa_supplicant*,struct wpa_ssid*,char const*,char const*) ; 
 int /*<<< orphan*/ * wpas_dbus_error_invalid_args (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * wpas_dbus_error_network_unknown (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * wpas_dbus_error_unknown_error (int /*<<< orphan*/ *,char*) ; 
 char* wpas_dbus_new_decompose_object_path (char const*,int /*<<< orphan*/ ,char**) ; 

DBusMessage * wpas_dbus_handler_network_reply(DBusMessage *message,
					      struct wpa_supplicant *wpa_s)
{
#ifdef IEEE8021X_EAPOL
	DBusMessage *reply = NULL;
	const char *op, *field, *value;
	char *iface, *net_id;
	int id;
	struct wpa_ssid *ssid;

	if (!dbus_message_get_args(message, NULL,
				   DBUS_TYPE_OBJECT_PATH, &op,
				   DBUS_TYPE_STRING, &field,
				   DBUS_TYPE_STRING, &value,
				   DBUS_TYPE_INVALID))
		return wpas_dbus_error_invalid_args(message, NULL);

	/* Extract the network ID and ensure the network */
	/* is actually a child of this interface */
	iface = wpas_dbus_new_decompose_object_path(op,
						    WPAS_DBUS_NEW_NETWORKS_PART,
						    &net_id);
	if (iface == NULL || net_id == NULL || !wpa_s->dbus_new_path ||
	    os_strcmp(iface, wpa_s->dbus_new_path) != 0) {
		reply = wpas_dbus_error_invalid_args(message, op);
		goto out;
	}

	errno = 0;
	id = strtoul(net_id, NULL, 10);
	if (errno != 0) {
		reply = wpas_dbus_error_invalid_args(message, net_id);
		goto out;
	}

	ssid = wpa_config_get_network(wpa_s->conf, id);
	if (ssid == NULL) {
		reply = wpas_dbus_error_network_unknown(message);
		goto out;
	}

	if (wpa_supplicant_ctrl_iface_ctrl_rsp_handle(wpa_s, ssid,
						      field, value) < 0)
		reply = wpas_dbus_error_invalid_args(message, field);
	else {
		/* Tell EAP to retry immediately */
		eapol_sm_notify_ctrl_response(wpa_s->eapol);
	}

out:
	os_free(iface);
	return reply;
#else /* IEEE8021X_EAPOL */
	wpa_printf(MSG_DEBUG, "dbus: 802.1X not included");
	return wpas_dbus_error_unknown_error(message, "802.1X not included");
#endif /* IEEE8021X_EAPOL */
}