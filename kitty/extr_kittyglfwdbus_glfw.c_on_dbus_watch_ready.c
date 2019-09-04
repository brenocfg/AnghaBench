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
 unsigned int DBUS_WATCH_ERROR ; 
 unsigned int DBUS_WATCH_HANGUP ; 
 unsigned int DBUS_WATCH_READABLE ; 
 unsigned int DBUS_WATCH_WRITABLE ; 
 int POLLERR ; 
 int POLLHUP ; 
 int POLLIN ; 
 int POLLOUT ; 
 int /*<<< orphan*/  dbus_watch_handle (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static void
on_dbus_watch_ready(int fd, int events, void *data) {
    DBusWatch *watch = (DBusWatch*)data;
    unsigned int flags = 0;
    if (events & POLLERR) flags |= DBUS_WATCH_ERROR;
    if (events & POLLHUP) flags |= DBUS_WATCH_HANGUP;
    if (events & POLLIN) flags |= DBUS_WATCH_READABLE;
    if (events & POLLOUT) flags |= DBUS_WATCH_WRITABLE;
    dbus_watch_handle(watch, flags);
}