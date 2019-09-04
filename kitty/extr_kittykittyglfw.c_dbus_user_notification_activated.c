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
typedef  unsigned long uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  Py_True ; 
 int /*<<< orphan*/  call_boss (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,unsigned long,char const*) ; 
 int /*<<< orphan*/  dbus_notification_callback ; 

__attribute__((used)) static void
dbus_user_notification_activated(uint32_t notification_id, const char* action) {
    unsigned long nid = notification_id;
    call_boss(dbus_notification_callback, "Oks", Py_True, nid, action);
}