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
typedef  scalar_t__ dbus_bool_t ;
struct TYPE_2__ {struct wpas_dbus_priv* dbus; } ;
typedef  int /*<<< orphan*/  DBusMessageIter ;
typedef  int /*<<< orphan*/  DBusMessage ;

/* Variables and functions */
 int /*<<< orphan*/  DBUS_TYPE_OBJECT_PATH ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  WPAS_DBUS_NEW_IFACE_INTERFACE ; 
 int /*<<< orphan*/  WPAS_DBUS_NEW_IFACE_STA ; 
 int /*<<< orphan*/  dbus_connection_send (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_message_iter_append_basic (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const**) ; 
 int /*<<< orphan*/  dbus_message_iter_init_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dbus_message_new_signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  dbus_message_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_dbus_get_object_properties (struct wpas_dbus_priv*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void wpas_dbus_signal_station(struct wpa_supplicant *wpa_s,
				     const char *station_obj_path,
				     const char *sig_name,
				     dbus_bool_t properties)
{
	struct wpas_dbus_priv *iface;
	DBusMessage *msg;
	DBusMessageIter iter;

	iface = wpa_s->global->dbus;

	/* Do nothing if the control interface is not turned on */
	if (!iface || !wpa_s->dbus_new_path)
		return;

	wpa_printf(MSG_DEBUG, "dbus: STA signal %s", sig_name);
	msg = dbus_message_new_signal(wpa_s->dbus_new_path,
				      WPAS_DBUS_NEW_IFACE_INTERFACE, sig_name);
	if (!msg)
		return;

	dbus_message_iter_init_append(msg, &iter);
	if (!dbus_message_iter_append_basic(&iter, DBUS_TYPE_OBJECT_PATH,
					    &station_obj_path) ||
	    (properties &&
	     !wpa_dbus_get_object_properties(iface, station_obj_path,
					     WPAS_DBUS_NEW_IFACE_STA,
					     &iter)))
		wpa_printf(MSG_ERROR, "dbus: Failed to construct signal");
	else
		dbus_connection_send(iface->con, msg, NULL);
	dbus_message_unref(msg);
}