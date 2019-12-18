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
 int /*<<< orphan*/  A_UTF8_STRING ; 
 int /*<<< orphan*/  A__NET_WM_VISIBLE_NAME ; 
 int /*<<< orphan*/  XCB_PROP_MODE_REPLACE ; 
 int /*<<< orphan*/  conn ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  xcb_change_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  xcb_delete_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ewmh_update_visible_name(xcb_window_t window, const char *name) {
    if (name != NULL) {
        xcb_change_property(conn, XCB_PROP_MODE_REPLACE, window, A__NET_WM_VISIBLE_NAME, A_UTF8_STRING, 8, strlen(name), name);
    } else {
        xcb_delete_property(conn, window, A__NET_WM_VISIBLE_NAME);
    }
}