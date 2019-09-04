#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ id_type ;
typedef  int /*<<< orphan*/  dbus_bool_t ;
struct TYPE_2__ {int /*<<< orphan*/  eld; } ;
typedef  int /*<<< orphan*/  DBusWatch ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ addWatch (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* dbus_data ; 
 int /*<<< orphan*/  dbus_watch_get_enabled (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_watch_get_unix_fd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_watch_set_data (int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  events_for_watch (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free ; 
 scalar_t__* malloc (int) ; 
 int /*<<< orphan*/  on_dbus_watch_ready ; 

__attribute__((used)) static dbus_bool_t
add_dbus_watch(DBusWatch *watch, void *data) {
    id_type watch_id = addWatch(dbus_data->eld, data, dbus_watch_get_unix_fd(watch), events_for_watch(watch), dbus_watch_get_enabled(watch), on_dbus_watch_ready, watch);
    if (!watch_id) return FALSE;
    id_type *idp = malloc(sizeof(id_type));
    if (!idp) return FALSE;
    *idp = watch_id;
    dbus_watch_set_data(watch, idp, free);
    return TRUE;
}