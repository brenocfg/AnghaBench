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
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  A_I3_CONFIG_PATH ; 
 int /*<<< orphan*/  A_I3_PID ; 
 int /*<<< orphan*/  A_I3_SOCKET_PATH ; 
 int /*<<< orphan*/  A_UTF8_STRING ; 
 int /*<<< orphan*/  XCB_ATOM_CARDINAL ; 
 int /*<<< orphan*/  XCB_PROP_MODE_REPLACE ; 
 int /*<<< orphan*/  conn ; 
 int /*<<< orphan*/ * current_configpath ; 
 int /*<<< orphan*/ * current_socketpath ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  root ; 
 int strlen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_shmlog_atom () ; 
 int /*<<< orphan*/  xcb_change_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 

void x_set_i3_atoms(void) {
    pid_t pid = getpid();
    xcb_change_property(conn, XCB_PROP_MODE_REPLACE, root, A_I3_SOCKET_PATH, A_UTF8_STRING, 8,
                        (current_socketpath == NULL ? 0 : strlen(current_socketpath)),
                        current_socketpath);
    xcb_change_property(conn, XCB_PROP_MODE_REPLACE, root, A_I3_PID, XCB_ATOM_CARDINAL, 32, 1, &pid);
    xcb_change_property(conn, XCB_PROP_MODE_REPLACE, root, A_I3_CONFIG_PATH, A_UTF8_STRING, 8,
                        strlen(current_configpath), current_configpath);
    update_shmlog_atom();
}