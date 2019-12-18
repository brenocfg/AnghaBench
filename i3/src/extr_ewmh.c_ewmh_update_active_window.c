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
typedef  int /*<<< orphan*/  xcb_window_t ;

/* Variables and functions */
 int /*<<< orphan*/  A__NET_ACTIVE_WINDOW ; 
 int /*<<< orphan*/  XCB_ATOM_WINDOW ; 
 int /*<<< orphan*/  XCB_PROP_MODE_REPLACE ; 
 int /*<<< orphan*/  conn ; 
 int /*<<< orphan*/  root ; 
 int /*<<< orphan*/  xcb_change_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 

void ewmh_update_active_window(xcb_window_t window) {
    xcb_change_property(conn, XCB_PROP_MODE_REPLACE, root,
                        A__NET_ACTIVE_WINDOW, XCB_ATOM_WINDOW, 32, 1, &window);
}