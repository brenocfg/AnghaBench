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
struct wpas_dbus_priv {int /*<<< orphan*/  con; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  SIGPOLL ; 
 int /*<<< orphan*/  add_timeout ; 
 int /*<<< orphan*/  add_watch ; 
 int /*<<< orphan*/  dbus_connection_set_timeout_functions (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wpas_dbus_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_connection_set_wakeup_main_function (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wpas_dbus_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_connection_set_watch_functions (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wpas_dbus_priv*,int /*<<< orphan*/ *) ; 
 scalar_t__ eloop_register_signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wpas_dbus_priv*) ; 
 int /*<<< orphan*/  process_wakeup_main ; 
 int /*<<< orphan*/  remove_timeout ; 
 int /*<<< orphan*/  remove_watch ; 
 int /*<<< orphan*/  timeout_toggled ; 
 int /*<<< orphan*/  wakeup_main ; 
 int /*<<< orphan*/  watch_toggled ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int integrate_with_eloop(struct wpas_dbus_priv *priv)
{
	if (!dbus_connection_set_watch_functions(priv->con, add_watch,
						 remove_watch, watch_toggled,
						 priv, NULL) ||
	    !dbus_connection_set_timeout_functions(priv->con, add_timeout,
						   remove_timeout,
						   timeout_toggled, priv,
						   NULL)) {
		wpa_printf(MSG_ERROR, "dbus: Failed to set callback functions");
		return -1;
	}

	if (eloop_register_signal(SIGPOLL, process_wakeup_main, priv))
		return -1;
	dbus_connection_set_wakeup_main_function(priv->con, wakeup_main,
						 priv, NULL);

	return 0;
}