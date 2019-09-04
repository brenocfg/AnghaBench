#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct stat {scalar_t__ st_mtime; } ;
struct TYPE_5__ {scalar_t__ address_file_mtime; int /*<<< orphan*/  address_file_name; int /*<<< orphan*/  ok; scalar_t__ conn; int /*<<< orphan*/  inited; } ;
typedef  TYPE_1__ _GLFWIBUSData ;
typedef  int /*<<< orphan*/  GLFWbool ;

/* Variables and functions */
 int /*<<< orphan*/  GLFW_FALSE ; 
 scalar_t__ dbus_connection_get_is_connected (scalar_t__) ; 
 int /*<<< orphan*/  read_ibus_address (TYPE_1__*) ; 
 int /*<<< orphan*/  setup_connection (TYPE_1__*) ; 
 scalar_t__ stat (int /*<<< orphan*/ ,struct stat*) ; 

__attribute__((used)) static GLFWbool
check_connection(_GLFWIBUSData *ibus) {
    if (!ibus->inited) return GLFW_FALSE;
    if (ibus->conn && dbus_connection_get_is_connected(ibus->conn)) {
        return ibus->ok;
    }
    struct stat s;
    if (stat(ibus->address_file_name, &s) != 0 || s.st_mtime != ibus->address_file_mtime) {
        if (!read_ibus_address(ibus)) return GLFW_FALSE;
        setup_connection(ibus);
    }
    return GLFW_FALSE;
}