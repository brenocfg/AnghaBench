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
struct wpas_dbus_priv {int /*<<< orphan*/  con; scalar_t__ should_dispatch; } ;
typedef  scalar_t__ eloop_event_type ;
typedef  int /*<<< orphan*/  DBusWatch ;

/* Variables and functions */
 int /*<<< orphan*/  DBUS_WATCH_ERROR ; 
 int /*<<< orphan*/  DBUS_WATCH_READABLE ; 
 int /*<<< orphan*/  DBUS_WATCH_WRITABLE ; 
 scalar_t__ EVENT_TYPE_EXCEPTION ; 
 scalar_t__ EVENT_TYPE_READ ; 
 scalar_t__ EVENT_TYPE_WRITE ; 
 int /*<<< orphan*/  dbus_connection_ref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbus_connection_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbus_watch_handle (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dispatch_data (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void process_watch(struct wpas_dbus_priv *priv,
			  DBusWatch *watch, eloop_event_type type)
{
	dbus_connection_ref(priv->con);

	priv->should_dispatch = 0;

	if (type == EVENT_TYPE_READ)
		dbus_watch_handle(watch, DBUS_WATCH_READABLE);
	else if (type == EVENT_TYPE_WRITE)
		dbus_watch_handle(watch, DBUS_WATCH_WRITABLE);
	else if (type == EVENT_TYPE_EXCEPTION)
		dbus_watch_handle(watch, DBUS_WATCH_ERROR);

	if (priv->should_dispatch) {
		dispatch_data(priv->con);
		priv->should_dispatch = 0;
	}

	dbus_connection_unref(priv->con);
}