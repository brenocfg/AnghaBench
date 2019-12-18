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
typedef  int /*<<< orphan*/  DBusWatch ;

/* Variables and functions */
 unsigned int DBUS_WATCH_READABLE ; 
 unsigned int DBUS_WATCH_WRITABLE ; 
 int /*<<< orphan*/  EVENT_TYPE_EXCEPTION ; 
 int /*<<< orphan*/  EVENT_TYPE_READ ; 
 int /*<<< orphan*/  EVENT_TYPE_WRITE ; 
 unsigned int dbus_watch_get_flags (int /*<<< orphan*/ *) ; 
 int dbus_watch_get_unix_fd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_watch_set_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eloop_unregister_sock (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void remove_watch(DBusWatch *watch, void *data)
{
	unsigned int flags;
	int fd;

	flags = dbus_watch_get_flags(watch);
	fd = dbus_watch_get_unix_fd(watch);

	eloop_unregister_sock(fd, EVENT_TYPE_EXCEPTION);

	if (flags & DBUS_WATCH_READABLE)
		eloop_unregister_sock(fd, EVENT_TYPE_READ);
	if (flags & DBUS_WATCH_WRITABLE)
		eloop_unregister_sock(fd, EVENT_TYPE_WRITE);

	dbus_watch_set_data(watch, NULL, NULL);
}