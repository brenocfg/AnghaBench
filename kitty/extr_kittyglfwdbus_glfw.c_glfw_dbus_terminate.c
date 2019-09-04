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
typedef  int /*<<< orphan*/  _GLFWDBUSData ;
struct TYPE_2__ {int /*<<< orphan*/ * eld; } ;

/* Variables and functions */
 int /*<<< orphan*/  dbus_connection_unref (int /*<<< orphan*/ *) ; 
 TYPE_1__* dbus_data ; 
 int /*<<< orphan*/ * session_bus ; 

void
glfw_dbus_terminate(_GLFWDBUSData *dbus) {
    if (dbus_data) {
        dbus_data->eld = NULL;
        dbus_data = NULL;
    }
    if (session_bus) {
        dbus_connection_unref(session_bus);
        session_bus = NULL;
    }
}