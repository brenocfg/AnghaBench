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
 int /*<<< orphan*/  A__NET_WM_STATE ; 
 int /*<<< orphan*/  A__NET_WM_STATE_FOCUSED ; 
 int /*<<< orphan*/  DLOG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  conn ; 
 int /*<<< orphan*/  xcb_add_property_atom (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xcb_remove_property_atom (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ewmh_update_focused(xcb_window_t window, bool is_focused) {
    if (is_focused) {
        DLOG("Setting _NET_WM_STATE_FOCUSED for window = %d.\n", window);
        xcb_add_property_atom(conn, window, A__NET_WM_STATE, A__NET_WM_STATE_FOCUSED);
    } else {
        DLOG("Removing _NET_WM_STATE_FOCUSED for window = %d.\n", window);
        xcb_remove_property_atom(conn, window, A__NET_WM_STATE, A__NET_WM_STATE_FOCUSED);
    }
}