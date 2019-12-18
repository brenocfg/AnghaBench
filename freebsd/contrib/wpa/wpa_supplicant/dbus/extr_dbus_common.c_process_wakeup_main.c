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
 scalar_t__ DBUS_DISPATCH_DATA_REMAINS ; 
 int SIGPOLL ; 
 int /*<<< orphan*/  dbus_connection_dispatch (int /*<<< orphan*/ ) ; 
 scalar_t__ dbus_connection_get_dispatch_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbus_connection_ref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbus_connection_unref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void process_wakeup_main(int sig, void *signal_ctx)
{
	struct wpas_dbus_priv *priv = signal_ctx;

	if (sig != SIGPOLL || !priv->con)
		return;

	if (dbus_connection_get_dispatch_status(priv->con) !=
	    DBUS_DISPATCH_DATA_REMAINS)
		return;

	/* Only dispatch once - we do not want to starve other events */
	dbus_connection_ref(priv->con);
	dbus_connection_dispatch(priv->con);
	dbus_connection_unref(priv->con);
}