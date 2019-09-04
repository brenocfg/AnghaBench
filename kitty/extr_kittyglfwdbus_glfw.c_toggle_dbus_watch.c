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
typedef  int /*<<< orphan*/  id_type ;
struct TYPE_2__ {int /*<<< orphan*/  eld; } ;
typedef  int /*<<< orphan*/  DBusWatch ;

/* Variables and functions */
 TYPE_1__* dbus_data ; 
 int /*<<< orphan*/ * dbus_watch_get_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_watch_get_enabled (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  toggleWatch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
toggle_dbus_watch(DBusWatch *watch, void *data) {
    id_type *idp = dbus_watch_get_data(watch);
    if (idp) toggleWatch(dbus_data->eld, *idp, dbus_watch_get_enabled(watch));
}