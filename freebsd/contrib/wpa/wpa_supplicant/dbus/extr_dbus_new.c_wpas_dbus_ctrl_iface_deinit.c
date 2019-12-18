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
struct wpas_dbus_priv {int /*<<< orphan*/  con; int /*<<< orphan*/  dbus_new_initialized; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  WPAS_DBUS_NEW_PATH ; 
 int /*<<< orphan*/  dbus_connection_unregister_object_path (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_dbus_ctrl_iface_props_deinit (struct wpas_dbus_priv*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void wpas_dbus_ctrl_iface_deinit(struct wpas_dbus_priv *priv)
{
	if (!priv->dbus_new_initialized)
		return;
	wpa_printf(MSG_DEBUG, "dbus: Unregister D-Bus object '%s'",
		   WPAS_DBUS_NEW_PATH);
	dbus_connection_unregister_object_path(priv->con, WPAS_DBUS_NEW_PATH);
	wpa_dbus_ctrl_iface_props_deinit(priv);
}