#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  input_ctx_path; int /*<<< orphan*/  conn; } ;
typedef  TYPE_1__ _GLFWIBUSData ;

/* Variables and functions */
 int /*<<< orphan*/  DBUS_TYPE_INVALID ; 
 int /*<<< orphan*/  IBUS_INPUT_INTERFACE ; 
 int /*<<< orphan*/  IBUS_SERVICE ; 
 scalar_t__ check_connection (TYPE_1__*) ; 
 int /*<<< orphan*/  glfw_dbus_call_method_no_reply (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
simple_message(_GLFWIBUSData *ibus, const char *method) {
    if (check_connection(ibus)) {
        glfw_dbus_call_method_no_reply(ibus->conn, IBUS_SERVICE, ibus->input_ctx_path, IBUS_INPUT_INTERFACE, method, DBUS_TYPE_INVALID);
    }
}