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
struct wpas_dbus_priv {int /*<<< orphan*/  global; } ;
typedef  int /*<<< orphan*/  DBusMessage ;
typedef  int /*<<< orphan*/  DBusHandlerResult ;
typedef  int /*<<< orphan*/  DBusConnection ;

/* Variables and functions */
 int /*<<< orphan*/  DBUS_HANDLER_RESULT_HANDLED ; 
 int /*<<< orphan*/  DBUS_HANDLER_RESULT_NOT_YET_HANDLED ; 
 int /*<<< orphan*/  DBUS_INTERFACE_LOCAL ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  dbus_connection_set_exit_on_disconnect (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ dbus_message_is_signal (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpa_supplicant_terminate_proc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static DBusHandlerResult disconnect_filter(DBusConnection *conn,
					   DBusMessage *message, void *data)
{
	struct wpas_dbus_priv *priv = data;

	if (dbus_message_is_signal(message, DBUS_INTERFACE_LOCAL,
				   "Disconnected")) {
		wpa_printf(MSG_DEBUG, "dbus: bus disconnected, terminating");
		dbus_connection_set_exit_on_disconnect(conn, FALSE);
		wpa_supplicant_terminate_proc(priv->global);
		return DBUS_HANDLER_RESULT_HANDLED;
	} else
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
}