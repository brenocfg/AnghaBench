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
struct wpas_dbus_priv {int /*<<< orphan*/  con; } ;
struct wpa_supplicant {int /*<<< orphan*/  dbus_new_path; TYPE_1__* global; } ;
struct TYPE_2__ {struct wpas_dbus_priv* dbus; } ;
typedef  int /*<<< orphan*/  DBusMessageIter ;
typedef  int /*<<< orphan*/  DBusMessage ;

/* Variables and functions */
 int /*<<< orphan*/  DBUS_TYPE_STRING ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  WPAS_DBUS_NEW_IFACE_INTERFACE ; 
 int /*<<< orphan*/  dbus_connection_send (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_message_iter_append_basic (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const**) ; 
 int /*<<< orphan*/  dbus_message_iter_init_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dbus_message_new_signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dbus_message_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

void wpas_dbus_signal_eap_status(struct wpa_supplicant *wpa_s,
				 const char *status, const char *parameter)
{
	struct wpas_dbus_priv *iface;
	DBusMessage *msg;
	DBusMessageIter iter;

	iface = wpa_s->global->dbus;

	/* Do nothing if the control interface is not turned on */
	if (iface == NULL || !wpa_s->dbus_new_path)
		return;

	msg = dbus_message_new_signal(wpa_s->dbus_new_path,
				      WPAS_DBUS_NEW_IFACE_INTERFACE,
				      "EAP");
	if (msg == NULL)
		return;

	dbus_message_iter_init_append(msg, &iter);

	if (!dbus_message_iter_append_basic(&iter, DBUS_TYPE_STRING, &status) ||
	    !dbus_message_iter_append_basic(&iter, DBUS_TYPE_STRING,
					    &parameter))
		wpa_printf(MSG_ERROR, "dbus: Failed to construct signal");
	else
		dbus_connection_send(iface->con, msg, NULL);
	dbus_message_unref(msg);
}