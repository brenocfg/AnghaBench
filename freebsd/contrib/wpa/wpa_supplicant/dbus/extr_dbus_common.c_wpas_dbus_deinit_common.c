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
struct wpas_dbus_priv {struct wpas_dbus_priv* con; } ;

/* Variables and functions */
 int /*<<< orphan*/ * ELOOP_ALL_CTX ; 
 int /*<<< orphan*/  dbus_connection_remove_filter (struct wpas_dbus_priv*,int /*<<< orphan*/ ,struct wpas_dbus_priv*) ; 
 int /*<<< orphan*/  dbus_connection_set_timeout_functions (struct wpas_dbus_priv*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_connection_set_watch_functions (struct wpas_dbus_priv*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_connection_unref (struct wpas_dbus_priv*) ; 
 int /*<<< orphan*/  disconnect_filter ; 
 int /*<<< orphan*/  dispatch_initial_dbus_messages ; 
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/ ,struct wpas_dbus_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_free (struct wpas_dbus_priv*) ; 
 int /*<<< orphan*/  process_timeout ; 

__attribute__((used)) static void wpas_dbus_deinit_common(struct wpas_dbus_priv *priv)
{
	if (priv->con) {
		eloop_cancel_timeout(dispatch_initial_dbus_messages,
				     priv->con, NULL);
		eloop_cancel_timeout(process_timeout, priv, ELOOP_ALL_CTX);

		dbus_connection_set_watch_functions(priv->con, NULL, NULL,
						    NULL, NULL, NULL);
		dbus_connection_set_timeout_functions(priv->con, NULL, NULL,
						      NULL, NULL, NULL);
		dbus_connection_remove_filter(priv->con, disconnect_filter,
					      priv);

		dbus_connection_unref(priv->con);
	}

	os_free(priv);
}