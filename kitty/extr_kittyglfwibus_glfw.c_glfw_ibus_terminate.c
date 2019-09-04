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
struct TYPE_3__ {int /*<<< orphan*/  ok; int /*<<< orphan*/ * address_file_name; int /*<<< orphan*/ * address; int /*<<< orphan*/ * input_ctx_path; int /*<<< orphan*/ * conn; } ;
typedef  TYPE_1__ _GLFWIBUSData ;

/* Variables and functions */
 int /*<<< orphan*/  GLFW_FALSE ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  glfw_dbus_close_connection (int /*<<< orphan*/ *) ; 

void
glfw_ibus_terminate(_GLFWIBUSData *ibus) {
    if (ibus->conn) {
        glfw_dbus_close_connection(ibus->conn);
        ibus->conn = NULL;
    }
#define F(x) if (ibus->x) { free((void*)ibus->x); ibus->x = NULL; }
    F(input_ctx_path);
    F(address);
    F(address_file_name);
#undef F

    ibus->ok = GLFW_FALSE;
}