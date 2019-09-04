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
typedef  int /*<<< orphan*/  DBusTimeout ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ addTimer (int /*<<< orphan*/ ,void*,double,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* dbus_data ; 
 scalar_t__ dbus_timeout_get_enabled (int /*<<< orphan*/ *) ; 
 scalar_t__ dbus_timeout_get_interval (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_timeout_set_data (int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free ; 
 scalar_t__* malloc (int) ; 
 int /*<<< orphan*/  on_dbus_timer_ready ; 
 int /*<<< orphan*/  removeTimer (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static dbus_bool_t
add_dbus_timeout(DBusTimeout *timeout, void *data) {
    int enabled = dbus_timeout_get_enabled(timeout) ? 1 : 0;
    double interval = ((double)dbus_timeout_get_interval(timeout)) / 1000.0;
    if (interval < 0) return FALSE;
    id_type timer_id = addTimer(dbus_data->eld, data, interval, enabled, true, on_dbus_timer_ready, timeout, NULL);
    if (!timer_id) return FALSE;
    id_type *idp = malloc(sizeof(id_type));
    if (!idp) {
        removeTimer(dbus_data->eld, timer_id);
        return FALSE;
    }
    *idp = timer_id;
    dbus_timeout_set_data(timeout, idp, free);
    return TRUE;

}