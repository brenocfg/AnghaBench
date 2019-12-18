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
struct wpas_dbus_priv {int dummy; } ;
typedef  int /*<<< orphan*/  dbus_bool_t ;
typedef  int /*<<< orphan*/  DBusWatch ;

/* Variables and functions */
 unsigned int DBUS_WATCH_READABLE ; 
 unsigned int DBUS_WATCH_WRITABLE ; 
 int /*<<< orphan*/  EVENT_TYPE_EXCEPTION ; 
 int /*<<< orphan*/  EVENT_TYPE_READ ; 
 int /*<<< orphan*/  EVENT_TYPE_WRITE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  dbus_watch_get_enabled (int /*<<< orphan*/ *) ; 
 unsigned int dbus_watch_get_flags (int /*<<< orphan*/ *) ; 
 int dbus_watch_get_unix_fd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_watch_set_data (int /*<<< orphan*/ *,struct wpas_dbus_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eloop_register_sock (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wpas_dbus_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  process_watch_exception ; 
 int /*<<< orphan*/  process_watch_read ; 
 int /*<<< orphan*/  process_watch_write ; 

__attribute__((used)) static dbus_bool_t add_watch(DBusWatch *watch, void *data)
{
	struct wpas_dbus_priv *priv = data;
	unsigned int flags;
	int fd;

	if (!dbus_watch_get_enabled(watch))
		return TRUE;

	flags = dbus_watch_get_flags(watch);
	fd = dbus_watch_get_unix_fd(watch);

	eloop_register_sock(fd, EVENT_TYPE_EXCEPTION, process_watch_exception,
			    priv, watch);

	if (flags & DBUS_WATCH_READABLE) {
		eloop_register_sock(fd, EVENT_TYPE_READ, process_watch_read,
				    priv, watch);
	}
	if (flags & DBUS_WATCH_WRITABLE) {
		eloop_register_sock(fd, EVENT_TYPE_WRITE, process_watch_write,
				    priv, watch);
	}

	dbus_watch_set_data(watch, priv, NULL);

	return TRUE;
}