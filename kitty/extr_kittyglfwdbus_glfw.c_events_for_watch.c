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
 int POLLIN ; 
 int POLLOUT ; 
 unsigned int dbus_watch_get_flags (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int
events_for_watch(DBusWatch *watch) {
    int events = 0;
    unsigned int flags = dbus_watch_get_flags(watch);
    if (flags & DBUS_WATCH_READABLE) events |= POLLIN;
    if (flags & DBUS_WATCH_WRITABLE) events |= POLLOUT;
    return events;
}