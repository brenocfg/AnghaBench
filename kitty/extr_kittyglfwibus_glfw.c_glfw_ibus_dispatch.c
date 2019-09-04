#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ conn; } ;
typedef  TYPE_1__ _GLFWIBUSData ;

/* Variables and functions */
 int /*<<< orphan*/  glfw_dbus_dispatch (scalar_t__) ; 

void
glfw_ibus_dispatch(_GLFWIBUSData *ibus) {
    if (ibus->conn) glfw_dbus_dispatch(ibus->conn);
}